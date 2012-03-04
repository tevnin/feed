#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    jonnysMovies.loadMovie("http://dl.dropbox.com/u/5491478/EM%20Client/Feed/FeedTest01.mp4");
    jonnysMovies.play();
    
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
			oneOn = !oneOn;
		}else if ( m.getAddress() == "/controller1/button2" ){
			twoOn = !oneOn;
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
		}else if ( m.getAddress() == "/controller2/button2" ){
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
		}else if ( m.getAddress() == "/controller3/button2" ){
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
		}else if ( m.getAddress() == "/controller4/button2" ){
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
    
    jonnysMovies.update();
    
    //api.twitter.com/1/trends/1.json&oauth_consumer_key=mxq8PZhuAlSPNbh4Sc3U0Q&oauth_consumer_secret=9GNnOXCXOVG9S78d15634HGTE5OG4io9q95INQPJc&oauth_token=493376157-eAJOc7MJuZ2rfdYbgjWielZ4gMsHyBjBF5D94yeR&oauth_token_secret=i3ERynzoagxe6FZOqgBh93yqJasCMBvuTmbNbLxIxk
}


//--------------------------------------------------------------
void testApp::draw(){
    jonnysMovies.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (oneOn == true) {
        ofSetColor(255, 255, 255);
        //jonnysMovies.setPaused(false);
        //jonnysMovies.draw(0, 0);
        
        ofSetColor(255, 0, 0);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 200);
        ofSetColor(255, 255, 255);
    }else if (twoOn == true) {
        ofSetColor(255, 255, 255);
        //jonnysMovies.setPaused(true);
        //jonnysMovies.draw(0, 0);
        
        ofSetColor(0, 255, 0);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 100);  
    }else if (threeOn == true) {
        ofSetColor(255, 255, 255);
        //jonnysMovies.setPaused(false);
        //jonnysMovies.draw(0, 0);
        
        ofSetColor(0, 0, 255);
        int n=ofRandom(twitter.size());
        string message = twitter[n]["text"].asString();
        font.drawString(message, 10, 300);  
    }else if (fourOn == true) {
        ofSetColor(255, 255, 255);
        //jonnysMovies.setPaused(true);
        //jonnysMovies.draw(0, 0);
        

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
