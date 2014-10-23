//
//  GoofyNodeButton.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeButton.h"
#include "GoofyNodeStage.h"

GoofyNodeButton::GoofyNodeButton()
{
 // timerToCheck = 0;
}


GoofyNodeButton::GoofyNodeButton(GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
}


GoofyNodeButton::~GoofyNodeButton()
{
  
}

void GoofyNodeButton::setup(string name)
{
  GoofyNode::setup(name);
  setSize(30,30);
  type = GOOFY_BUTTON;
  enableMouseEvents();
  createSinglePin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f((30-10)*.5,30));
}

void GoofyNodeButton::update()
{
}

void GoofyNodeButton::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  drawBackground();
  ofPushStyle();
  ofSetColor(255,0,0);
  float radius = (width *.7)*.5;
  float center = (width)*.5;
  ofCircle(center, center, radius);
  drawNodes();
  ofPopStyle();
  ofPopMatrix();
}

void GoofyNodeButton::onPressIn(int x, int y, int button)
{
  activeOutputs();
}

void GoofyNodeButton::onPressOut(int x, int y, int button)
{
}