//
//  GoofyNodeLineConnection.cpp
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#include "GoofyNodeLineConnection.h"

GoofyNodeLineConnection::GoofyNodeLineConnection(GoofyNodePin* pin)
{
  setup(pin);
}

GoofyNodeLineConnection::GoofyNodeLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2)
{
  setup(pin1, pin2);
}

void GoofyNodeLineConnection::setup(GoofyNodePin* pin1, GoofyNodePin* pin2)
{
  setup(pin1);
  secondPin = pin2;
}

void GoofyNodeLineConnection::setup(GoofyNodePin* pin)
{
  editable          = false;
  secondPin         = NULL;
  selected          = false;
  toRemove          = false;
  firstPin          = pin;
  maxSelectedRange  = 5;
  logVerboseModule  = "GoofyNodeLineConnection";
  startPoint  = ofVec2f(pin->getX() + 5, pin->getY() + 5);
  enableMouseEvents();
}

GoofyNodeLineConnection::~GoofyNodeLineConnection()
{
  firstPin = NULL;
  secondPin = NULL;
  connection = NULL;
  disableMouseEvents();
}
  
void GoofyNodeLineConnection::draw()
{
  startPoint  = ofVec2f(firstPin->getX() + 5, firstPin->getY() + 5);
  if(secondPin != NULL)
    endPoint  = ofVec2f(secondPin->getX() + 5, secondPin->getY() + 5);
  ofPushStyle();
  if(selected)
    ofSetColor(255,0,0);
  else
    ofSetColor(255);
  ofLine(startPoint, endPoint);
  ofPopStyle();
}

void GoofyNodeLineConnection::enableMouseEvents()
{
  ofAddListener(ofEvents().mouseReleased, this, &GoofyNodeLineConnection::_mouseReleased);
  ofAddListener(ofEvents().keyReleased, this, &GoofyNodeLineConnection::_keyReleased);
}

void GoofyNodeLineConnection::disableMouseEvents()
{
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNodeLineConnection::_mouseReleased);
  ofRemoveListener(ofEvents().keyReleased, this, &GoofyNodeLineConnection::_keyReleased);
}

void GoofyNodeLineConnection::_keyReleased(ofKeyEventArgs &e)
{
   if(e.key == OF_KEY_BACKSPACE && selected)
   {
     remove();
   }
}

void GoofyNodeLineConnection::remove()
{
  toRemove = true;
  ofLogVerbose(logVerboseModule, "Remove line");
  GoofyNode* nodeToRemoveConnection;
  if(firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    nodeToRemoveConnection = firstPin->parent;
    ofLogVerbose(logVerboseModule, "Remove from first pin");
  }
  else
  {
    nodeToRemoveConnection = secondPin->parent;
    ofLogVerbose(logVerboseModule, "Remove from second pin");
  }
  nodeToRemoveConnection->removeConnection(connection);
  nodeToRemoveConnection = NULL;
  connection = NULL;
}

void GoofyNodeLineConnection::_mouseReleased(ofMouseEventArgs &e)
{
  if(secondPin == NULL || firstPin == NULL || editable)
    return;
  
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(isCloseToTheLine(x,y))
    selected = true;
  else
    selected = false;
}

bool GoofyNodeLineConnection::isCloseToTheLine(int x, int y)
{
  float delta = (endPoint.y - startPoint.y)/(endPoint.x - startPoint.x);
  float y1 = (delta*(endPoint.x - x)-endPoint.y);
  y1 *= -1;
  float distance = abs(y1-y);
  
  if(distance >= 0 && distance <= maxSelectedRange)
  {
    if(startPoint.x > endPoint.x)
    {
      if(x < startPoint.x && x > endPoint.x)
        return true;
      else
        return false;
    }
    else if(startPoint.x <= endPoint.x)
    {
      if(x < endPoint.x && x > startPoint.x)
        return true;
      else
        return false;
    }
  }
  return false;
}