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
    
    stringSize = 1;


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
		}else {
            oneOn = false;
            twoOn = false;
            threeOn = false;
            fourOn = false;
            //sliderOn = false;
        } 
        if (m.getAddress() == "/controller1/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
            //cout << stringSize << endl;
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
		}
        if (m.getAddress() == "/controller2/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
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
        if (m.getAddress() == "/controller3/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
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
        
        if (m.getAddress() == "/controller4/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
		}
        

	}
    
    if (ofGetFrameNum()%1800 == 0) {
        //Twitter
        string url = "http://tweetriver.com/EdibleCircuits/feedmixer.json?limit=5";
        // Now parse the JSON
        bool parsingSuccessful = twitter.open(url);
        if ( parsingSuccessful ){
            cout << twitter.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        
        int n=ofRandom(twitter.size());
    }
    
    jonnysMovies.update();
}


//--------------------------------------------------------------
void testApp::draw(){
    jonnysMovies.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    
    if (oneOn == true) {
        
        ofSetColor(255, 255, 255);
        string user = "@" + twitter[1]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, ofGetHeight()/5 - 50);
        
        ofSetColor(0,255,255);
        string message = twitter[1]["text"].asString();
        
        float messageWidth = font.stringWidth(message);
        if (messageWidth > ofGetWidth()-10) {
            string line1 = message.substr(0, 70);
            string line2 = message.substr(71, 70);
            
            font.drawString(line1, 10, ofGetHeight()/5);
            font.drawString(line2, 10, ofGetHeight()/5+50);
        }else {
            font.drawString(message, 10, ofGetHeight()/5);
        }
        
        
        ofSetColor(255, 255, 255);
    }else if (twoOn == true) {
        
        ofSetColor(255, 255, 255);
        string user = "@" + twitter[2]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 2*ofGetHeight()/5 - 50);
        
        ofSetColor(255,0,255);
        string message = twitter[2]["text"].asString();
        float messageWidth = font.stringWidth(message);
        if (messageWidth > ofGetWidth()-10) {
            string line1 = message.substr(0, 70);
            string line2 = message.substr(71, 70);
            
            font.drawString(line1, 10, 2*ofGetHeight()/5);
            font.drawString(line2, 10, 2*ofGetHeight()/5+50);
        }else {
            font.drawString(message, 10, 2*ofGetHeight()/5);
        } 
        
        ofSetColor(255, 255, 255);
    }else if (threeOn == true) {
        
        ofSetColor(255, 255, 255);
        string user = "@" + twitter[3]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 3*ofGetHeight()/5 - 50);
        
        ofSetColor(255,255,0);
        string message = twitter[3]["text"].asString();
        float messageWidth = font.stringWidth(message);
        if (messageWidth > ofGetWidth()-10) {
            string line1 = message.substr(0, 70);
            string line2 = message.substr(71, 70);
            
            font.drawString(line1, 10, 3*ofGetHeight()/5);
            font.drawString(line2, 10, 3*ofGetHeight()/5+50);
        }else {
            font.drawString(message, 10, 3*ofGetHeight()/5);
        }
        
        ofSetColor(255, 255, 255);
    }else if (fourOn == true) {
        
        ofSetColor(255, 255, 255);
        string user = "@" + twitter[4]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 4*ofGetHeight()/5 - 50);
        
        ofSetColor(200,200,200);
        string message = twitter[4]["text"].asString();
        float messageWidth = font.stringWidth(message);
        if (messageWidth > ofGetWidth()-10) {
            string line1 = message.substr(0, 70);
            string line2 = message.substr(71, 70);
            
            font.drawString(line1, 10, 4*ofGetHeight()/5);
            font.drawString(line2, 10, 4*ofGetHeight()/5+50);
        }else {
            font.drawString(message, 10, 4*ofGetHeight()/5);
        } 
        
        ofSetColor(255, 255, 255);
    }else if (sliderOn == true){
        ofSetColor(0, 0, 0);
        string feed = "#FEED";
        float mappedSize = ofMap(stringSize, 0, 127, 1, 3);
        
        float feedWidth = font.stringWidth(feed)/2;
        float feedHeight = font.stringHeight(feed)/2;
        
        float screenWidth = ofGetWidth()/2;
        float screenHeight = ofGetHeight()/2;
        
        float x = screenWidth-feedWidth;
        float y = screenHeight-feedHeight;
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
            
            
            ofTranslate(screenWidth,screenHeight);
            ofScale(mappedSize, mappedSize);
            font.drawString(feed, 0-feedWidth, 0);
        
        ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        
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
