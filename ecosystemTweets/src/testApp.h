#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxJSONElement.h"
#include "particle.h"


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
		
		
		ofTrueTypeFont  franklinBook;
	
		ofxJSONElement result1;
        ofxJSONElement result2;
    
        // particle stuff
        vector <particle> particles;
        vector <particle> particles2;
        
        void audioRequested(float *input, int bufferSize, int nChannels);
        float frequency;
        float position;
        float positionAdder;
    
        bool printHash;
};

#endif	

