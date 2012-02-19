#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	ofBackground(255, 255, 255);
	
	for (int i = 0; i < 20; i++){
		particle myParticle;
		myParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
		// more interesting with diversity :)
		//myParticle.damping = ofRandom(0.001, 0.05);
		particles.push_back(myParticle);
	}
	frequency = 440;
    position= 0;
    positionAdder = (frequency/44100.0);
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
    
    positionAdder = (frequency/44100.0)*TWO_PI;
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addForce(0.0, 0.28);
		particles[i].addDampingForce();
		particles[i].bounceOffWalls();
		particles[i].update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0x000000);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
        
        if (particles[i].pos.y >= ofGetHeight()) {
            frequency = ofMap(particles[i].pos.x, 0, ofGetWidth(), 29, 1000);
        }
        
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
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
	for (int i = 0; i < particles.size(); i++){
		particles[i].setInitialCondition(mouseX,mouseY,ofRandom(-10,10), ofRandom(-10,10));
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}

void testApp::audioRequested(float *output, int bufferSize, int nChannels){
    
    for(int i = 0; i<bufferSize; i++){
        //modulator = ofMap(sin(positionModulator), -1, 1, 0, 1);
        float sample = sin( position );
        position += positionAdder;
        
        output[i*2+0]= sample / 10;        
    } 
    
    // because sin(..) of very large values is less precise, 
    //let's keep the position variable in the range of 0 to TWO_PI.  
    // it's cyclical!
    while (position>TWO_PI) {       
        position -= TWO_PI;
    }
    
    
    
}
