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
  pinMode = mode;
  cout << "NEW PIN" << endl;
}

GoofyNodePin::~GoofyNodePin()
{
  
}

void GoofyNodePin::setup(string name)
{
  GoofyNode::setup(name);
  cout << "NEW PIN SETUP" << mainStage << endl;
  type = GOOFY_PIN;
}

void GoofyNodePin::update()

{
  
}
void GoofyNodePin::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  GoofyNode::drawBackground();
  if(isMouseOver)
    drawHole();
  ofPopMatrix();
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
  if(isMouseOver)
  {
    if(mainStage->lineConnection == NULL)
      mainStage->addPinConnection(this);
  }
}