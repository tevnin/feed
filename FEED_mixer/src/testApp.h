#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxJSONElement.h"

// listen on port 9000
#define HOST "169.254.40.135"
#define PORT 9000
#define NUM_MSG_STRINGS 20

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera otherwise, we'll use a movie file


class testApp : public ofBaseApp{
	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofTrueTypeFont		font;
		ofxOscReceiver      receiver;
        ofVideoGrabber      vidGrabber;
        //ofVideoPlayer       jonnysMovies;
        bool                frameByframe;
    
        ofxCvColorImage			colorImg;

		int				current_msg_string;
		string		msg_strings[NUM_MSG_STRINGS];
		float			timers[NUM_MSG_STRINGS];

		int				mouseX, mouseY;
		string			mouseButtonState;
    
        bool            oneOn;
        bool            twoOn;
        bool            threeOn;
        bool            fourOn;
        bool            sliderOn;
    
        ofxJSONElement  twitter;
        string          url;
        int             stringSize;
        int tweetNum;
};
