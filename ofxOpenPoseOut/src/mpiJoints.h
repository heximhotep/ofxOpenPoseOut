#include "ofMain.h"

#pragma once
enum MPIJointTypes
{
	HEAD,
	NECK_BASE,
	RIGHT_SHOULDER,
	RIGHT_ELBOW,
	RIGHT_WRIST,
	LEFT_SHOULDER,
	LEFT_ELBOW,
	LEFT_WRIST,
	RIGHT_HIP,
	RIGHT_KNEE,
	RIGHT_FOOT,
	LEFT_HIP,
	LEFT_KNEE,
	LEFT_FOOT
};

static const std::string mpiJointTypeNames[] =
{
	"head",
	"neck",
	"right_shoulder",
	"right_elbow",
	"right_wrist",
	"left_shoulder",
	"left_elbow",
	"left_wrist",
	"right_hip",
	"right_knee",
	"right_foot",
	"left_hip",
	"left_knee",
	"left_foot"
};
