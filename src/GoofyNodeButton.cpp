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
  GoofyNodeButton(NULL);
}

GoofyNodeButton::GoofyNodeButton(GoofyNodeStage* mainStage, string name)
{
  setup(mainStage, name);
}

GoofyNodeButton::~GoofyNodeButton()
{
  
}

void GoofyNodeButton::setup(GoofyNodeStage* mainStage, string name)
{
  GoofyNode::setup(mainStage, name);
  setSize(30,30);
  type = GOOFY_BUTTON;
  enableMouseEvents();
  createSinglePin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f((30-10)*.5,30), "output");
}

void GoofyNodeButton::update()
{
}

void GoofyNodeButton::drawAfterBackground()
{
  ofPushStyle();
  ofSetColor(255,0,0);
  float radius = (width *.7)*.5;
  float center = (width)*.5;
  ofCircle(center, center, radius);
}

void GoofyNodeButton::onReleaseIn(int x, int y, int button)
{
  if(!isDraggingIn)
    activeOutputs();
}

GoofyNodeButton* GoofyNodeButton::createButton(ofVec2f pos, GoofyNodeStage* mainStage, string name)
{
  GoofyNodeButton* btn = new GoofyNodeButton(mainStage);
  //btn->setup("button");
  btn->setPos(pos);
  mainStage = NULL;
  return btn;
}