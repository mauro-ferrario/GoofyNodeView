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
  // timerToCheck = 0;
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
     cout << "Fine timer" << endl;
     timerEnded();
     timerActive = false; //        nodeOutConnections[a]->playMovie();
 // bar((ShadowInteractiveLayer*)nodeOutConnections[a]->videoPlayer, &ShadowInteractiveLayer::activeFunction,ofRandom(0));
   }
 }
}

void GoofyNodeDelay::startTimer()
{
  timeStartTimer = timer.getAppTimeMillis();
  endTimer = timeStartTimer +  10 * 1000;
  timerActive = true;
}
 
void GoofyNodeDelay::timerEnded()
{
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    switch(nodeOutConnections[a]->type)
    {
      case GOOFY_DELAY:
      {
        cout << "Delay" << endl;
        GoofyNodeDelay* delay = (GoofyNodeDelay*)nodeOutConnections[a];
        delay->activeFunction(nodeOutConnectionsFunctionId[a]);
        delay = NULL;
        break;
      }
      case GOOFY_LAYER:
      {
        cout << "Layer" << endl;
        GoofyBridgeToNode* tempLayer = nodeOutConnections[a]->interactiveLayer;
        tempLayer->activeFunction(nodeOutConnectionsFunctionId[a]);
        break;
      }
      case GOOFY_SIMPLE_NODE:
        cout << "Layer 2" << endl;
        break;
    }
  }
}

void GoofyNodeDelay::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  drawBackground();
  ofPushStyle();
  ofSetColor(255,255,255);
  ofRect(5, 5, ofMap(timer.getAppTimeMillis(), timeStartTimer, endTimer, 0, width - 10, true), height - 10);
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
        cout << nodeOutConnections.size() << endl;
        cout << "Start timer" << endl;
      }
  }
}