#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  ofSetLogLevel(OF_LOG_VERBOSE);
  
  ofSetVerticalSync(false);
  ofSetFrameRate(120);
  ofBackground(0);
  
  nodeView = new GoofyNodeStage("Main", ofGetWindowWidth(), ofGetWindowHeight());
  fake1 = new FakeClassForNode();
  fake1->setup();
  fake1->id = "2014102703052-2625";
  nodeView->addLayer(fake1);
  
  xml.loadFile("test.xml");
  if(false)
  {
    nodeView->loadFromXML(&xml);
  }
  else
  {
    delay1 = new GoofyNodeDelay(nodeView);
    delay1->setPos(ofVec2f(40,140));
    delay1->addToStage();
    
    fake1 = new FakeClassForNode();
    fake1->setup();
    nodeView->addNode(fake1);
    
    button = new GoofyNodeButton(nodeView);
    button->setPos(ofVec2f(40,40));
    button->addToStage();
    
    delay2 = new GoofyNodeDelay(nodeView);
    delay2->setPos(ofVec2f(340,140));
    delay2->addToStage();
      
    nodeView->addNode(GOOFY_DELAY, nodeView);
    nodeView->addNode(GOOFY_BUTTON, nodeView);
  }
  
    
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
  if(key == 's')
  {
    xml.clear();
    nodeView->saveInfo(&xml);
    xml.saveFile("test.xml");
  }
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
