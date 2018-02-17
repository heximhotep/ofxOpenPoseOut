@echo off

set GET_CAFFE_PATH=ofxOpenPoseOut\3rdparty\windows
set GET_CAFFE_BAT=getCaffe.bat
set GET_CAFFETP_PATH=ofxOpenPoseOut\3rdparty\windows
set GET_CAFFETP_BAT=getCaffe3rdparty.bat
set GET_OPENCV_PATH=ofxOpenPoseOut\3rdparty\windows
set GET_OPENCV_BAT=getOpenCV.bat
set GET_MODELS_PATH=ofxOpenPoseOut\models
set GET_MODELS_BAT=getModels.bat

cd %GET_CAFFE_PATH%
%GET_CAFFE_BAT%
cd ../../..

cd %GET_CAFFETP_PATH%
%GET_CAFFETP_BAT%
cd ../../..

cd %GET_OPENCV_PATH%
%GET_OPENCV_BAT%
cd ../../..

cd %GET_MODELS_PATH%
%GET_MODELS_BAT%
cd ../..