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
  GoofyNodeDelay(NULL);
}

GoofyNodeDelay::GoofyNodeDelay(GoofyNodeStage* mainStage, string name)
{
  timerActive = false;
  setup(mainStage, name);
  mainStage = NULL;
}

GoofyNodeDelay::~GoofyNodeDelay()
{
  textTimer.disable();
}

void GoofyNodeDelay::setup(GoofyNodeStage* mainStage, string name)
{
  secondsDelay    = 0;
  isPause         = false;
  timeStartPause  = 0;
  GoofyNode::setup(mainStage, GOOFY_DELAY, name);
  setSize(110,30);
  createSinglePin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f((110-10)*.5,30), "output");
  createSinglePin(1, GOOFY_NODE_PIN_INPUT, ofVec2f((110-10)*.5,-10), "input");
  createSinglePin(2, GOOFY_NODE_PIN_INPUT, ofVec2f(-10, 0), "stop");
  createSinglePin(3, GOOFY_NODE_PIN_INPUT, ofVec2f(-10, 20), "pause");
  initTextTimer();
  mainStage = NULL;
}

void GoofyNodeDelay::saveSpecificInfo(ofxXmlSettings* xml)
{
  xml->addValue("delay", ofToFloat(textTimer.text) > secondsDelay ? ofToFloat(textTimer.text) : secondsDelay);
  xml = NULL;
}

void GoofyNodeDelay::update()
{
  if(timerActive&&!isPause)
  {
    textTimer.text = ofToString((endTimer - timer.getAppTimeMillis())/1000);
  }
  textTimer.bounds.x = getX() + 20 - dragOffset.x;
  textTimer.bounds.y = getY() + 7 - dragOffset.y;
  checkTimer();
}

void GoofyNodeDelay::checkTimer()
{
 if(timerActive&&!isPause)
 {
   if(timer.getAppTimeMillis() >= endTimer)
   {
     timerEnded();
   }
 }
}

void GoofyNodeDelay::setDelay(float seconds)
{
  if(seconds < 0)
  {
    ofLogWarning("GoofyNodeDelay::setDelay", "Delay must be positive or equal to 0!");
    return;
  }
  secondsDelay = seconds;
  textTimer.text = ofToString(secondsDelay);
}

void GoofyNodeDelay::startTimer()
{
  if(isPause)
    pauseTimer();
  else
  {
    secondsDelay    = ofToFloat(textTimer.text);
    textTimer.disable();
    timeStartTimer  = timer.getAppTimeMillis();
    endTimer        = timeStartTimer +  secondsDelay * 1000;
    timerActive     = true;
  }
}

void GoofyNodeDelay::stopTimer()
{
  resetTimer();
}

 
void GoofyNodeDelay::timerEnded()
{
  resetTimer();
  activeOutputs();
}

void GoofyNodeDelay::pauseTimer()
{
  if(!timerActive)
    return;
  isPause = !isPause;
  if(isPause)
  {
    timeStartPause = timer.getAppTimeMillis();
  }
  else
  {
    float timerOffset = timer.getAppTimeMillis() - timeStartPause;
    endTimer        += timerOffset;
  }
}

void GoofyNodeDelay::resetTimer()
{
  timerActive     = false;
  isPause         = false;
  textTimer.text = ofToString(secondsDelay);
  textTimer.enable();
}

void GoofyNodeDelay::draw()
{
  GoofyNode::draw();
  ofPushStyle();
  ofSetColor(0);
  textTimer.draw();
  ofPopStyle();
}

void GoofyNodeDelay::drawAfterBackground()
{
  ofPushStyle();
  ofSetColor(255,255,255);
  if(timerActive&&!isPause)
  {
    ofRect(5, 5, ofMap(timer.getAppTimeMillis(), timeStartTimer, endTimer, 0, width - 10, true), height - 10);
  }
  else if(isPause)
  {
    ofRect(5, 5, ofMap(timeStartPause, timeStartTimer, endTimer, 0, width - 10, true), height - 10);
  }
  else
  {
    ofRect(5, 5, width - 10, height - 10);
  }
  ofPopStyle();
}


void GoofyNodeDelay::activeFunction(int id)
{
  switch(id)
  {
    case 1:
      {
        startTimer();
        break;
      }
    case 2:
    {
      stopTimer();
      break;
    }
    case 3:
    {
      pauseTimer();
      break;
    }
  }
}

void GoofyNodeDelay::initTextTimer()
{
  textTimer.setup();
  textTimer.text = ofToString(secondsDelay);
  textTimer.bounds.x = getX();
  textTimer.bounds.y = getY();
}

GoofyNodeDelay* GoofyNodeDelay::createDelay(ofVec2f pos, GoofyNodeStage* mainStage, float secondsDelay, string name)
{
  GoofyNodeDelay* delay = new GoofyNodeDelay(mainStage, name);
  delay->setDelay(secondsDelay);
  delay->setPos(pos);
  return delay;
}