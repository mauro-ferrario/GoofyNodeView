//
//  GoofyBridgeToNode.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyBridgeToNode.h"


GoofyBridgeToNode::GoofyBridgeToNode()
{
  name = "";
}

GoofyBridgeToNode::~GoofyBridgeToNode()
{
  
}

void GoofyBridgeToNode::initId()
{
  bridgeId = ofToString(ofGetYear())+ofToString(ofGetMonth())+ofToString(ofGetDay())+ofToString(ofGetHours())+ofToString(ofGetMinutes())+ofToString(ofGetSeconds())+"-"+ofToString(int(ofRandom(10000)));
  cout << bridgeId << endl;
}

void GoofyBridgeToNode::setup()
{
  if(bridgeId == "")
    initId();
  defineNodeMethods();
}

void GoofyBridgeToNode::activeFunction(int id)
{
}

void GoofyBridgeToNode::defineNodeMethods()
{
}

void GoofyBridgeToNode::addMethod(string methodName)
{
  functionNames.push_back(methodName);
}