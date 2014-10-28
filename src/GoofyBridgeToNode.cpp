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
  
}

GoofyBridgeToNode::~GoofyBridgeToNode()
{
  
}

void GoofyBridgeToNode::initId()
{
  id = ofToString(ofGetYear())+ofToString(ofGetMonth())+ofToString(ofGetDay())+ofToString(ofGetHours())+ofToString(ofGetMinutes())+ofToString(ofGetSeconds())+"-"+ofToString(int(ofRandom(10000)));
}

void GoofyBridgeToNode::setup()
{
  cout << "CAll setup" << endl;
  if(id == "")
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