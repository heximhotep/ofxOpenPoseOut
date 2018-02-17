#include "ofApp.h"

#define SETTINGS_PATH "bin/data/settings.config"
#define OUTPUT_PATH "output/output.json"

//--------------------------------------------------------------

const static string getJointName(CocoJointTypes j)
{
	return cocoJointTypeNames[j];
}

const static string getJointName(MPIJointTypes j)
{
	return mpiJointTypeNames[j];
}

OpenPoseArguments ofApp::loadSettings()
{
	ifstream settingsFile(SETTINGS_PATH);
	OpenPoseArguments result;
	string line;
	while (getline(settingsFile, line))
	{
		istringstream lineStream(line);
		string key;
		if (getline(lineStream, key, ':'))
		{
			string value;
			if (getline(lineStream, value))
			{
				if (strcmp(key.c_str(), "inputVideoPath") == 0)
				{
					cerr << "got input path" << std::endl;
					result.inputVideoPath = value;
				}
				if (strcmp(key.c_str(), "loggingLevel") == 0)
				{
					cerr << "got logging level" << std::endl;
					result.loggingLevel = ofToInt(value);
				}
				if (strcmp(key.c_str(), "modelFolder") == 0)
				{
					cerr << "got model folder" << std::endl;
					result.modelFolder = value;
				}
				if (strcmp(key.c_str(), "netResolution") == 0)
				{
					cerr << "got net resolution" << std::endl;
					result.netResolution = value;
				}
				if (strcmp(key.c_str(), "outputResolution") == 0)
				{
					cerr << "got output resolution" << std::endl;
					result.outputResolution = value;
				}
				if (strcmp(key.c_str(), "gpuDeviceNumber") == 0)
				{
					cerr << "got gpu device number" << std::endl;
					result.gpuDeviceNumber = ofToInt(value);
				}
				if (strcmp(key.c_str(), "modelType") == 0)
				{
					cerr << "got model type" << std::endl;
					if (strcmp(value.c_str(), "COCO") == 0)
					{
						result.modelType = ModelType::COCO;
					}
					if (strcmp(value.c_str(), "MPI") == 0)
					{
						result.modelType = ModelType::MPI;
					}
					if (strcmp(value.c_str(), "MPI_4_layers") == 0)
					{
						result.modelType = ModelType::MPI_4_layers;
					}
				}
				if (strcmp(key.c_str(), "scaleGap") == 0)
				{
					cerr << "got scale gap" << std::endl;
					result.scaleGap = ofToDouble(value);
				}
				if (strcmp(key.c_str(), "scaleNumber") == 0)
				{
					cerr << "got scale number" << std::endl;
					result.scaleNumber = ofToInt(value);
				}
				if (strcmp(key.c_str(), "startFrame") == 0)
				{
					cerr << "got start frame" << std::endl;
					result.startFrame = ofToInt(value);
				}
				if (strcmp(key.c_str(), "numFrames") == 0)
				{
					cerr << "got frame count" << std::endl;
					result.numFrames = ofToInt(value);
				}
				if (strcmp(key.c_str(), "skipFrames") == 0)
				{
					cerr << "got frame skip" << std::endl;
					result.frameSkip = ofToInt(value);
				}
			}
		}
	}
	return result;
}

void ofApp::setup()
{
	currentFrame = 0;
	//OpenPoseArguments defined in 'openPoseUtil.h'
	OpenPoseArguments args = loadSettings();

	//extract pose data from all images in input directory
	
	scenes = imageExtraction(args);
	Json::Value jsonObject;
	ofxJSONElement jsonWriter;

	int numScenes = scenes.scenes.size();
	
	jsonObject["numScenes"] = numScenes;
	jsonObject["poseModel"] = modelNames[args.modelType];
	jsonObject["imageWidth"] = scenes.width;
	jsonObject["imageHeight"] = scenes.height;

	for (int i = 0; i < numScenes; i++)
	{
		string sceneIndex = ofToString(i);
		PoseScene scene = scenes.scenes[i];
		int numPoses = scene.poses.size();
		jsonObject[sceneIndex]["numPoses"] = numPoses;
		//within each scene we iterate through each detected skeleton
		for (int j = 0; j < numPoses; j++)
		{
			string poseIndex = ofToString(j);
			PosePoints pose = scene.poses[j];
			int numPoints = pose.positions.size();
			//within each skeleton we iterate through each detected point
			for (int k = 0; k < pose.positions.size(); k++)
			{
				JointPosition position = pose.positions[k];
				string jointName;
				if (args.modelType == ModelType::COCO)
					jointName = getJointName((CocoJointTypes)k);
				else
					jointName = getJointName((MPIJointTypes)k);
				Json::Value pointVec(Json::arrayValue);
				pointVec.append(position.x);
				pointVec.append(position.y);
				pointVec.append(position.z); //z encodes the confidence of the guessed position
				jsonObject[sceneIndex][poseIndex][jointName] = pointVec;
			}
		}
	}
	
	string outputName = OUTPUT_PATH;

	jsonWriter.append(jsonObject);
	jsonWriter.save(outputName, false);
	cerr << "finished saving" << endl;
	ofExit(0);
}
