#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    //LOAD IN JONNY'S VIDEO
    //vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    colorImg.allocate(320,240);
    
    //jonnysMovies.loadMovie("http://dl.dropbox.com/u/5491478/EM%20Client/Feed/FeedTest01.mp4");
    //jonnysMovies.play();
    
    font.loadFont("Oswald-Bold.ttf", 32);
	font.setLineHeight(36);
    
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );


	ofBackground( 30, 30, 130 );
    
    //initialize variables
    oneOn = false;
    twoOn = false;
    threeOn = false;
    fourOn = false;
    
    stringSize = 1;
    tweetNum = 0;


}

//--------------------------------------------------------------
void testApp::update(){
    bool bNewFrame = false;
    
    vidGrabber.grabFrame();
    //bNewFrame = vidGrabber.isFrameNew();

    
	//if (bNewFrame){
        
        colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
        
  	//}

    //jonnysMovies.idleMovie();


	// check for waiting messages
	while( receiver.hasWaitingMessages() ){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );

		//check for message

        //controller1
		if ( m.getAddress() == "/controller1/button1" ){
			tweetNum = 0;
            oneOn = true;
            
		}else if ( m.getAddress() == "/controller1/button2" ){
			tweetNum = 1;
            oneOn = true;
            
		}else if (m.getAddress() == "/controller1/button3"){
            tweetNum = 3;
            oneOn = true;
            
		}else if (m.getAddress() == "/controller1/button4"){
            tweetNum = 4;
            oneOn = true;
            
		}else {
            oneOn = false;
            twoOn = false;
            threeOn = false;
            fourOn = false;
        } 
        if (m.getAddress() == "/controller1/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
            //cout << stringSize << endl;
		}
        
        //controller2
		if ( m.getAddress() == "/controller2/button1" ){
			tweetNum = 5;
            twoOn = true;
		}else if ( m.getAddress() == "/controller2/button2" ){
			tweetNum = 6;
            twoOn = true;
		}else if (m.getAddress() == "/controller2/button3"){
            tweetNum = 7;
            twoOn = true;
		}else if (m.getAddress() == "/controller2/button4"){
            tweetNum = 8;
            twoOn = true;
		}
        if (m.getAddress() == "/controller2/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
        }
        
        //controller3
		if ( m.getAddress() == "/controller3/button1" ){
            tweetNum = 9;
			threeOn = true;
		}else if ( m.getAddress() == "/controller3/button2" ){
            tweetNum = 10;
			threeOn = true;
		}
		else if (m.getAddress() == "/controller3/button3"){
            tweetNum =11;
            threeOn = true;
		}
        else if (m.getAddress() == "/controller3/button4"){
            tweetNum = 12;
            threeOn = true;
		}
        if (m.getAddress() == "/controller3/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
		}
        
        //controller4
		if ( m.getAddress() == "/controller4/button1" ){
            tweetNum = 13;
			fourOn = true;
		}else if ( m.getAddress() == "/controller4/button2" ){
            tweetNum = 14;
			fourOn = true;
		}
		else if (m.getAddress() == "/controller4/button3"){
            tweetNum = 15;
            fourOn = true;
		}
        else if (m.getAddress() == "/controller4/button4"){
            tweetNum = 16;
            fourOn = true;
		}
        
        if (m.getAddress() == "/controller4/slider1"){
            sliderOn = true;
            stringSize = m.getArgAsInt32( 0 );
		}
        

	}
        
    //refresh tweets every 30 seconds
    if (ofGetFrameNum()%1800 == 0) {
        //Twitter
        string url = "http://tweetriver.com/EdibleCircuits/feedmixer2.json?limit=20";
        // Now parse the JSON
        bool parsingSuccessful = twitter.open(url);
        if ( parsingSuccessful ){
            cout << twitter.getRawString() << endl;
        }else{
            cout  << "Failed to parse JSON" << endl;
        }
        
        int n=ofRandom(twitter.size());
    }
    
    //jonnysMovies.update();
}


//--------------------------------------------------------------
void testApp::draw(){
    //jonnysMovies.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetHexColor(0xffffff);
	colorImg.draw(0,0,ofGetWidth(),ofGetHeight());
    if (oneOn == true) {
        
        ofSetColor(255, 255, 255);
        string user = "@" + twitter[tweetNum]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, ofGetHeight()/5 - 50);
        
        ofSetColor(0,255,255);
        string message = twitter[tweetNum]["text"].asString();
        
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
        string user = "@" + twitter[tweetNum]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 2*ofGetHeight()/5 - 50);
        
        ofSetColor(255,0,255);
        string message = twitter[tweetNum]["text"].asString();
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
        string user = "@" + twitter[tweetNum]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 3*ofGetHeight()/5 - 50);
        
        ofSetColor(255,255,0);
        string message = twitter[tweetNum]["text"].asString();
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
        string user = "@" + twitter[tweetNum]["user"]["screen_name"].asString() + ":";
        font.drawString(user, 10, 4*ofGetHeight()/5 - 50);
        
        ofSetColor(200,200,200);
        string message = twitter[tweetNum]["text"].asString();
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
        string feed = "#FEEDmixer";
        float mappedSize = ofMap(stringSize, 0, 127, 1, 5);
        
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
    if(key == 's'){
        vidGrabber.videoSettings();
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
