#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "particle.h"
#include "binner.h"
#include "ofxJSONElement.h"
#include "ofxTimeUtils.h"

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
        vector<particle > myParticles2;
        vector<particle > myParticles3;
        vector<particle > myParticles4;
        vector<particle > myParticles5;
        
        ofSoundStream soundStream;
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
        string typeStr;
	
        ofTrueTypeFont	Archer;
        ofxJSONElement topTrends;
        ofxJSONElement result1;
        ofxJSONElement result2;
        ofxJSONElement result3;
        ofxJSONElement result4;
        ofxJSONElement result5;
	
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
    
        bool printHash;
    
        ofxTimeUtils getHour;
    
        int time_r, time_g, time_b;
    
        string url1, url2, url3, url4, url5, twitterURL;
        string trend1, trend2, trend3, trend4;
        
        float oldNum1, newNum1, oldNum2, newNum2, oldNum3, newNum3, oldNum4, newNum4, oldNum5, newNum5 ;
        int numDiff1, numDiff2, numDiff3, numDiff4, numDiff5;
    
        int proportion;
    
		
};

#endif

