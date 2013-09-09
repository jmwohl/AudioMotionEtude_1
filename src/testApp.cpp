#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    
    cW = ofGetScreenWidth();
    cH = ofGetScreenHeight();
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(cW,cH);

    colorImg.allocate(cW,cH);
	grayImage.allocate(cW,cH);
	grayBg.allocate(cW,cH);
	grayDiff.allocate(cW,cH);

	bLearnBakground = true;
    showVideo = false;
	threshold = 80;
    numCols = 20;
    numRows = 20;
    xMargin = yMargin = 40;
    hitAreaRadius = 40;
    
    
    for (int j = 0; j <= numRows; j++) {
        for (int k = 0; k <= numCols; k++) {
            int x = xMargin + ((ofGetScreenWidth()-xMargin*2)/numCols)*j;
            int y = yMargin + ((ofGetScreenHeight()- yMargin*2)/numRows)*k;
            ofPoint c = ofPoint(x, y);
            int index = j % 8;
            string path = "vibe_" + ofToString(index) + ".wav";
            float vol = 1.f - (float)k / (float)numCols;
            float pan = -((float)numRows/2 - (float)j) / ((float)numRows/2);
            
            cout << pan << endl;
            
            triggers.push_back(Trigger(c, 20, path, vol, pan));
        }
    }
    
    isFullScreen = false;
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0,0,0);

    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

        colorImg.setFromPixels(vidGrabber.getPixels(), cW,cH);
        
        // do this on every frame
		grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
        
        grayImage = colorImg;
        

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 500, 10000, 10, false);	// find holes
	}

}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
    
    if (showVideo) {
        grayImage.draw(0,0);
    }
    
//	grayBg.draw(20,280);
//	grayDiff.draw(360,280);

	// then draw the contours:
//    colorImg.draw(0,0);

//	ofRect(360,540,cW,cH);
//	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);
    
    for (tI = triggers.begin(); tI != triggers.end(); tI++) {
        for (int i = 0; i < contourFinder.nBlobs; i++){
            
            // for each blob, get the centroid.  If the centroid is within a certain distance from a Trigger, change the trigger color and play the Trigger's sound.
            ofPoint centroid = contourFinder.blobs[i].centroid;
            ofPoint triggerCenter = tI->center;
            
            if (ofDist(centroid.x, centroid.y, triggerCenter.x, triggerCenter.y) < 20) {
                cout << "HIT!" << endl;
                if (!tI->player.getIsPlaying()) {
                    tI->player.play();
                    tI->triggered = true;
                }
            }
        }
        tI->draw();
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
        case 13:
            isFullScreen = !isFullScreen;
            ofSetFullscreen(isFullScreen);
		case ' ':
			bLearnBakground = true;
            showVideo = !showVideo;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
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
