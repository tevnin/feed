#include "testApp.h"

// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) { 
	return a->pos.x < b->pos.x; 
}              


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofSetFullscreen(true);
	width=0;
	height=0;
	dist=0;
	
	//frameByframe = false;

	testMovie.loadMovie("movies/around-the-world-sized.mov");
	daft.loadSound("songs/daftpunk.mp3");
	
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 128;
	daft.play();
    
    for (int i = 0; i < 15; i++){
        particle * p = new particle();
        myParticles.push_back(p);
		
        myParticles[i]->pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        myParticles[i]->vel.set(0,0);
    }
    count = 0;
    stageA = true;
    stageB = false;
    stageC = false;
    
    movieW = 1680;
    movieH = 1050;
    
    testMovie.play();


}

//--------------------------------------------------------------
void testApp::update(){
	avg=0;
    testMovie.idleMovie();
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}
    //	daft.setVolume(MIN(5.0f, 1));
	sort( myParticles.begin(), myParticles.end(), comparisonFunction );               // sort them!
	
	
	
	//ofBackground(0,0,0); //Grey background, NY style
	
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
	
        for (int i = 0; i < myParticles.size(); i++){
            for (int j = i-1; j >= 0; j--){
                if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  10) break;
                
                myParticles[i]->addRepulsionForce( ofGetWidth()/2,ofGetHeight()/2,100,fftSmoothed[i]*50);
            }
        }

	
        for (int i = 0; i < myParticles.size(); i++){
            myParticles[i]->addAttractionForce( ofGetWidth()/2,ofGetHeight()/2,10000,2.5);
            myParticles[i]->addRepulsionForce( ofGetWidth()/2,ofGetHeight()/2,100,fftSmoothed[i]*100);
            myParticles[i]->addDampingForce();
            myParticles[i]->update();
        }
   // }  
    
    for (int i = 0; i < nBandsToGet; i++) {
        if ((fftSmoothed[i]*100) > 420 ) {
            for (int i = 0; i < myParticles.size(); i++){
				myParticles[i]->setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}

        }
    }
    
    
    if (count >= 0 && count < 150){
        stageA = true;
        stageB = false;
        stageC = false;
    }
    
    if (count >= 150 && count < 300){
        stageA = false;
        stageB = true;
        stageC = false;
    }
    
    if (count >= 300 && count < 450){
        stageA = false;
        stageB = false;
        stageC = true;
    }

    if (count == 450) {
        count = 0;
    }
    
    count++;

}

//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending();
	ofSetColor(255,255,255,30);
    float pcount = 0;
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    testMovie.draw(0,0, ofGetWidth(), ofGetHeight());
    
    
	
	ofSetColor(255,255,255, 255);
	
	ofSetRectMode(OF_RECTMODE_CENTER);
//    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),20,420);
//    ofDrawBitmapString("count: " + ofToString(count),20,520);

    
    if (stageA == true){

        for (int h=0; h<myParticles.size(); h++) {
            for (int i=0; i < (int)movieW/128; i++) {
                for (int j=0; j < (int)movieH/128;j++) {
                    width = 128;
                    height = 120;
                    testMovie.getTextureReference().bind();
                    ofPushMatrix();
                    ofTranslate(0,0,0);
                    glBegin(GL_QUADS);
                    
                        glTexCoord2f(myParticles[h]->pos.x, myParticles[i]->pos.y);
                        glVertex2f(myParticles[h]->pos.x, myParticles[i]->pos.y);
                        glTexCoord2f(myParticles[h]->pos.x, (myParticles[i]->pos.y+height));
                        glVertex2f(myParticles[h]->pos.x, (myParticles[i]->pos.y+height));
                        glTexCoord2f((myParticles[h]->pos.x+width),(myParticles[i]->pos.y+height));
                        glVertex2f((myParticles[h]->pos.x+width),(myParticles[i]->pos.y+height));
                        glTexCoord2f((myParticles[h]->pos.x+width),myParticles[i]->pos.y);
                        glVertex2f((myParticles[h]->pos.x+width),myParticles[i]->pos.y);    
                    
                    glEnd();
                    ofRect( myParticles[h]->pos.x, myParticles[i]->pos.y,150,150);
                            
                    testMovie.getTextureReference().unbind();
                    
                    
                    dist = ofDist(myParticles[i]->pos.x, myParticles[i]->pos.y, myParticles[j]->pos.x, myParticles[j]->pos.y);
                    if(dist < 600) {
                        
                        pcount++;
                        float alpha = ofMap(dist,0, 180, 0, 30);
                        ofSetColor(255, 255, 255,30-alpha);
                        
                        
                    }
                    if(pcount >=80) {
                        
                        float mapfft = ofMap(avg, 0, .03, 20,100, true);
                        pcount = 0;
                    }
                    ofPopMatrix();
                    
               }
            }
        }
    }
    
    if (stageB == true) {
        for (int h=0; h<myParticles.size(); h++) {
            for (int i=0; i < (int)ofGetWidth()/128; i++) {
                for (int j=0; j < (int)ofGetHeight()/128;j++) {
                    width=128-(fftSmoothed[i] * 350);
                    height=120-(fftSmoothed[i] * 200);
                    //width = 128;
                    //height = 120;
                    
                    //ofSetColor(0, 0, 0, 80);
                    //ofRect(myParticles[h]->pos.x-5, myParticles[h]->pos.y-5, width+10, height+10);
                    
                    ofSetColor(255,255,255, 255);
                    testMovie.getTextureReference().bind();
                    glBegin(GL_QUADS);
                    
                    glTexCoord2f(myParticles[h]->pos.x,myParticles[h]->pos.y); 
                    glVertex2f(myParticles[h]->pos.x+100, myParticles[h]->pos.y+100); 
                    glTexCoord2f(myParticles[h]->pos.x,(myParticles[h]->pos.y+height));
                    glVertex2f(myParticles[h]->pos.x+100, (myParticles[h]->pos.y+height+100));
                    glTexCoord2f((myParticles[h]->pos.x+width),(myParticles[h]->pos.y+height));
                    glVertex2f((myParticles[h]->pos.x+width)+100,(myParticles[h]->pos.y+height)+100);              
                    glTexCoord2f((myParticles[h]->pos.x+width),myParticles[h]->pos.y);
                    glVertex2f((myParticles[h]->pos.x+width)+100,myParticles[h]->pos.y+100);                
                    
                    glEnd(); 
                    ofRect(myParticles[h]->pos.x-5, myParticles[h]->pos.y-5, width+10, height+10);
                    testMovie.getTextureReference().unbind();
                    
                }
            }
        }
    }

    
    if (stageC == true){
        for (int h=0; h<myParticles.size(); h++) {
            for (int i=0; i < (int)movieW/128; i++) {
                for (int j=0; j < (int)movieH/128;j++) {
                    width = 128;
                    height = 120;
                    
                        testMovie.getTextureReference().bind();
                        //ofPushMatrix();    
                            //ofTranslate(0,0,0);
                            glBegin(GL_QUADS);
                            
                            glTexCoord2f(myParticles[h]->pos.x, myParticles[h]->pos.y);
                            glVertex2f(myParticles[h]->pos.x, myParticles[h]->pos.y);
                            glTexCoord2f(myParticles[h]->pos.x, (myParticles[h]->pos.y+height));
                            glVertex2f(myParticles[h]->pos.x, (myParticles[h]->pos.y+height)); 
                            glTexCoord2f((myParticles[h]->pos.x+width),(myParticles[h]->pos.y+height));
                            glVertex2f((myParticles[h]->pos.x+width),(myParticles[h]->pos.y+height));
                            glTexCoord2f((myParticles[h]->pos.x+width),myParticles[h]->pos.y);
                            glVertex2f((myParticles[h]->pos.x+width),myParticles[h]->pos.y);   
                            
                            glEnd();
                            ofRect( myParticles[h]->pos.x, myParticles[i]->pos.y,150,150);
                            //ofPopMatrix();
                    testMovie.getTextureReference().unbind();
                    
                    
                }
            }
        }
    }
    
    
       
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch (key){
			
		case ' ':
            ofToggleFullscreen();
            break;
            
        case 'r':
			// reposition everything: 
			for (int i = 0; i < myParticles.size(); i++){
				myParticles[i]->setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}
			break;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
