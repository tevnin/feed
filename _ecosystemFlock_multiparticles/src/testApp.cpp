#include "testApp.h"
#include "particle.h"
#include "ofxTimeUtils.h"

//--------------------------------------------------------------
void testApp::setup(){


	
	setupBins(ofGetWidth(), ofGetHeight(), 30,30);
	
	ofBackground(255, 255, 255);
	ofSetCircleResolution(6);
    
    sky.loadImage("sunset_bw2.jpg");

	
	//ofSetVerticalSync(true); // turned off, to see frameRateChanges...
    
    //***************>>>>>>>>TWITTER>>>>>>>>***************//
    
    //franklinBook.loadFont("frabk.ttf", 32);
    //franklinBook.setLineHeight(36);
    
    // Twitter API: http://dev.twitter.com/doc/get/trends/current
    
    string url1 = "http://tweetriver.com/EdibleCircuits/test1/meta.json";
    string url2 = "http://tweetriver.com/EdibleCircuits/trend1/meta.json";

	
    // Now parse the JSON
    bool parsing1Successful = result1.open(url1);
    if ( parsing1Successful ){
        //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend1 = result1["count"]["approved"];
    
    int num1 = trend1.asInt();
    //cout << num/100 << endl;
    //printHash = false;
    
    bool parsing2Successful = result2.open(url2);
    if ( parsing2Successful ){
        //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend2 = result2["count"]["approved"];
    
    int num2 = trend2.asInt();
    //cout << num/100 << endl;
    printHash = false;
	
    
    if ((num1/100)>2000) {
        num1 = 200,000;
    }
    
    if ((num2/100)>2000) {
        num2 = 200,000;
    }
    
    // particle stuff

    for (int i = 0; i < num1/100; i++){
        particle newParticle;
        newParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticle.damping = ofRandom(0.001, 0.05);
        myParticles.push_back(newParticle);
    }
    
    
    for (int i = 0; i < num2/100; i++){
        particle newParticle;
        newParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticle.damping = ofRandom(0.001, 0.05);
        myParticles2.push_back(newParticle);
    }


     //sound stuff------------------------------
	soundStream.listDevices();
	int bufferSize = 256;
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
	//>>-------------------------------------------

}

//--------------------------------------------------------------
void testApp::update(){
    
	//sound stuff------------------------------
	
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	
	//records the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}

	//sound stuff------------------------------    
    
	
	for (int i = 0; i < myParticles.size(); i++){
		computeBinPosition( myParticles[i].pos.x, myParticles[i].pos.y,  &(myParticles[i].bitFlagW), &(myParticles[i].bitFlagH));
	}
    
    for (int i = 0; i < myParticles2.size(); i++){
		computeBinPosition( myParticles2[i].pos.x, myParticles2[i].pos.y,  &(myParticles2[i].bitFlagW), &(myParticles2[i].bitFlagH));
	}
	

	
	int count = 0;
	
    for (int i = 0; i < myParticles.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles[i].addRepulsionForce( myParticles[j],15,1.2); 
                myParticles[i].addForFlocking( myParticles[j]);

				count ++;
			}
        }
    }
    
    for (int i = 0; i < myParticles2.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles2[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles2[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles2[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles2[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles2[i].addRepulsionForce( myParticles2[j],15,1.2); 
                myParticles2[i].addForFlocking( myParticles2[j]);
                
				count ++;
			}
        }
    }
	
	printf("%i \n", count);
    

    
    if(ofGetFrameNum()%600 == 0){
        // Now parse the JSON
        bool parsing1Successful = result1.open(url1);
        if ( parsing1Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend1 = result1["count"]["approved"];
        
        int num1 = trend1.asInt();
        
        for (int i = 0; i < num1/100; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles.push_back(p);
        }
        
        // Now parse the JSON
        bool parsing2Successful = result2.open(url1);
        if ( parsing2Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend2 = result2["count"]["approved"];
        
        int num2 = trend2.asInt();
        
        for (int i = 0; i < num1/100; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles2.push_back(p);
        }

    }
    
    for (int i = 0; i < myParticles.size(); i++){
        
        //if (keyOption==1) {
            myParticles[i].cohesion.distance = 1600;
            myParticles[i].alignment.distance = 1600;
            myParticles[i].seperation.distance = 1600;
            
            
            myParticles[i].cohesion.strength = 0.15;
            myParticles[i].alignment.strength = scaledVol*2;
            myParticles[i].seperation.strength = 0.015;
            
            myParticles[i].damping =  0.03f;	
        //}
        /*
        else if (keyOption==2) {
            myParticles[i].cohesion.distance = 200;
            myParticles[i].alignment.distance = 600;
            myParticles[i].seperation.distance = 400;
            
            
            myParticles[i].cohesion.strength = 0.015;
            myParticles[i].alignment.strength = scaledVol;
            myParticles[i].seperation.strength = 0.015;
            
            myParticles[i].damping =  0.05f;	
        }
        
        else if (keyOption==3) {
            myParticles[i].cohesion.distance = 800;
            myParticles[i].alignment.distance = 800;
            myParticles[i].seperation.distance = 400;
            
            
            myParticles[i].cohesion.strength = 0.30;
            myParticles[i].alignment.strength = scaledVol * 2;
            myParticles[i].seperation.strength = 0.015;
            
            myParticles[i].damping =  0.5f;	
        }*/
         
        if (myParticles[i].alignment.strength < 0.15) {
            myParticles[i].alignment.strength = 0.15;
        }
        
        
	}
    

    /////////////////
 
    for (int i = 0; i < myParticles.size(); i++){
		myParticles[i].addFlockingForce();
		myParticles[i].addDampingForce();
		myParticles[i].update();
	}
    
    // wrap torroidally.
	for (int i = 0; i < myParticles.size(); i++){
		ofVec2f pos = myParticles[i].pos;
		if (pos.x < 0) pos.x = ofGetWidth();
		if (pos.x > ofGetWidth()) pos.x = 0;
		if (pos.y < 0) pos.y = ofGetHeight();
		if (pos.y > ofGetHeight()) pos.y = 0;
		myParticles[i].pos = pos;
	}
    
	for (int i = 0; i < myParticles.size(); i++){
        myParticles[i].resetForce();
    }
    /*if (myParticles.size()>500) {
        for (int i = 0; i < myParticles.size(); i++){
            myParticles[i].alignment.strength = 2;
        }
    }*/
    
    
    ///////////////// myParticles 2
    for (int i = 0; i < myParticles2.size(); i++){
        
        //if (keyOption==1) {
        myParticles2[i].cohesion.distance = 1600;
        myParticles2[i].alignment.distance = 1600;
        myParticles2[i].seperation.distance = 1600;
        
        
        myParticles2[i].cohesion.strength = 0.15;
        myParticles2[i].alignment.strength = scaledVol*2;
        myParticles2[i].seperation.strength = 0.015;
        
        myParticles2[i].damping =  0.05f;	

        
        if (myParticles2[i].alignment.strength < 0.15) {
            myParticles2[i].alignment.strength = 0.15;
        }
        
        
	}
    
    
    /////////////////
    
    for (int i = 0; i < myParticles2.size(); i++){
		myParticles2[i].addFlockingForce();
		myParticles2[i].addDampingForce();
		myParticles2[i].update();
	}
    
    // wrap torroidally.
	for (int i = 0; i < myParticles2.size(); i++){
		ofVec2f pos = myParticles2[i].pos;
		if (pos.x < 0) pos.x = ofGetWidth();
		if (pos.x > ofGetWidth()) pos.x = 0;
		if (pos.y < 0) pos.y = ofGetHeight();
		if (pos.y > ofGetHeight()) pos.y = 0;
		myParticles2[i].pos = pos;
	}
    
	for (int i = 0; i < myParticles2.size(); i++){
        myParticles2[i].resetForce();
    }
    /*if (myParticles.size()>500) {
     for (int i = 0; i < myParticles.size(); i++){
     myParticles[i].alignment.strength = 2;
     }
     }*/
    
    ////////////////*************TIME*************////////////////
    
    cout << getHour.currentHour << endl;
    
    if ((getHour.currentHour>7)&&(getHour.currentHour<12)) {
        time_r = ofMap(getHour.currentHour, 7, 13, 153, 249);
        time_g = ofMap(getHour.currentHour, 7, 13, 255, 226);
        time_b = ofMap(getHour.currentHour, 7, 13, 255, 0);
        
        cout << time_r << endl;
    }
    
    if ((getHour.currentHour>12)&&(getHour.currentHour<19)) {
        time_r = ofMap(getHour.currentHour, 12, 19, 249, 255);
        time_g = ofMap(getHour.currentHour, 12, 19, 226, 156);
        time_b = ofMap(getHour.currentHour, 12, 19, 0, 5);
        
        cout << time_r << endl;
    }
    

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	ofSetColor(time_r, time_g, time_b, 200);
	sky.draw(0, 0, 1680, 1050);

    
	for (int i = 0; i < myParticles.size(); i++){
        
        //if (keyOption==1) {
            ofSetColor(0, 0, 0);
            myParticles[i].drawBird();
        //}
      /*  else if(keyOption==2){
            myParticles[i].drawWeed();
        }
        else if(keyOption==3){
            ofSetColor(100, 100, 100);
            ofEnableAlphaBlending();
            myParticles[i].drawSand();
        }*/
    }
    
    for (int i=0; i < myParticles2.size(); i++) {
        ofSetColor(250, 0, 117);
        myParticles2[i].drawBird();
    }
	
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;	
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :) 
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :) 
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
    if (key=='1') {
        keyOption = 1;
    }
    else if(key=='2') {
        keyOption = 2;
    }
    else if(key=='3') {
        keyOption = 3;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
}
