//
//  GoofyNode.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNode.h"
#include "GoofyNodePin.h"
#include "GoofyNodeStage.h"


GoofyNode::GoofyNode()
{
  
}

GoofyNode::~GoofyNode()
{
  
}

void GoofyNode::setMainStage(GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
}

void GoofyNode::enableMouseEvents()
{
  ofAddListener(ofEvents().mousePressed, this, &GoofyNode::_mousePressed);
  ofAddListener(ofEvents().mouseMoved, this, &GoofyNode::_mouseMoved);
  ofAddListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged);
  ofAddListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased);
}

void GoofyNode::disableMouseEvents()
{
  ofRemoveListener(ofEvents().mousePressed, this, &GoofyNode::_mousePressed);
  ofRemoveListener(ofEvents().mouseMoved, this, &GoofyNode::_mouseMoved);
  ofRemoveListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged);
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased);
}

void GoofyNode::setSize(int w, int h)
{
  width   = w;
  height  = h;
}

void GoofyNode::drawNodes()
{
  for(int a = 0; a < nodes.size(); a++)
  {
    nodes[a]->update();
    nodes[a]->draw();
  }
}

void GoofyNode::_mousePressed(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(hitTest(x, y))
  {
    if(!isMousePressed)
    {
      isMousePressed = true;
      onPressIn(x, y, button);
    }
  }
  else
  {
    onPressOut(x, y, button);
    //cout << "Mouse pressed out" << name << endl;
    //onPressOutside(x, y, button);
  }
}

void GoofyNode:: setPos(ofVec2f newPos)
{
  pos = newPos;
}

void GoofyNode::_mouseReleased(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(hitTest(x, y))
  {
    onReleaseIn(x, y, button);
   // onRelease(x, y, button);
  }
  else
  {
   // if(isMousePressed(button)) onReleaseOutside(x, y, button);
  }
  isMousePressed = false;
 // mouseReleased(x, y, button);
}

void GoofyNode::_mouseMoved(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(hitTest(x, y))
  {
    isMouseOver = true;
    // onRelease(x, y, button);
  }
  else
  {
    isMouseOver = false;
  }
}

void GoofyNode::_mouseDragged(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;

  if(hitTest(x, y))
  {
    isMouseOver = true;
    // onRelease(x, y, button);
  }
  else
  {
    isMouseOver = false;
  }
  
//  if(hitTest(x, y)) {						// if mouse is over the object
//    if(!_isMouseOver) {						// if wasn't over previous frame
//      //				onPress(x, y);							// call onPress - maybe not
//      _isMouseOver = true;						// update flag
//      onRollOver(x, y);						// call onRollOver
//    }
//    onDragOver(x, y, button);				// and trigger onDragOver
//  } else {
//    if(_isMouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
//      onRollOut();							// call onRollOut
//      _isMouseOver = false;						// update flag
//    }
//    if(isMousePressed(button)) {
//      onDragOutside(x, y, button);
//    }
//    _isMousePressed[button] = false;
//  }
//  
//  _stateChangeTimestampMillis = ofGetElapsedTimeMillis();
//  
  mouseDragged(x, y, button);


}

float GoofyNode::getX()
{
  if(parent == NULL)
  {
    return pos.x;
  }
  else
  {
    return pos.x + parent->getX();
  }
}

float GoofyNode::getY()
{
  if(parent == NULL)
  {
    return pos.y;
  }
  else
  {
    return pos.y + parent->getY();
  }
}

bool GoofyNode::hitTest(int tx, int ty)
{
  float x = getX();
  float y = getY();
  return (tx > x) && (tx < x + width) && (ty > y) && (ty < y + height);
}

void GoofyNode::setup(string name)
{
  this->name = name;
  parent = NULL;
  pos.x = pos.y = 0;
  type = GOOFY_SIMPLE_NODE;
}

void GoofyNode::update()
{
  
}

void GoofyNode::draw()
{

}

void GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos)
{
  GoofyNodePin* newPin = new GoofyNodePin(mode);
  newPin->setup(ofToString(idFunction));
  newPin->setSize(10,10);
  newPin->setPos(pos);
  newPin->pinId = idFunction;
  newPin->enableMouseEvents();
  newPin->parent = this;
  //nodes.push_back(newPin);
  this->addNode(newPin, this->mainStage);
}


void GoofyNode::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  node->parent = this;
  node->setMainStage(mainStage);
  nodes.push_back(node);
}

/*
void GoofyNode::addNodeOutConnection(GoofyNode* node)
{
  if(node->parent != parent)
  {
    cout << "Error!, not in the same level" << endl;
    return;
  }
  nodeOutConnections.push_back(node);
}

*/

void GoofyNode::drawBackground()
{
  ofPushStyle();
  ofSetColor(100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNode::onPressIn(int x, int y, int button)
{
  
}

void GoofyNode::onPressOut(int x, int y, int button)
{
  
}

void GoofyNode::mouseDragged(int x, int y, int button)
{
  
}

void GoofyNode::onReleaseIn(int x, int y, int button)
{
  
}