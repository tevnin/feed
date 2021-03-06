#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxJSONElement.h"

// listen on port 12345
#define HOST "localhost"
#define PORT 9000
#define NUM_MSG_STRINGS 20

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
        ofVideoPlayer       jonnysMovies;
        bool                frameByframe;

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
};
