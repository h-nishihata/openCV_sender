#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sender.setup(HOST, PORT);
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
    
	bLearnBakground = true;
	threshold = 50;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
	ofBackground(100,100,100);
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame){
        
        colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
        
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;
			bLearnBakground = false;
		}
        
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
        
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);
        
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
    
	ofFill();
	ofSetHexColor(0x333333);
	ofRect(0,0,320,240);
	ofSetHexColor(0xffffff);
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(0,0);
        ofSetColor(255);
        if(contourFinder.blobs[i].hole){
                if (contourFinder.nBlobs>7) {
                        ofDrawBitmapString("hole",
                        contourFinder.blobs[i].boundingRect.getCenter().x,
                        contourFinder.blobs[i].boundingRect.getCenter().y);
                    
                        ofxOscMessage m;
                        m.setAddress("/holes");
                        m.addStringArg("found");
                        sender.sendMessage( m );
                }
        }else{
            ofxOscMessage m;
            m.setAddress("/holes");
            m.addStringArg("notFound");
            sender.sendMessage( m );
        }
        
    }
    
    
    if (contourFinder.blobs.size() > 8) {
        ofxOscMessage m;
        m.setAddress("/blobs");
        m.addStringArg("found");
        sender.sendMessage( m );
    }else{
        ofxOscMessage m;
        m.setAddress("/blobs");
        m.addStringArg("notFound");
        sender.sendMessage( m );
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
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