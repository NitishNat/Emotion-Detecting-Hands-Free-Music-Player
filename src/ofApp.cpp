#include "ofApp.h"
using namespace ofxCv;
using namespace cv;


//--------------------------------------------------------------
//***************************Credits**************************
//I would like to give credits to Kyle McDonald for the
//faceTracker library and the tutorials on using it.
//          https://github.com/kylemcdonald
//--------------------------------------------------------------

void ofApp::setup(){

    ofSetVerticalSync(true);
    cam.setup(640, 480);
    
    //Sets up the face tracker
    tracker.setup();
    tracker.setRescale(.5);
}

//--------------------------------------------------------------

void ofApp::update(){
    
    //Updates camera after every frame
    cam.update();
    if(cam.isFrameNew()) {
        if(tracker.update(toCv(cam))) {
            //Classify the tracked Face into one of the three emotions.
            classifier.classify(tracker);
        }
    }
}

//--------------------------------------------------------------

void ofApp::draw(){
    
    
    float maximumEyebrowHeight = 9.0f;
    float maximumMouthHeight = 2.0f;
    float maximumEyeOpeness = 3.5f;
    
    //Creates a mouthHeight object that tracks how wide the mouth is open
    float mouthHeight = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT);
    //Creates an eyebrowHeight object that tracks how high the eyebrows are raised
    float eyebrowHeight = tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT);
    //Creates an eyeOpenness object that tracks how wide the eyes are
    float eyeOpenness = tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS);
    
    //Checks to see if eyebrow height is above threshold value, and if it is, music is paused
    if (eyebrowHeight >= maximumEyebrowHeight) {
        
        //check if music is playing
        if (soundx.isPlaying()) {
           
            //pause music since eyebrow height is above threshold value
            soundx.setPaused(true);
            
        }
    }
    
    //Checks to see if mouth height is above threshold value, and if it is, music is played
    if (mouthHeight >= maximumMouthHeight) {
        
        //check to see if music is being played for the first time
        if (!soundx.isPlaying() && !isMusicPlaying) {
            
            soundx.play();
            isMusicPlaying = true;
        //resume the music if it has already been paused before
        } else {
            
            soundx.setPaused(false);
            isMusicPlaying = false;
            
        }
    }
    
    //hecks to see if eye is open above threshold value, and if it is, song is changed
    if (eyeOpenness >= maximumEyeOpeness) {
        
        //Go to the next song and start playing it
        i++;
        soundx.load(std::to_string(i) + ".mp3");
        soundx.play();
        
    }
    

    //Draw a box on the top left corner of the screen
    ofSetColor(200);
    cam.draw(0, 0);
    tracker.draw();
    int w = 120, h = 15;
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(5, 10);
    int primary = classifier.getPrimaryExpression();
    //Array with possible expressions
    std::string descriptionArray [3] = {"smiling","mind == blown","nuetral"};
    
    //print out all the expressions
    for(int i = 0; i < 3; i++){
        
        ofSetColor(i == primary ? ofColor::red : ofColor::black);
        
        //controls the size of the box representing probabilities of each emotion
        ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
        ofSetColor(255);
        ofDrawBitmapString(descriptionArray[i], 5, 9);
        ofTranslate(0, h + 10);
    }
    
    ofPopMatrix();
    ofPopStyle();
    
    //Draw box with instructions on key functions on the bottom left
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
    ofDrawBitmapStringHighlight(string() +
                                "r - reset\n" +
                                "l - load expressions",
                                14, ofGetHeight() - 7 * 12);
    
    
  
    ofDrawBitmapStringHighlight(string() +
                                "** open mouth to resume **\n" +
                                "** blink to pause **\n" +
                                "** raise eyebrows to change songs **\n",
                                350, ofGetHeight() - 7 * 12);
    
    //    float mouthHeight = camTracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT);
    //
    //    if (mouthHeight >= 5) {
    //        soundx.play();
    // }
    
    
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){

    //reset the classified emotions as well as the tracker
    if(key == 'r') {
        
        tracker.reset();
        classifier.reset();
    }
    
    //load the expressions to show probabilities
    if(key == 'l') {
        
        classifier.load("expressions");
    }
    
    //take a screenshot saved in the bin folder of the project
    if (key == 'c') {
        
        ofSaveFrame();
    }
    
    //    if(key == 'e') {
    //
    //        classifier.addExpression();
    //    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
