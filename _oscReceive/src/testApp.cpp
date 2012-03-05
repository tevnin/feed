#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    jonnysMovies.loadMovie("http://dl.dropbox.com/u/5491478/EM%20Client/Feed/FeedTest01.mp4");
    jonnysMovies.play();
    
    font.loadFont("Oswald-Bold.ttf", 32);
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

    jonnysMovies.idleMovie();
    
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
		}else if ( m.getAddress() == "/controller1/button2" ){
			twoOn = true;
		}else if (m.getAddress() == "/controller1/button3"){
            threeOn = true;
		}else if (m.getAddress() == "/controller1/button4"){
            fourOn = true;
		}else if (m.getAddress() == "/controller1/slider1"){
            sliderOn = true;
		}else {
            oneOn = false;
            twoOn = false;
            threeOn = false;
            fourOn = false;
            sliderOn = false;
        }
        
        //controller2
		if ( m.getAddress() == "/controller2/button1" ){
			oneOn = true;
		}else if ( m.getAddress() == "/controller2/button2" ){
			twoOn = true;
		}else if (m.getAddress() == "/controller2/button3"){
            threeOn = true;
		}else if (m.getAddress() == "/controller2/button4"){
            fourOn = true;
		}else if (m.getAddress() == "/controller2/slider1"){
            sliderOn = true;
        }
        
        //controller3
		if ( m.getAddress() == "/controller3/button1" ){
			oneOn = true;
		}else if ( m.getAddress() == "/controller3/button2" ){
			twoOn = true;
		}
		else if (m.getAddress() == "/controller3/button3"){
            threeOn = true;
		}
        else if (m.getAddress() == "/controller3/button4"){
            fourOn = true;
		}
        else if (m.getAddress() == "/controller3/slider1"){
            sliderOn = true;
		}
        
        //controller4
		if ( m.getAddress() == "/controller4/button1" ){
			oneOn = true;
		}else if ( m.getAddress() == "/controller4/button2" ){
			twoOn = true;
		}
		else if (m.getAddress() == "/controller4/button3"){
            threeOn = true;
		}
        else if (m.getAddress() == "/controller4/button4"){
            fourOn = true;
		}
        else if (m.getAddress() == "/controller4/slider1"){
            sliderOn = true;
		}
        

	}
    
    if (ofGetFrameNum()%3600 == 0) {
        //Twitter
        string url = "http://tweetriver.com/EdibleCircuits/feedmixer.json?limit=16";
        // Now parse the JSON
        bool parsingSuccessful = twitter.open(url);
        if ( parsingSuccessful ){
            cout << twitter.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
    }
    
    jonnysMovies.update();
}


//--------------------------------------------------------------
void testApp::draw(){
    jonnysMovies.draw(0, 0, ofGetWidth(), ofGetHeight());
    int n=ofRandom(twitter.size());
    
    if (oneOn == true) {
        
        ofSetColor(0,255,255);
        string message = twitter[n]["text"].asString();
        //vector<string> split = ofSplitString(message, "sxsw");
        font.drawString(message, 10, ofGetHeight()/5);
        
        ofSetColor(255, 255, 255);
    }else if (twoOn == true) {
        
        ofSetColor(255,0,255);
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 2*ofGetHeight()/5); 
        
        ofSetColor(255, 255, 255);
    }else if (threeOn == true) {
        
        ofSetColor(255,255,0);
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 3*ofGetHeight()/5); 
        
        ofSetColor(255, 255, 255);
    }else if (fourOn == true) {
        
        ofSetColor(0,0,0);
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 4*ofGetHeight()/5);  
        
        ofSetColor(255, 255, 255);
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
