#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	ofBackground(255, 255, 255);

	
    // tweet stuff
        franklinBook.loadFont("frabk.ttf", 32);
        franklinBook.setLineHeight(36);

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
//            printHash = false;
    
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


    
    // particle stuff
        for (int i = 0; i < num1/100; i++){
            particle myParticle;
            myParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
            // more interesting with diversity :)
            //myParticle.damping = ofRandom(0.001, 0.05);
            particles.push_back(myParticle);
        }

    
        for (int i = 0; i < num2/100; i++){
            particle myParticle;
            myParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
            // more interesting with diversity :)
            //myParticle.damping = ofRandom(0.001, 0.05);
            particles2.push_back(myParticle);
        }
    
    frequency = 440;
    position= 0;
    positionAdder = (frequency/44100.0);

}


//--------------------------------------------------------------
void testApp::update(){
    
    positionAdder = (frequency/44100.0)*TWO_PI;
    
    if(ofGetFrameNum()%600 == 0){
        for (int i = 0; i < particles.size(); i++){
            particles[i].setInitialCondition(200,300,ofRandom(-10,10), ofRandom(-10,10));
        }
        
        for (int i = 0; i < particles2.size(); i++){
            particles2[i].setInitialCondition(400,500,ofRandom(-10,10), ofRandom(-10,10));
        }
        printHash = false;
    }
    
    	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addForce(0.0, 0.28);
		particles[i].addDampingForce();
		particles[i].bounceOffWalls();
		particles[i].update();
	}

    
	for (int i = 0; i < particles2.size(); i++){
		particles2[i].resetForce();
		particles2[i].addForce(0.0, 0.28);
		particles2[i].addDampingForce();
		particles2[i].bounceOffWalls();
		particles2[i].update();
	}
    
    if(printHash){
        string hashTag = "#RelationshipsShould";
        ofSetHexColor(0x00FF00);
        franklinBook.drawString(hashTag, 100, 100);
    }
}

//--------------------------------------------------------------
void testApp::draw() {
	
    // twitter
        // See this page for all of the ways to access data in a Json::Value
        // http://jsoncpp.sourceforge.net/class_json_1_1_value.html	

        ofSetHexColor(0x00FF00);
    
    // particles
        ofSetColor(0x000000);
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
            
            if (particles[i].pos.y >= ofGetHeight()) {
                frequency = ofMap(particles[i].pos.x, 0, ofGetWidth(), 29, 1000);
            }
            
        }
    
        ofSetColor(0x0000ff);
        
        for (int i = 0; i < particles2.size(); i++){
            particles2[i].draw();
            
            if (particles2[i].pos.y >= ofGetHeight()) {
                frequency = ofMap(particles2[i].pos.x, 0, ofGetWidth(), 29, 1000);
            }
            
        }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
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
    printHash = true;

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

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
