//
//  GoofyNodeStage.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeStage.h"


GoofyNodeStage::GoofyNodeStage()
{
  
}

GoofyNodeStage::~GoofyNodeStage()
{
  
}

void GoofyNodeStage::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_STAGE;
}

void GoofyNodeStage::drawBackground()
{
  ofPushStyle();
  ofSetColor(100, 100);
  ofRect(0,0, width, height);
  ofPopStyle();
}