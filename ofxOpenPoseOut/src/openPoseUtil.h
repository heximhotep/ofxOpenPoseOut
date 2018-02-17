#pragma once

#include "masterHeaders.h"
#include <openpose/core/headers.hpp>
#include <openpose/filestream/headers.hpp>
#include <openpose/gui/headers.hpp>
#include <openpose/pose/headers.hpp>
#include <openpose/utilities/headers.hpp>

//model to be used in pose estimation
//COCO - 18 points
//MPI  - 15 points
//MPI_4_layers - 15 points - faster but less accurate
enum ModelType
{
	COCO,
	MPI,
	MPI_4_layers
};

struct OpenPoseArguments
{
	int loggingLevel;
	string inputVideoPath;
	string modelFolder;
	ModelType modelType;
	string netResolution;
	string outputResolution;
	int gpuDeviceNumber;
	double scaleGap;
	int scaleNumber;
	int startFrame, numFrames, frameSkip;
};

struct PoseScenes
{
	int width, height;
	std::vector<struct PoseScene> scenes;
};

struct PoseScene 
{
	string sceneName;
	vector<struct PosePoints> poses;
};

struct PosePoints
{
	vector<struct JointPosition> positions;
};

struct JointPosition
{
	float x, y, z;
	JointPosition(float, float, float);
};

static ofDirectory inputImageDirectory;

PoseScenes imageExtraction(struct OpenPoseArguments args);
