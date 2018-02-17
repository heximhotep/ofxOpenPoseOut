
#include "openPoseUtil.h"

JointPosition::JointPosition(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

PoseScenes imageExtraction(struct OpenPoseArguments args)
{
	int logging_level = args.loggingLevel;
	PoseScenes result;

	op::ConfigureLog::setPriorityThreshold((op::Priority)args.loggingLevel);
	op::Point<int> netInputSize = op::flagsToPoint(args.netResolution);
	op::Point<int> outputSize(op::flagsToPoint(args.outputResolution));
	string modelPoseStr;
	switch (args.modelType)
	{
	case(ModelType::COCO):
		modelPoseStr = "COCO";
		break;
	case(ModelType::MPI):
		modelPoseStr = "MPI";
		break;
	case(ModelType::MPI_4_layers):
		modelPoseStr = "MPI_4_layers";
		break;
	}
	op::PoseModel poseModel = op::flagsToPoseModel(modelPoseStr);

	op::ScaleAndSizeExtractor scaleAndSizeExtractor(netInputSize, outputSize, args.scaleNumber, args.scaleGap);
	op::CvMatToOpInput cvMatToOpInput;
	op::CvMatToOpOutput cvMatToOpOutput;
	op::PoseExtractorCaffe poseExtractorCaffe{ poseModel, args.modelFolder, args.gpuDeviceNumber, {}, op::ScaleMode::ZeroToOne, false };
	
	poseExtractorCaffe.initializationOnThread();

	ofVideoPlayer vidPlayer;
	
	vidPlayer.load(args.inputVideoPath);
	printf("video has %d total frames -- jumping to frame %d\n", vidPlayer.getTotalNumFrames(), args.startFrame, stderr);
	vidPlayer.play();

	vidPlayer.setFrame(args.startFrame); 
	vidPlayer.setPaused(true);
	
	for (int i = 0; i < args.numFrames; i++)
	{
		ofPixels & framePixels = vidPlayer.getPixels();
		ofImage testImg;
		testImg.allocate(framePixels.getWidth(), framePixels.getHeight(), OF_IMAGE_COLOR);
		testImg.setFromPixels(framePixels);
		//due to differences in the versions of opencv used by ofxOpenCV and OpenPose, the most pain free way i could find to
		//pass captured image frames to OpenPose is to save the image to disk...
		testImg.saveImage("frameImg.jpg", ofImageQualityType::OF_IMAGE_QUALITY_MEDIUM);
		//and then reload it using the op namespace I/O functionality
		cv::Mat inputImage = op::loadImage("bin/data/frameImg.jpg", CV_LOAD_IMAGE_COLOR);
		const op::Point<int> imageSize{ inputImage.cols, inputImage.rows };
		result.width = imageSize.x;
		result.height = imageSize.y;
		// Get desired scale sizes
		std::vector<double> scaleInputToNetInputs;
		std::vector<op::Point<int>> netInputSizes;
		double scaleInputToOutput;
		op::Point<int> outputResolution;
		std::tie(scaleInputToNetInputs, netInputSizes, scaleInputToOutput, outputResolution)
			= scaleAndSizeExtractor.extract(imageSize);
		// Format input image to OpenPose input and output formats
		const auto netInputArray = cvMatToOpInput.createArray(inputImage, scaleInputToNetInputs, netInputSizes);
		auto outputArray = cvMatToOpOutput.createArray(inputImage, scaleInputToOutput, outputResolution);
		// Estimate poseKeypoints
		poseExtractorCaffe.forwardPass(netInputArray, imageSize, scaleInputToNetInputs);
		const auto poseKeypoints = poseExtractorCaffe.getPoseKeypoints();
		cerr << "pose keypoints are a float array of dimensions " << poseKeypoints.getSize(0) << " x " << poseKeypoints.getSize(1) << " x " << poseKeypoints.getSize(2) << endl;
		int numPoses = poseKeypoints.getSize(0);
		int numJoints = poseKeypoints.getSize(1);
		PoseScene scene;

		scene.sceneName = "__SCENE__" + ofToString(i);
		for (int i = 0; i < numPoses; i++)
		{
			PosePoints pose;
			for (int j = 0; j < numJoints; j++)
			{
				JointPosition joint(poseKeypoints.at({ i, j, 0 }), poseKeypoints.at({ i, j, 1 }), poseKeypoints.at({ i, j, 2 }));
				pose.positions.push_back(joint);
			}
			scene.poses.push_back(pose);
		}
		result.scenes.push_back(scene);

		vidPlayer.nextFrame();
		if (args.frameSkip > 0)
		{
			int skips = 0;
			while (skips < args.frameSkip)
			{
				vidPlayer.nextFrame();
				skips++;
			}
		}
	}
	printf("returning from imageExtraction\n", stderr);
	vidPlayer.close();
	//ofFile testFile();
	//ofFile::open(boost::filesystem::)
	return result;
}