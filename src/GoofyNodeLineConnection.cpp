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
  toRemove  = false;
  firstPin  = pin;
  logVerboseModule = "GoofyNodeLineConnection::_keyReleased";
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
   if(e.key == 127 && selected)
   {
     toRemove = true;
     ofLogVerbose(logVerboseModule, "Remove line");
     if(firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
     {
       ofLogVerbose(logVerboseModule, "Remove from first pin");
       firstPin->parent->removeConnection(connection);
       // Rimuovo da pin1
     }
     else
     {
       ofLogVerbose(logVerboseModule, "Remove from second pin");
       secondPin->parent->removeConnection(connection);
       // Rimuovo da pin2
     }
     connection = NULL;
     // lancia il listener per rimuovere questo
   }
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