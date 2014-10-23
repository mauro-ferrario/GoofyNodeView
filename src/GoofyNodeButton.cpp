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
  // timerToCheck = 0;
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
  //if(timerToCheck > 0)
   // checkTimers();
}

/*
void GoofyNodeButton::checkTimers()
{
  for(int a = 0; a < timerActive.size(); a++)
  {
 
    if(timerActive[a])
    {
      if(timer.getAppTimeMillis() >= timeStartTimer[a] + nodeOutConnectionsParams[a] * 1000)
      {
        timerActive[a] = false;
        timerToCheck--;
        cout << "End timer" << a << endl;
//        nodeOutConnections[a]->playMovie();
       // bar((ShadowInteractiveLayer*)nodeOutConnections[a]->videoPlayer, &ShadowInteractiveLayer::activeFunction,ofRandom(0));
      }
    }
  }
   }
   */

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

void GoofyNodeButton::addNodeOutConnection(GoofyNode* node)
{
/*  GoofyNode::nodeOutConnections.push_back(node);
  nodeOutConnectionsParams.push_back(ofRandom(1,10));
 */
//  timerActive.push_back(false);
 // timeStartTimer.push_back(0);
}

void GoofyNodeButton::onPressIn(int x, int y, int button)
{
  cout << "button pressed qui" << endl;
  
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    cout << "Dentro " << endl;
    GoofyBridgeToNode* tempLayer = nodeOutConnections[a]->interactiveLayer;
    tempLayer->activeFunction(a);
  }
  //activeFunction
 // startTimers();
}

void GoofyNodeButton::onPressOut(int x, int y, int button)
{
}

/*
void GoofyNodeButton::startTimers()
{
  for(int a = 0; a < timerActive.size(); a++)
  {
    timeStartTimer[a] = timer.getAppTimeMillis();
    timerActive[a] = true;
    timerToCheck++;
  }
}
*/