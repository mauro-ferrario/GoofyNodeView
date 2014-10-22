//
//  GoofyNodePin.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodePin.h"


GoofyNodePin::GoofyNodePin(GoofyNodePinMode mode)
{
  pinMode = mode;
}

GoofyNodePin::~GoofyNodePin()
{
  
}

void GoofyNodePin::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_PIN;
}

void GoofyNodePin::update()

{
  
}
void GoofyNodePin::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  GoofyNode::drawBackground();
  if(isMouseOver)
    drawHole();
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

void GoofyNodePin::onPress(int x, int y, int button)
{
  
}