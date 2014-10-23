//
//  GoofyNodePin.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodePin.h"
#include "GoofyNodeStage.h"

GoofyNodePin::GoofyNodePin(GoofyNodePinMode mode)
{
  pinId     = -1;
  pinMode   = mode;
}

GoofyNodePin::~GoofyNodePin()
{
  
}

void GoofyNodePin::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_PIN;
  enableMouseEvents();
}

void GoofyNodePin::update()

{
  
}
void GoofyNodePin::drawAfterBackground()
{
  //cout << "Drag over pin" << isMouseOver <<  endl;
  if(isMouseOver)
    drawHole();
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

void GoofyNodePin::onPressIn(int x, int y, int button)
{
}

void GoofyNodePin::onReleaseIn(int x, int y, int button)
{
   mainStage->addPinConnection(this);
}

void GoofyNodePin::onPressOut(int x, int y, int button)
{
  
}

void GoofyNodePin::mouseDragged(int x, int y, int button)
{
  if(isDraggingIn)
  {
    //cout << "Drag pin mouse over" << endl;
    if(mainStage->lineConnection == NULL)
      mainStage->addPinConnection(this);
  }
}