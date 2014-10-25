#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  ofSetLogLevel(OF_LOG_VERBOSE);
  
  ofSetVerticalSync(false);
  ofSetFrameRate(120);
  ofBackground(0);
  
  nodeView = new GoofyNodeStage();
  nodeView->setup("Main");
  nodeView->setSize(ofGetWindowWidth(), ofGetWindowHeight());
  
  
  delay1 = new GoofyNodeDelay(nodeView);
  delay1->setup("Delay 1");
  delay1->setPos(ofVec2f(40,140));
  nodeView->addNode(delay1);
  
  fake1 = new FakeClassForNode();
  fake1->setup();
  nodeView->addNode(fake1);
  
  button = new GoofyNodeButton(nodeView);
  button->setup("Button");
  button->setPos(ofVec2f(40,40));
  nodeView->addNode(button);
  
  
  delay2 = new GoofyNodeDelay(nodeView);
  delay2->setup("Delay 2");
  delay2->setPos(ofVec2f(340,140));
  nodeView->addNode(delay2);
  nodeView->addNode(GOOFY_DELAY, nodeView);
  nodeView->addNode(GOOFY_BUTTON, nodeView);
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
