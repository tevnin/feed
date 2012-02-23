#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

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
        void makeWish();
        void backToDandelion();
        void audioIn(float * input, int bufferSize, int nChannels); 

		
		// let's make a vector of them
		vector <particle> particles;
        vectorField VF;
	
		bool	bRepel;
		float	radius;
		float	strength;
    
        int drawingStyle;
        bool bFade;
    
        float prevMouseX;
        float prevMouseY;
        
        int moveX;
        int moveY;
        
        float prevFluffX;
        float prevFluffY;
    
        int counter;
    bool makeWishbool;
	
		ofImage bg, spot, spot2;
    
	
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
 
    
    
    
   
	
		 
	
};

#endif
	
