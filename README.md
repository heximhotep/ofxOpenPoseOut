# ofxOpenPose
#### openframeworks project set up to support the OpenPose C++ library
![alt text](https://raw.githubusercontent.com/heximhotep/ofxOpenPoseOut/master/docs/example_img_in.jpg "input frame")
![alt text](https://raw.githubusercontent.com/heximhotep/ofxOpenPoseOut/master/docs/example_img_out.jpg "output frame")

### Prerequisites
openFrameworks
CUDA 8.0 AND 9.0
ofxOpenCV
ofxJSON
K-Lite Codec Pack
(recommended) ffmpeg

### Installation
1. clone this repo into the 'apps' folder of your openFrameworks installation. 
2. run 'setup.bat' to download 3rd party libraries and model files
3. navigate to ofxOpenPoseOut/bin/data
4. place input video(s) in the input folder. Any video format for which you have a codec installed for will work. 
5. open 'settings.config' in Sublime or Wordpad (notepad does not load newlines and is hard to use).
  - change the 'inputVideoPath' property to match the name of your intended video (keep 'input/' prefix)
  - set the 'startFrame' property to the frame you'd like to start analysis at (if set to 0, you will start at the beginning of the video)
  - set the 'numFrames' property to the number of frames you'd like to capture from the video
  - set the 'skipFrames' property to the number of frames you'd like to skip between each capture (0 means no skips -- negative values don't work currently);
6. either open the ofxOpenPoseOut.sln file in the base directory and build for x64 Release, or simply run the prebuilt 'ofxOpenPoseOut.exe' located in ofxOpenPoseOut/bin
