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
        
        string url1 = "http://tweetriver.com/EdibleCircuits/feedmixer.jsonn";

    
        

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

}


//--------------------------------------------------------------
void testApp::update(){
    
        printHash = false;
     
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
        ofSetColor(0x0000ff);
        

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


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
