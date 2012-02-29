#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "particle.h"
#include "binner.h"
#include "vectorField.h"
#include "ofxJSONElement.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
    
        void audioIn(float * input, int bufferSize, int nChannels); 

		vector<particle > myParticles;
    
        vectorField VF;
        ofSoundStream soundStream;
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
        string typeStr;
	
        ofTrueTypeFont	verdana;
        ofxJSONElement result1;
        ofxJSONElement result2;
        string url1;
	
        bool	bRepel;
        bool	blowIson; 
        bool	goodBlow;
        bool    cellExcited;
        float	radius;
        float	strength;
        float   blowUp;
        float   atractStrenght; 
        float	soundBlowup; 
        float	smoothedVol;
        float	scaledVol, scaledVolalpha;
	
        int 	bufferCounter;
        int 	drawCounter;
	
        int drawingStyle;
        bool bFade;
        bool bParticlesRepel;
	
        float prevMouseX;
        float prevMouseY;
        ofImage sky;
        
        int keyOption;
		
};

#endif

