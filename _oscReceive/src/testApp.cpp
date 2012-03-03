#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    font.loadFont("frabk.ttf", 32);
	font.setLineHeight(36);
    
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	ofBackground( 30, 30, 130 );
    
    oneOn = false;
    twoOn = false;
    threeOn = false;
    fourOn = false;

}

//--------------------------------------------------------------
void testApp::update(){

	// hide old messages
	for ( int i=0; i<NUM_MSG_STRINGS; i++ ){
		if ( timers[i] < ofGetElapsedTimef() )
			msg_strings[i] = "";
	}

	// check for waiting messages
	while( receiver.hasWaitingMessages() ){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );

		// check for mouse moved message
        
        //this is the address - put it in as a string
        
        //controller1
		if ( m.getAddress() == "/controller1/button1" ){
			oneOn = true;
		}
		// check for mouse button message
		else if ( m.getAddress() == "/controller1/button2" ){
			twoOn = true;
		}
		else if (m.getAddress() == "/controller1/button3"){
            threeOn = !threeOn;
		}
        else if (m.getAddress() == "/controller1/button4"){
            fourOn = !fourOn;
		}
        else if (m.getAddress() == "/controller1/slider1"){
            sliderOn = !sliderOn;
		}
        
        //controller2
		if ( m.getAddress() == "/controller2/button1" ){
			oneOn = !oneOn;
		}
		// check for mouse button message
		else if ( m.getAddress() == "/controller2/button2" ){
			twoOn = !twoOn;
		}
		else if (m.getAddress() == "/controller2/button3"){
            threeOn = !threeOn;
		}
        else if (m.getAddress() == "/controller2/button4"){
            fourOn = !fourOn;
		}
        else if (m.getAddress() == "/controller2/slider1"){
            sliderOn = !sliderOn;
		}
        
        //controller3
		if ( m.getAddress() == "/controller3/button1" ){
			oneOn = !oneOn;
		}
		// check for mouse button message
		else if ( m.getAddress() == "/controller3/button2" ){
			twoOn = !twoOn;
		}
		else if (m.getAddress() == "/controller3/button3"){
            threeOn = !threeOn;
		}
        else if (m.getAddress() == "/controller3/button4"){
            fourOn = !fourOn;
		}
        else if (m.getAddress() == "/controller3/slider1"){
            sliderOn = !sliderOn;
		}
        
        //controller4
		if ( m.getAddress() == "/controller4/button1" ){
			oneOn = !oneOn;
		}
		// check for mouse button message
		else if ( m.getAddress() == "/controller4/button2" ){
			twoOn = !twoOn;
		}
		else if (m.getAddress() == "/controller4/button3"){
            threeOn = !threeOn;
		}
        else if (m.getAddress() == "/controller4/button4"){
            fourOn = !fourOn;
		}
        else if (m.getAddress() == "/controller4/slider1"){
            sliderOn = !sliderOn;
		}

	}
    
    if (ofGetFrameNum()%3600 == 0) {
        //Twitter
        string url = "http://tweetriver.com/EdibleCircuits/feedmixer.json";
        // Now parse the JSON
        bool parsingSuccessful = twitter.open(url);
        if ( parsingSuccessful ){
            cout << twitter.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
    }
    

}


//--------------------------------------------------------------
void testApp::draw(){

//	string buf;
//	buf = "listening for osc messages on port" + ofToString( PORT );
//	ofDrawBitmapString( buf, 10, 20 );
//
//	// draw mouse state
//	buf = "mouse: " + ofToString( mouseX, 4) +  " " + ofToString( mouseY, 4 );
//	ofDrawBitmapString( buf, 430, 20 );
//	ofDrawBitmapString( mouseButtonState, 580, 20 );
//
//	for ( int i=0; i<NUM_MSG_STRINGS; i++ ){
//		ofDrawBitmapString( msg_strings[i], 10, 40+15*i );
//	}
    
    if (oneOn == true) {
        ofSetColor(255, 0, 0);
        
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 200);        
    }else if (twoOn == true) {
        ofSetColor(0, 255, 0);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 100);  
    }else if (threeOn == true) {
        ofSetColor(0, 0, 255);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 300);  
    }else if (fourOn == true) {
        ofSetColor(255, 255, 255);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 400);  
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
