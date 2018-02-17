#pragma once
#include "masterHeaders.h"
#include "openPoseUtil.h"

static const string modelNames[] =
{
	"COCO",
	"MPI",
	"MPI_4_layers"
};

const static string getJointName(CocoJointTypes k);
const static string getJointName(MPIJointTypes k);

class ofApp : public ofBaseApp
{
	int currentFrame;
	PoseScenes scenes;
	ofImage currentImage;
	OpenPoseArguments loadSettings();
	ofVideoPlayer videoPlayer;

	public:
		void setup();
};
