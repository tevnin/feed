#include "testApp.h"
void testApp::setup(){
	
	//receiver.setup( PORT );
	
	
    frameW  = 640;
    frameH  = 480;
    nFrames = 0;
    
	
	//kinect
	kinect.init();
	kinect.setVerbose(true);
	kinect.open();
	kinectSource = &kinect;
	angle = -40;
	kinect.setCameraTiltAngle(angle);
	pointCloudRotationY = 180;
	bDrawPointCloud = false;
	
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	
    //vid.initGrabber(frameW,frameH);
	
    gifEncoder.setup(frameW, frameH, .25, 256);
    //ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
    
    ofBackground(50, 40, 50);
	
	
	ofDirectory dir;
	dir.listDir("");
	for (int j = 0; j < dir.size(); j++){
		
		string fileName = dir.getPath(j);
		cout << fileName << endl;
		ofImage * temp = new ofImage;
		temp->loadImage(dir.getPath(j));
		data.push_back(temp);
	}
	
	ofSetVerticalSync(true);
	
	recordingCount = 0;
	//ofSetFrameRate(60);
	//player.loadMovie("test.gif");
    counter = 0;
    capture = false;
}

//--------------------------------------------------------------
void testApp::update(){ 
	
	
    //vid.update();
	kinect.update();
	//player.update();
/*	
	//osc
	// check for waiting messages
	while( receiver.hasWaitingMessages() ){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		//check for message
		
        //controller1
        
                
        if(capture == true){
            captureFrame();
            capture = false;
        } 
            
                      
        
		if ( m.getAddress() == "/controller1/button1" && m.getArgAsInt32( 0 ) == 0){
            capture = true;
            counter++;
        }else if ( m.getAddress() == "/controller1/button2" && m.getArgAsInt32( 0 ) == 0){
            capture = true;
			counter++;
		}else if (m.getAddress() == "/controller1/button3" && m.getArgAsInt32( 0 ) == 0){
            capture = true;
            counter++;
		}else if (m.getAddress() == "/controller1/button4" && m.getArgAsInt32( 0 ) == 0){
            capture = true;
            counter++;
		}else {
            capture=false;
        
        
        if (m.getAddress() == "/controller1/slider1" && m.getArgAsInt32( 0 ) == 127){
            
            cout <<"start saving\n" << endl;
            gifEncoder.save("gifs/test"+ofGetTimestampString()+".gif");
			saveImages();

		}
        
        if (counter >= 4) {
            cout << "DONE!!" << endl;
            gifEncoder.reset();
            counter = 0;
        }
        
        cout << counter <<endl;
       
        //controller2
		if ( m.getAddress() == "/controller2/button1" ){
            captureFrame();
            
			
		}else if ( m.getAddress() == "/controller2/button2" ){
            captureFrame();
			
		}else if (m.getAddress() == "/controller2/button3"){
            captureFrame();
            
		}else if (m.getAddress() == "/controller2/button4"){
            captureFrame();
            
		}
        if (m.getAddress() == "/controller2/slider1"){
            gifEncoder.save();
        }
        
        //controller3
		if ( m.getAddress() == "/controller3/button1" ){
			
		}else if ( m.getAddress() == "/controller3/button2" ){
			
		}
		else if (m.getAddress() == "/controller3/button3"){
            
		}
        else if (m.getAddress() == "/controller3/button4"){
           
		}
        if (m.getAddress() == "/controller3/slider1"){
           
		}
        
        //controller4
		if ( m.getAddress() == "/controller4/button1" ){
			
		}else if ( m.getAddress() == "/controller4/button2" ){
			
		}
		else if (m.getAddress() == "/controller4/button3"){
            
		}
        else if (m.getAddress() == "/controller4/button4"){
           
		}
        
        if (m.getAddress() == "/controller4/slider1"){
            
		}
        
		
	}
	*/
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
    for (int j = 0; j < imgs.size(); j ++) {
        imgs[j]->draw(j* (frameW/2 + 5), frameH + 200, frameW/2, frameH/2);
    }
	
	//draw live video -- create a toggle screen?
	kinect.draw(0,0);
    //vid.draw(0, 0);
    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW+10, 20);
	
	// draw the gif at mouseX, mouseY
	
	
	if (data.size() > 0){
		data[ofGetFrameNum()/8 % data.size()]->draw(ofGetWidth()/2, 0);
	}
	
	//player.draw(mouseX, mouseY);
	
	
	
	
}

//void testApp::onGifSaved(string &fileName) {
//	
//	
//	
//	
//	
//	for (int i = 0; i < nFrames; i ++) {
//        delete imgs[i];
//    }
//	imgs.clear();
//	
//	
//}

void testApp::midiButton(){
    
    
//    while( receiver.hasWaitingMessages() ){
//		// get the next message
//		ofxOscMessage m;
//		receiver.getNextMessage( &m );
//		
//        
//        
//        if ( m.getAddress() == "/controller2/button1" && m.getArgAsInt32( 0 ) == 0 ){
//            captureFrame();
//            
//            
//        }else if ( m.getAddress() == "/controller2/button2" && m.getArgAsInt32( 0 ) == 0){
//            captureFrame();
//            
//        }else if (m.getAddress() == "/controller2/button3" && m.getArgAsInt32( 0 ) == 0){
//            captureFrame();
//            
//        }else if (m.getAddress() == "/controller2/button4" && m.getArgAsInt32( 0 ) == 0){
//            captureFrame();
//            
//        }
//        if (m.getAddress() == "/controller2/slider1" && m.getArgAsInt32( 0 ) == 0){
//            gifEncoder.save("gifs/test"+ofGetTimestampString()+".gif");
//        }
//        
//	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	

    switch (key) {
        case ' ':
            captureFrame();
            break;
        case 's':
            cout <<"start saving\n" << endl;
            gifEncoder.save("gifs/test"+ofGetTimestampString()+".gif");
			saveImages();
            break;
        default:
            break;
			
		case 'p':
			gifEncoder.reset();
			break;
    }
}

void testApp::saveImages(){
	
	
	// create a directory for each recording
	
	ofDirectory myDirectory( ofToString(recordingCount));
	if (!myDirectory.exists()){
		myDirectory.create();
	} else {
		myDirectory.listDir();
		for (int j = 0; j < myDirectory.size(); j++){
			
			ofFile temp(myDirectory.getPath(j));
			temp.remove(true);
		}
	}
	
	// save these images to that directory
	for (int j = 0; j < imgs.size(); j++){
		imgs[j]->saveImage(ofToString(recordingCount) + "/frame_" + ofToString(j) + ".png");
		delete imgs[j];
	}
	
	imgs.clear();
	dir.reset();

	
/////////clear the playing images

	for (int j = 0; j < data.size(); j++){
		delete data[j];
	}
	data.clear();
	
	// reload images
	
	ofDirectory dir;
	dir.listDir(ofToString(recordingCount) );
	for (int j = 0; j < dir.size(); j++){
		string fileName = dir.getPath(j);
		ofImage * temp = new ofImage;
		temp->loadImage(dir.getPath(j));
		data.push_back(temp);
	}
	
	recordingCount++;
//    gifEncoder.reset();
	
}

void testApp::captureFrame() {
	
    gifEncoder.addFrame(kinect.getPixels(), frameW, frameH, 24, .1f);
    ofImage * img = new ofImage();										// <-- this looks like a memory leak. 
    img->allocate(frameW, frameH, OF_IMAGE_COLOR);
    img->setFromPixels(kinect.getPixels(), frameW, frameH, OF_IMAGE_COLOR);
    imgs.push_back(img);
    nFrames++;
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

//--------------------------------------------------------------
void testApp::exit(){ 
	
	//kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
	
    gifEncoder.exit();
}

