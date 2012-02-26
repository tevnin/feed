#pragma once

#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

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

		ofVideoPlayer 		testMovie;
        vector <particle *> myParticles;
    
        ofSoundPlayer		daft;
        
        float 				* fftSmoothed;
        
		float dist;
		float avg;

        int nBandsToGet;
        float width;
        float height;
    
        int count;
        bool stageA;
        bool stageB;
        bool stageC;
    int movieW;
    int movieH;

};

