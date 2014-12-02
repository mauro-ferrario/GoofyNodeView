//
//  GoofyNodePartitura.cpp
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#include "GoofyNodePartitura.h"
#include "GoofyNodeStage.h"

GoofyNodePartitura::GoofyNodePartitura()
{
  GoofyNodePartitura(NULL);
}

GoofyNodePartitura::GoofyNodePartitura(GoofyNodeStage* mainStage, string name)
{
  timerActive = false;
  setup(mainStage, name);
  mainStage = NULL;
}

GoofyNodePartitura::~GoofyNodePartitura()
{
  textTimer.disable();
}

void GoofyNodePartitura::setup(GoofyNodeStage* mainStage, string name)
{
  secondsDelay    = 20;
  isPause         = false;
  timeStartPause  = 0;
  actualPosInTimeline = -1;
  GoofyNode::setup(mainStage, GOOFY_PARTITURA, name);
  setSize(110,30);
  
  float prevPos = 0;
  float endPos = 500;
  for(int a = 1; a < 18; a++)
  {
    ofVec2f randomPos;
    randomPos.x = ofRandom(prevPos, prevPos + (endPos - prevPos)/(12-a));
    randomPos.x = endPos/20*a;
    randomPos.y = ofRandom(30,60);
    prevPos = randomPos.x;
    connections.push_back(createSinglePartituraPin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f(randomPos),""));
  }
  
  
  createSinglePin(1, GOOFY_NODE_PIN_INPUT, ofVec2f((0),30), "input");
  createSinglePin(0, GOOFY_NODE_PIN_OUTPUT, ofVec2f((endPos),30), "output");
  createSinglePin(2, GOOFY_NODE_PIN_INPUT, ofVec2f(-10, 0), "stop");
  createSinglePin(3, GOOFY_NODE_PIN_INPUT, ofVec2f(-10, 20), "pause");
  
  initTextTimer();
  mainStage = NULL;
}

void GoofyNodePartitura::saveSpecificInfo(ofxXmlSettings* xml)
{
  xml->addValue("delay", ofToFloat(textTimer.text) > secondsDelay ? ofToFloat(textTimer.text) : secondsDelay);
  xml = NULL;
}

void GoofyNodePartitura::update()
{
  if(timerActive&&!isPause)
  {
    textTimer.text = ofToString((endTimer - timer.getAppTimeMillis())/1000);
    pointerPos.x = ofMap(timer.getAppTimeMillis(), timeStartTimer, endTimer, connections[0]->pos.x, connections[connections.size()-1]->pos.x);
  }
  else
  {
    pointerPos.x = ofMap(endTimer, timeStartTimer, endTimer, connections[0]->pos.x, connections[connections.size()-1]->pos.x);
  }
  
  textTimer.bounds.x = getX() + 20 - dragOffset.x;
  textTimer.bounds.y = getY() + 7 - dragOffset.y;
  checkTimer();
  
  if(timerActive&&!isPause)
  {
    int totConnections = connections.size();
    int totFunctions = 0;
    int prevPosInTimeline = actualPosInTimeline;
    for(int a = 0; a < totConnections - 1; a++)
    {
      if(pointerPos.x >= connections[a]->pos.x && pointerPos.x < connections[a+1]->pos.x)
      {
        if(a > 0)
          actualPosInTimeline = a-1;
        if(prevPosInTimeline != actualPosInTimeline)
        {
          cout << "***** BANG ***** " << endl;
          if(a != totConnections - 1)
          {
            GoofyNodePartituraPin* pin = (GoofyNodePartituraPin*)connections[a];
            pin->activated = true;
            pin = NULL;
          }
        }
        else
        {
          // cout << "***** NON BANG ***** " << endl;
        }
        if(actualPosInTimeline < 0)
          actualPosInTimeline = 0;
        float delta = (connections[a+1]->pos.y - connections[a]->pos.y)/(connections[a+1]->pos.x - connections[a]->pos.x);
        pointerPos.y = delta * (pointerPos.x - connections[a]->pos.x) + connections[a]->pos.y;
      }
    }
  }
}

void GoofyNodePartitura::checkTimer()
{
  if(timerActive&&!isPause)
  {
    if(timer.getAppTimeMillis() >= endTimer)
    {
      timerEnded();
    }
  }
}

void GoofyNodePartitura::setDelay(float seconds)
{
  if(seconds < 0)
  {
    ofLogWarning("GoofyNodeDelay::setDelay", "Delay must be positive or equal to 0!");
    return;
  }
  secondsDelay = seconds;
  textTimer.text = ofToString(secondsDelay);
}

void GoofyNodePartitura::startTimer()
{
  if(isPause)
    pauseTimer();
  else
  {
    secondsDelay    = ofToFloat(textTimer.text);
    pointerPos.x    = 0;
    actualPosInTimeline = -1;
    textTimer.disable();
    timeStartTimer  = timer.getAppTimeMillis();
    endTimer        = timeStartTimer +  secondsDelay * 1000;
    timerActive     = true;
  }
}

void GoofyNodePartitura::stopTimer()
{
  resetTimer();
}


void GoofyNodePartitura::timerEnded()
{
  resetTimer();
  activeOutputs();
}

void GoofyNodePartitura::pauseTimer()
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

void GoofyNodePartitura::resetTimer()
{
  timerActive     = false;
  isPause         = false;
  textTimer.text = ofToString(secondsDelay);
  textTimer.enable();
}

void GoofyNodePartitura::draw()
{
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(pos - dragOffset);
  drawBackground();
  drawAfterBackground();
  ofPushStyle();
  ofSetColor(255);
  int totConnections = connections.size();
  for(int a = 0; a < totConnections -1; a++)
  {
    ofLine(connections[a]->pos,connections[a+1]->pos);
  }
  //  textTimer.draw();
  ofPopStyle();
  drawNodes();
  drawAfterNodes();
  if(selected&&type != GOOFY_STAGE)
    drawSelected();
  ofPushStyle();
  ofSetColor(255,0,0);
  ofCircle(pointerPos, 2);
  ofPopStyle();
  ofPopMatrix();
  
  ofPushStyle();
  ofSetColor(0);
  textTimer.draw();
  ofPopStyle();
}

void GoofyNodePartitura::drawAfterBackground()
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


void GoofyNodePartitura::activeFunction(int id)
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

void GoofyNodePartitura::initTextTimer()
{
  textTimer.setup();
  textTimer.text = ofToString(secondsDelay);
  textTimer.bounds.x = getX();
  textTimer.bounds.y = getY();
}

GoofyNodePartitura* GoofyNodePartitura::createPartitura(ofVec2f pos, GoofyNodeStage* mainStage, float secondsDelay, string name)
{
  GoofyNodePartitura* partitura = new GoofyNodePartitura(mainStage, name);
  /*
  delay->setDelay(secondsDelay);
  delay->setPos(pos);
  */
  return partitura;
}

GoofyNode* GoofyNodePartitura::createSinglePartituraPin(int idFunction, GoofyNodePinMode mode, ofVec2f pos)
{
  return createSinglePartituraPin(idFunction, mode, pos, ofToString(idFunction));
}

GoofyNode* GoofyNodePartitura::createSinglePartituraPin(int idFunction, GoofyNodePinMode mode, ofVec2f pos, string name)
{
  GoofyNodePartituraPin* newPin = new GoofyNodePartituraPin(mainStage, name, mode);
  newPin->setPos(pos);
  newPin->pinId = idFunction;
  newPin->parent = this;
  this->addNode(newPin, this->mainStage);
  return newPin;
}