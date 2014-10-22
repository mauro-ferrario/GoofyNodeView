//
//  GoofyNodeButton.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeButton.h"


GoofyNodeButton::GoofyNodeButton()
{
 // timerToCheck = 0;
}


GoofyNodeButton::~GoofyNodeButton()
{
  
}


void GoofyNodeButton::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_BUTTON;
  enableMouseEvents();
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
  ofPopStyle();
  ofPopMatrix();
 // drawNodeOutConnections();
}

void GoofyNodeButton::addNodeOutConnection(GoofyNode* node)
{
/*  GoofyNode::nodeOutConnections.push_back(node);
  nodeOutConnectionsParams.push_back(ofRandom(1,10));
 */
//  timerActive.push_back(false);
 // timeStartTimer.push_back(0);
}

void GoofyNodeButton::onPress(int x, int y, int button)
{
  cout << "button pressed" << endl;
 // startTimers();
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