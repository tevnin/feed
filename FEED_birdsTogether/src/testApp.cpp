#include "testApp.h"
#include "particle.h"
#include "ofxTimeUtils.h"

//--------------------------------------------------------------
void testApp::setup(){

    //ofSetFrameRate(60);

	int proportion = 100;
	setupBins(ofGetWidth(), ofGetHeight(), 30,30);
	
	ofBackground(255, 255, 255);
	ofSetCircleResolution(6);
    
    // Loading Fonts and Images
    
    sky.loadImage("sunset_bw_1920.jpg");
    Archer.loadFont("Oswald-Regular.ttf", 14);
    Archer.setLineHeight(22);


	ofSetVerticalSync(true); // turned off, to see frameRateChanges...
    
    //***************>>>>>>>>TWITTER>>>>>>>>***************//
        
    // Twitter API: http://dev.twitter.com/doc/get/trends/current
    
    url1 = "http://tweetriver.com/EdibleCircuits/sxswtrend1/meta.json";
    url2 = "http://tweetriver.com/EdibleCircuits/sxswtrend2/meta.json";
    url3 = "http://tweetriver.com/EdibleCircuits/sxswtrend3/meta.json";
    url4 = "http://tweetriver.com/EdibleCircuits/sxswtrend4/meta.json";
    url5 = "http://tweetriver.com/EdibleCircuits/sxswtrend5/meta.json";

	
    // Now parse the JSON
    
    //TREND 1------------------------------/////////////////////
    bool parsing1Successful = result1.open(url1);
    if ( parsing1Successful ){
        //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend1 = result1["count"]["approved"];
    oldNum1 = trend1.asInt();
    //cout << num/100 << endl;
    //printHash = false;
    
    
    //TREND 2------------------------------/////////////////////
    bool parsing2Successful = result2.open(url2);
    if ( parsing2Successful ){
    //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend2 = result2["count"]["approved"];
    oldNum2 = trend2.asInt();
    //cout << num/100 << endl;
    printHash = false;
    
    //TREND 3------------------------------/////////////////////
    bool parsing3Successful = result3.open(url3);
    if ( parsing3Successful ){
        //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend3 = result3["count"]["approved"];
    oldNum3 = trend3.asInt();
    //cout << num/100 << endl;
    printHash = false;
    
    //TREND 4------------------------------/////////////////////
    bool parsing4Successful = result4.open(url4);
    if ( parsing4Successful ){
        //cout << result.getRawString() << endl;
    }else{
        cout  << "Failed to parse JSON" << endl;
    }
    ofxJSONElement trend4 = result4["count"]["approved"];
    oldNum4 = trend4.asInt();
    //cout << num/100 << endl;
    printHash = false;
	

    if ((oldNum1/proportion)>800) {
        oldNum1 = 20000;
    }
    
    if ((oldNum2/proportion)>800) {
        oldNum2 = 20000;
    }
    
    if ((oldNum3/proportion)>800) {
        oldNum3 = 20000;
    }
    
    if ((oldNum4/proportion)>800) {
        oldNum4 = 20000;
    }
    
    
    //PARTICLESSSSSSS------------------------------/////////////////////
    for (int i = 0; i < oldNum1/proportion; i++){
        particle newParticle;
        newParticle.setInitialCondition(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticles[i].damping = ofRandom(0.001, 0.05);
        myParticles.push_back(newParticle);
    }
    
    
    for (int i = 0; i < oldNum2/proportion; i++){
        particle newParticle;
        newParticle.setInitialCondition(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticles[i].damping = ofRandom(0.001, 0.05);
        myParticles2.push_back(newParticle);
    }
    
    for (int i = 0; i < oldNum3/proportion; i++){
        particle newParticle;
        newParticle.setInitialCondition(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticles[i].damping = ofRandom(0.001, 0.05);
        myParticles3.push_back(newParticle);
    }
    
    for (int i = 0; i < oldNum4/proportion; i++){
        particle newParticle;
        newParticle.setInitialCondition(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(-10,10), ofRandom(-10,10));
        // more interesting with diversity :)
        //myParticles[i].damping = ofRandom(0.001, 0.05);
        myParticles4.push_back(newParticle);
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
    
    /*
	//trend 1------------------------------/////////////////////
	for (int i = 0; i < myParticles.size(); i++){
		computeBinPosition( myParticles[i].pos.x, myParticles[i].pos.y,  &(myParticles[i].bitFlagW), &(myParticles[i].bitFlagH));
	}
    
    //trend 2------------------------------/////////////////////
    for (int i = 0; i < myParticles2.size(); i++){
		computeBinPosition( myParticles2[i].pos.x, myParticles2[i].pos.y,  &(myParticles2[i].bitFlagW), &(myParticles2[i].bitFlagH));
	}
    
    //trend 3------------------------------/////////////////////
    for (int i = 0; i < myParticles3.size(); i++){
		computeBinPosition( myParticles3[i].pos.x, myParticles3[i].pos.y,  &(myParticles3[i].bitFlagW), &(myParticles3[i].bitFlagH));
	}
    */
	

	
	int count = 0;
	
    //trend 1------------------------------/////////////////////
    for (int i = 0; i < myParticles.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles[i].addRepulsionForce( myParticles[j],15,8); 
                myParticles[i].addForFlocking( myParticles[j]);

				count ++;
			}
        }
    }
    
    //trend 2------------------------------/////////////////////
    for (int i = 0; i < myParticles2.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles2[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles2[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles2[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles2[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles2[i].addRepulsionForce( myParticles2[j],15,8); 
                myParticles2[i].addForFlocking( myParticles2[j]);
                
				count ++;
			}
        }
    }
    
    //trend 3------------------------------/////////////////////
    for (int i = 0; i < myParticles3.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles3[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles3[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles3[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles3[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles3[i].addRepulsionForce( myParticles3[j],15,8); 
                myParticles3[i].addForFlocking( myParticles3[j]);
                
				count ++;
			}
        }
    }
    
    //trend 4------------------------------/////////////////////
    for (int i = 0; i < myParticles4.size(); i++){
		
		unsigned int bitFlagH_pta = myParticles4[i].bitFlagH;
		unsigned int bitFlagW_pta = myParticles4[i].bitFlagW;
		
        for (int j = 0; j < i; j++){
			
			unsigned int bitFlagH_ptb = myParticles4[j].bitFlagH;
			unsigned int bitFlagW_ptb = myParticles4[j].bitFlagW;
			
			if ((bitFlagW_pta & bitFlagW_ptb) && (bitFlagH_pta & bitFlagH_ptb)){
				myParticles4[i].addRepulsionForce( myParticles4[j],15,8); 
                myParticles4[i].addForFlocking( myParticles4[j]);
                
				count ++;
			}
        }
    }
	
	printf("%i \n", count);
    

    
    if(ofGetFrameNum()%2000 == 0){
        // Now parse the JSON
        bool parsing1Successful = result1.open(url1);
        if ( parsing1Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend1 = result1["count"]["approved"];
        
        newNum1 = trend1.asInt();
        
        newNum1 = int(newNum1 / proportion);
        oldNum1 = int(oldNum1 / proportion);
        
        if (newNum1<oldNum1) {
            //newNum1 = oldNum1; 
            numDiff1 = 0;
        }
        else {
            numDiff1 = newNum1 - oldNum1;
        }
        
        if ((numDiff1>400)||(numDiff1<0)) {
            numDiff1 = 0;
        }
        for (int i = 0; i < numDiff1; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles.push_back(p);
        }
        
        // Now parse the JSON
        bool parsing2Successful = result2.open(url2);
        if ( parsing1Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend2 = result2["count"]["approved"];
        
        newNum2 = trend2.asInt();
        
        newNum2 = newNum2 / proportion;
        oldNum2 = oldNum2 / proportion;
        
        if (newNum2<oldNum2) {
            //newNum1 = oldNum1; 
            numDiff2 = 0;
        }
        else {
            numDiff2 = newNum2 - oldNum2;
        }
        
        if ((numDiff2>400)||(numDiff2<0)) {
            numDiff2 = 0;
        }
        for (int i = 0; i < numDiff2; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles.push_back(p);
        }
        cout << "newnum2=" << endl;
        cout << newNum2 << endl;
        
        
        // Now parse the JSON trend 3!!!!!!!!!!!!!!!
        bool parsing3Successful = result3.open(url3);
        if ( parsing3Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend3 = result3["count"]["approved"];
        
        newNum3 = trend3.asInt();
        
        newNum3 = newNum3 / proportion;
        oldNum3 = oldNum3 / proportion;
        
        if (newNum3<oldNum3) {
            //newNum3 = oldNum3; 
            numDiff3 = 0;
        }
        else {
            numDiff3 = newNum3 - oldNum3;
        }
        
        if ((numDiff3>400)||(numDiff3<0)) {
            numDiff3 = 0;
        }
        for (int i = 0; i < numDiff3; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles3.push_back(p);
        }
        
        // Now parse the JSON trend 4!!!!!!!!!!!!!!!
        bool parsing4Successful = result4.open(url4);
        if ( parsing4Successful ){
            //cout << result.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        ofxJSONElement trend4 = result4["count"]["approved"];
        
        newNum4 = trend4.asInt();
        
        newNum4 = newNum4 / proportion;
        oldNum4 = oldNum4 / proportion;
        
        if (newNum4<oldNum4) {
            newNum4 = oldNum4; 
            numDiff4 = 0;
        }
        else {
            numDiff4 = newNum4 - oldNum4;
        }
        
        if ((numDiff4>400)||(numDiff4<0)) {
            numDiff4 = 0;
        }
        for (int i = 0; i < numDiff4; i++){
            particle p;
            p.pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p.vel.set(0,0);
            myParticles4.push_back(p);
        }

    }
    
    ///////////////// myParticles 1 /////////////////
    for (int i = 0; i < myParticles.size(); i++){
        
        //if (keyOption==1) {
            myParticles[i].cohesion.distance = 1600;
            myParticles[i].alignment.distance = 1600;
            myParticles[i].seperation.distance = 1600;
            
            
            myParticles[i].cohesion.strength = 0.25;
            myParticles[i].alignment.strength = scaledVol;
            myParticles[i].seperation.strength = 0.015;
            
            myParticles[i].damping =  0.06f;
         
        if (myParticles[i].alignment.strength < 0.15) {
            myParticles[i].alignment.strength = 0.15;
        }        
	}
 
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
    
    /*if (myParticles.size()==200) {
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
        
        
        myParticles2[i].cohesion.strength = 0.25;
        myParticles2[i].alignment.strength = scaledVol*2;
        myParticles2[i].seperation.strength = 0.015;
        
        myParticles2[i].damping =  0.06f;	

        
        if (myParticles2[i].alignment.strength < 0.15) {
            myParticles2[i].alignment.strength = 0.15;
        }
	}

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
    
    
    ///////////////// myParticles 3
    for (int i = 0; i < myParticles3.size(); i++){
        
        //if (keyOption==1) {
        myParticles3[i].cohesion.distance = 1600;
        myParticles3[i].alignment.distance = 1600;
        myParticles3[i].seperation.distance = 1600;
        
        
        myParticles3[i].cohesion.strength = 0.25;
        myParticles3[i].alignment.strength = scaledVol*2;
        myParticles3[i].seperation.strength = 0.015;
        
        myParticles3[i].damping =  0.06f;	
        
        
        if (myParticles3[i].alignment.strength < 0.15) {
            myParticles3[i].alignment.strength = 0.15;
        }
        
        
	}
    
    for (int i = 0; i < myParticles3.size(); i++){
		myParticles3[i].addFlockingForce();
		myParticles3[i].addDampingForce();
		myParticles3[i].update();
	}
    
    // wrap torroidally.
	for (int i = 0; i < myParticles3.size(); i++){
		ofVec2f pos = myParticles3[i].pos;
		if (pos.x < 0) pos.x = ofGetWidth();
		if (pos.x > ofGetWidth()) pos.x = 0;
		if (pos.y < 0) pos.y = ofGetHeight();
		if (pos.y > ofGetHeight()) pos.y = 0;
		myParticles3[i].pos = pos;
	}
    
	for (int i = 0; i < myParticles3.size(); i++){
        myParticles3[i].resetForce();
    }
    /*if (myParticles.size()>500) {
     for (int i = 0; i < myParticles.size(); i++){
     myParticles[i].alignment.strength = 2;
     }
     }*/
    
    ///////////////// myParticles 4
    for (int i = 0; i < myParticles4.size(); i++){
        
        
        myParticles4[i].cohesion.distance = 1600;
        myParticles4[i].alignment.distance = 1600;
        myParticles4[i].seperation.distance = 1600;
        
        
        myParticles4[i].cohesion.strength = 0.25;
        myParticles4[i].alignment.strength = scaledVol*2;
        myParticles4[i].seperation.strength = 0.015;
        
        myParticles4[i].damping =  0.06f;	
        
        
        if (myParticles4[i].alignment.strength < 0.15) {
            myParticles4[i].alignment.strength = 0.15;
        }
        
        
	}
    
    for (int i = 0; i < myParticles4.size(); i++){
		myParticles4[i].addFlockingForce();
		myParticles4[i].addDampingForce();
		myParticles4[i].update();
	}
    
    // wrap torroidally.
	for (int i = 0; i < myParticles4.size(); i++){
		ofVec2f pos = myParticles4[i].pos;
		if (pos.x < 0) pos.x = ofGetWidth();
		if (pos.x > ofGetWidth()) pos.x = 0;
		if (pos.y < 0) pos.y = ofGetHeight();
		if (pos.y > ofGetHeight()) pos.y = 0;
		myParticles4[i].pos = pos;
	}
    
	for (int i = 0; i < myParticles4.size(); i++){
        myParticles4[i].resetForce();
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
    }
    
    else if ((getHour.currentHour>12)&&(getHour.currentHour<19)) {
        time_r = ofMap(getHour.currentHour, 12, 19, 249, 255);
        time_g = ofMap(getHour.currentHour, 12, 19, 226, 156);
        time_b = ofMap(getHour.currentHour, 12, 19, 0, 5);
    }
    
    else {
        time_r = 53;
        time_g = 114;
        time_b = 185;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	ofSetColor(time_r, time_g, time_b, 200);
	sky.draw(0, 0, 1680, 1050);
   

    
	for (int i = 0; i < myParticles.size(); i++){
        ofSetColor(0, 0, 0);
        //ofDrawBitmapString("#WhatIMissMost", myParticles[0].pos.x+10, myParticles[0].pos.y+10);
        Archer.drawString("#WhatIMissMost", myParticles[0].pos.x+30, myParticles[0].pos.y+30);
        myParticles[i].drawBird();
    }
    
    for (int i=0; i < myParticles2.size(); i++) {
        ofSetColor(250, 0, 117);
        Archer.drawString("#10beautifulpeopleifollow", myParticles2[0].pos.x+30, myParticles2[0].pos.y+30);
        myParticles2[i].drawBird();
    }
	
    for (int i=0; i < myParticles3.size(); i++) {
        ofSetColor(255, 242, 0);
        Archer.drawString("#SomethingILearnedLongAgo", myParticles3[0].pos.x+10, myParticles3[0].pos.y+10);
        myParticles3[i].drawBird();
    }
    
    for (int i=0; i < myParticles4.size(); i++) {
        ofSetColor(255, 255, 255);
        Archer.drawString("#Patricia Heaton", myParticles4[0].pos.x+10, myParticles4[0].pos.y+10);
        myParticles4[i].drawBird();
    }
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("one bird = 100 tweets", ofGetWidth()-200, ofGetHeight()-50);
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;	
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2]*0.5;
        
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
