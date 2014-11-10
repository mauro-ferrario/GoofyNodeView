//
//  GoofyNodePin.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodePin.h"
#include "GoofyNodeStage.h"

GoofyNodePin::GoofyNodePin()
{
  GoofyNodePin(NULL);
}
                           
GoofyNodePin::GoofyNodePin(GoofyNodeStage* mainStage, string name, GoofyNodePinMode mode)
{
  pinId     = -1;
  pinMode   = mode;
  setup(mainStage, name);
}

GoofyNodePin::~GoofyNodePin()
{
  
}

void GoofyNodePin::setup(GoofyNodeStage* mainStage, string name)
{
  bDrawName = false;
  GoofyNode::setup(mainStage, GOOFY_PIN, name);
  setSize(10,10);
}

void GoofyNodePin::saveSpecificInfo(ofxXmlSettings* xml)
{
  xml->addValue("pinMode", pinMode);
  xml->addValue("pinId", pinId);
  xml = NULL;
}

void GoofyNodePin::update()
{
  
}

void GoofyNodePin::drawAfterBackground()
{
  if(isMouseOver)
  {
    drawHole();
    bDrawName = true;
  }
}

void GoofyNodePin::drawAfterNodes()
{
  if(bDrawName)
    drawName();
  bDrawName = false;
}

void GoofyNodePin::drawName()
{
  ofPushMatrix();
  ofTranslate(0,-10);
  ofPushStyle();
  int length = name.length();
  ofPushMatrix();
  ofTranslate(-5, -18);
  ofPushStyle();
  ofSetColor(0,255);
  ofRect(0,0,(length * 9)+5, 26);
  ofPopStyle();
  ofPopMatrix();
  ofSetColor(255);
  ofVec2f pos;
  ofDrawBitmapString(name, pos);
  ofPopStyle();
  ofPopMatrix();
}

void GoofyNodePin::drawHole()
{
  ofPushMatrix();
  ofPushStyle();
  ofSetColor(255);
  ofVec2f pos;
  pos.x = width*.5;
  pos.y = height*.5;
  ofCircle(pos, width*.25);
  ofPopStyle();
  ofPopMatrix();
}

void GoofyNodePin::onPressIn(int x, int y, int button)
{
}

void GoofyNodePin::onReleaseIn(int x, int y, int button)
{
 // cout << "release In pin" <<endl;
   mainStage->addPinConnection(this);
}

void GoofyNodePin::onPressOut(int x, int y, int button)
{
  
}

void GoofyNodePin::mouseDragged(int x, int y, int button)
{
  if(isDraggingIn)
  {
    if(mainStage->lineConnection == NULL)
      mainStage->addPinConnection(this);
  }
}