#include "ofMain.h"

#pragma once
enum CocoJointTypes
{
	NOSE,
	NECK,
	SHOULDER_LEFT,
	ELBOW_LEFT,
	WRIST_LEFT,
	SHOULDER_RIGHT,
	ELBOW_RIGHT,
	WRIST_RIGHT,
	HIP_RIGHT,
	KNEE_RIGHT,
	FOOT_RIGHT,
	HIP_LEFT,
	KNEE_LEFT,
	FOOT_LEFT,
	EYE_LEFT,
	EYE_RIGHT,
	EAR_LEFT,
	EAR_RIGHT
};

static const std::string cocoJointTypeNames[] =
{
	"nose",
	"neck",
	"left_shoulder",
	"left_elbow",
	"left_wrist",
	"right_shoulder",
	"right_elbow",
	"right_wrist",
	"right_hip",
	"right_knee",
	"right_foot",
	"left_hip",
	"left_knee",
	"left_foot",
	"left_eye",
	"right_eye",
	"left_ear",
	"right_ear"
};
