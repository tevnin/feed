#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    frameW  = 320;
    frameH  = 240;
    nFrames = 0;
    
    vid.initGrabber(frameW,frameH);

    //gifEncoder.setup(frameW, frameH, .25, 256);
    //ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
    
    ofBackground(50, 40, 50);
	
	
	ofDirectory dir;
	dir.listDir("");
	for (int i = 0; i < dir.size(); i++){
	
		string fileName = dir.getPath(i);
		cout << fileName << endl;
		ofImage * temp = new ofImage;
		temp->loadImage(dir.getPath(i));
		data.push_back(temp);
	}
	
	ofSetVerticalSync(true);
	
	//player.loadMovie("test.gif");
}

//--------------------------------------------------------------
void testApp::update(){ 
    vid.update();
	//player.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    for (int i = 0; i < imgs.size(); i ++) {
        imgs[i]->draw(i* (frameW/2 + 5), frameH, frameW/2, frameH/2);
    }
    vid.draw(0, 0);
    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW+10, 20);

	
	data[ofGetFrameNum()/8 % data.size()]->draw(mouseX, mouseY);
	
	//player.draw(mouseX, mouseY);
}

void testApp::onGifSaved(string &fileName) {
	
	
	for (int i = 0; i < nFrames; i ++) {
        delete imgs[i];
    }
	imgs.clear();
	
	
	
    cout << "gif saved as " << fileName << endl;
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
            //gifEncoder.save("test.gif");
			saveImages();
            break;
        default:
            break;
    }
}

void testApp::saveImages(){
	for (int i = 0; i < imgs.size(); i++){
		imgs[i]->saveImage("frame_" + ofToString(i) + ".png");
		delete imgs[i];
	}
	
	imgs.clear();
}

void testApp::captureFrame() {
    
    ofImage * img = new ofImage();										// <-- this looks like a memory leak. 
    img->allocate(frameW, frameH, OF_IMAGE_COLOR);
    img->setFromPixels(vid.getPixels(), frameW, frameH, OF_IMAGE_COLOR);
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
    //gifEncoder.exit();
}

