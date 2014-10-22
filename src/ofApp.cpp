#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetVerticalSync(false);
  ofSetFrameRate(120);
  ofBackground(0);
  nodeView = new GoofyNodeStage();
  nodeView->setup("Main");
  nodeView->setSize(ofGetWindowWidth(), ofGetWindowHeight());
  fake1 = new FakeClass();
  fake1->setup();
  nodeView->addNode(fake1);
  button = new GoofyNodeButton();
  button->setup("Button");
  button->setSize(50,50);
  button->setPos(ofVec2f(40,40));
  nodeView->addNode(button);
}

//--------------------------------------------------------------
void ofApp::update(){
  nodeView->update();
  ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
  nodeView->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
