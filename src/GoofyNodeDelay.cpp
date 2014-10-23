//
//  GoofyNodeDelay.cpp
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#include "GoofyNodeDelay.h"
#include "GoofyNodeStage.h"

GoofyNodeDelay::GoofyNodeDelay()
{
  timerActive = false;
}


GoofyNodeDelay::GoofyNodeDelay(GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
}


GoofyNodeDelay::~GoofyNodeDelay()
{
  
}

void GoofyNodeDelay::setup(string name)
{
  GoofyNode::setup(name);
  setSize(100,30);
  type = GOOFY_DELAY;
  createSinglePin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f((100-10)*.5,30));
  createSinglePin(0, GOOFY_NODE_PIN_INPUT, ofVec2f((100-10)*.5,-10));
}

void GoofyNodeDelay::update()
{
  checkTimer();
}

void GoofyNodeDelay::checkTimer()
{
 if(timerActive)
 {
   if(timer.getAppTimeMillis() >= endTimer)
   {
     timerEnded();
     timerActive = false;
   }
 }
}

void GoofyNodeDelay::startTimer()
{
  timeStartTimer = timer.getAppTimeMillis();
  endTimer = timeStartTimer +  1 * 1000;
  timerActive = true;
}
 
void GoofyNodeDelay::timerEnded()
{
  activeOutputs();
}

void GoofyNodeDelay::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  drawBackground();
  ofPushStyle();
  ofSetColor(255,255,255);
  if(timerActive)
  {
    ofRect(5, 5, ofMap(timer.getAppTimeMillis(), timeStartTimer, endTimer, 0, width - 10, true), height - 10);
  }
  else
  {
    ofRect(5, 5, width - 10, height - 10);
  }
  ofPopStyle();
  ofPushStyle();
  drawNodes();
  ofPopStyle();
  ofPopMatrix();
}


void GoofyNodeDelay::activeFunction(int id)
{
  switch(id)
  {
    case 0:
      {
        startTimer();
      }
  }
}