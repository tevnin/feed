#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	spot.loadImage("dand.png");
    spot2.loadImage("dand2.png");
    bg.loadImage("bg1.png");
	
	for (int i = 0; i < 40; i++){
		particle myParticle;
		float randomAngle = ofRandom(0, TWO_PI);
		myParticle.setInitialCondition(500,500,cos(randomAngle)/100,sin(randomAngle)/100);		
        myParticle.img = &spot;
        myParticle.img1 = &spot2;
		particles.push_back(myParticle);
		
	}
    
    VF.setupField(60,40,ofGetWidth(), ofGetHeight());
    
	
	bRepel		= true;
	radius		= 40;
	strength	= 0.5f; 
    
    drawingStyle = 0;
	bFade = false;
	
    moveX = 600;
    moveY = 200;
    
    makeWishbool = false;
	
	ofBackground(60, 60, 60);

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
    

	
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
        
        // get the force from the vector field: 
		ofVec2f frc;
		frc = VF.getForceFromPos(particles[i].pos.x, particles[i].pos.y);
		particles[i].addForce(frc.x, frc.y);
		particles[i].addDampingForce();
		particles[i].update();
	}
	
	
	if (bFade == true) VF.fadeField(0.99f);

	
	
	for (int i = 0; i < particles.size(); i++){
		
		particles[i].addAttractionForce(500, 500, 1000, 0.9);
		
	
		for (int j = 0; j < i; j++){
			if (bRepel){
				particles[i].addRepulsionForce(particles[j], 100, 0.9f);
			} else {
				particles[i].addAttractionForce(particles[j], 130, 0.05);
			}
		}
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
        particles[i].rotateFromPoint(499, 508);
		particles[i].update();
	}
    
//    printf("%i %i \n", mouseX, mouseY);
    
    //lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 4.0, true);
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    
    if (smoothedVol> 0.05) {
        makeWish();
    }
    
    if (makeWishbool){
        drawCounter ++;
        
        if (drawCounter > 380){
            backToDandelion();
            VF.clear();
            
            //makeWishbool = false;
            
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
	
	ofEnableAlphaBlending();
	//ofSetColor(0,130,130, 200);
	VF.draw();
    
   // ofSetColor(0,130,130, 200);
    bg.draw(0,0);
    
    
    //ofSetColor(255,255,255,255);
	
	
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
	
   
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	string reportString =	"(space) = reset\n(a/s) strength = " + ofToString(strength) + 
							"\n(z/x) radius = " + ofToString(radius) + 
							"\n(r) toggle mode = " + (bRepel ? "repelling" : "attracting");
	
	ofSetColor(40,40,0);
	//ofRect(10,10,70,80);
	ofSetColor(255,255,255);
	//ofDrawBitmapString(reportString, 30, 30);
	
    
    string mousepos ="mousex"+ ofToString(mouseX) + 
    "mouseY" + ofToString(mouseY) ;
    //ofDrawBitmapString(mousepos, 30, 100);
    
    //ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 30, 200);
    
    float newvol;
    newvol = scaledVol * 100.0, 0;
    
   // ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(smoothedVol), 30, 300);
    
   // ofDrawBitmapString("counter " + ofToString(drawCounter), 30, 500);
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':
			// reposition everything: 
			for (int i = 0; i < particles.size(); i++){
                float randomAngle = ofRandom(0, TWO_PI);
                particles[i].setInitialCondition(500,500,cos(randomAngle)/100,sin(randomAngle)/100);
			}
            VF.clear();
			break;
		case 'r':
			//bRepel = !bRepel;
            backToDandelion();
            
			break;
            
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

//--------------------------------------------------------------
void testApp::makeWish(){
       
    
      for (int i=0; i<310; i++) {
          moveX++;
          moveY++;
        
        }
        makeWishbool = true;
  
        float diffx = moveX - prevFluffX;
        float diffy = moveY - prevFluffY;
        //radius = diffx*0.5;
        
        VF.addVectorCircle(moveX, moveY, diffx*0.3, diffy*-0.1, 440, 0.08f);
    
        //VF.addInwardCircle(moveX, moveY, 600, 0.09f);
    float moveCircle = 1300;
//    if(moveX > 800){
//        
//        moveCircle -= 100;
//        VF.addClockwiseCircle(moveCircle, 300, 700, 0.07f);
//    }

        prevFluffX=moveX;
        prevFluffY=moveY;

  }

//--------------------------------------------------------------
void testApp::backToDandelion(){
    
    VF.clear();
    
    float diffx = moveX - prevFluffX;
    float diffy = moveY - prevFluffY;
    //radius = diffx*0.5;
    
    VF.addVectorCircle(500, 500, diffx*-0.5, diffy*-0.1, 3000, 1.5f);
    
    makeWishbool = false;
    drawCounter = 0;
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


