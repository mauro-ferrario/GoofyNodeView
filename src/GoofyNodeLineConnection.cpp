//
//  GoofyNodeLineConnection.cpp
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#include "GoofyNodeLineConnection.h"


#include "GoofyNodeLineConnection.h"

GoofyNodeLineConnection::GoofyNodeLineConnection(GoofyNodePin* pin)
{
  editable  = false;
  secondPin = NULL;
  selected  = false;
  firstPin  = pin;
  startPoint  = ofVec2f(pin->getX() + 5, pin->getY() + 5);
  enableMouseEvents();
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
}

void GoofyNodeLineConnection::disableMouseEvents()
{
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNodeLineConnection::_mouseReleased);
}

void GoofyNodeLineConnection::_mouseReleased(ofMouseEventArgs &e)
{
  if(secondPin == NULL)
    return;
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  ofVec2f point1 = ofVec2f(firstPin->getX() + 5, firstPin->getY() + 5);
  ofVec2f point2 = ofVec2f(secondPin->getX() + 5, secondPin->getY() + 5);
  
  float delta = (point2.y - point1.y)/(point2.x - point1.x);
  
  float y1 = (delta*(point2.x - x)-point2.y);
  y1 *= -1;
  
  if(abs(y1 - y) >= 0 && abs(y1 - y) <= 5)
  {
    selected = true;
  }
  else
  {
    selected = false;
  }
}