#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGifEncoder.h"
#include "ofxOsc.h"

// listen on port 12345
//#define HOST "169.254.40.135"
//#define PORT 9000
//#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);    
	
	void onGifSaved(string & fileName);
	void exit();
	void captureFrame();
    void midiButton();
	
	vector <ofImage *> imgs; // for previewing  
	
	//vector <ofxGifFrame *> pxs;
	void saveImages();
	
	int frameW, frameH;
	int nFrames;
    
	ofVideoGrabber vid;
	ofxGifEncoder gifEncoder;
	
	//ofVideoPlayer player;
	
	vector <ofImage *> data;
	ofDirectory dir;
	ofDirectory count;
	
	int recordingCount;
	
	//kinect
	ofxKinect 			kinect;
	ofxBase3DVideo* 	kinectSource;
	int					angle;
	int 				pointCloudRotationY;
	bool				bThreshWithOpenCV;
	bool				bDrawPointCloud;
	
	ofxCvColorImage		colorImg;
	
	ofxCvGrayscaleImage grayImage;			// grayscale depth image
	ofxCvGrayscaleImage grayThreshNear;		// the near thresholded image
	ofxCvGrayscaleImage grayThreshFar;		// the far thresholded image
	
	ofxCvContourFinder 	contourFinder;
	
	ofxOscReceiver	receiver;
    int counter;
    bool capture;
	
	
	
};
