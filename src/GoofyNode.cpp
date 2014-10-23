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
#include "GoofyNodeDelay.h"

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
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased);
}

void GoofyNode::removeMouseDragListener()
{
  ofRemoveListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged);
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
      if(type != GOOFY_PIN  && type != GOOFY_STAGE)
      {
        mouseDragStart = ofVec2f(x, y);
      }
      isMousePressed = true;
      onPressIn(x, y, button);
    }
  }
  else
  {
    onPressOut(x, y, button);
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
  
  if(isDraggingIn && dragOffset.length() != 0)
  {
    if(type != GOOFY_PIN  && type != GOOFY_STAGE)
    {
      pos -= dragOffset;
      dragOffset = ofVec2f(0,0);
    }
  }
  
  if(hitTest(x, y))
  {
    onReleaseIn(x, y, button);
  }
  else
  {
  }
  isMousePressed = false;
  isDraggingIn = false;
}

void GoofyNode::_mouseMoved(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(hitTest(x, y))
  {
    isMouseOver = true;
  }
  else
  {
    isMouseOver = false;
  }
}

bool GoofyNode::_mouseDragged(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;

  if(isDraggingIn)
  {
    if(type != GOOFY_PIN && type != GOOFY_STAGE)
    {
      dragOffset = mouseDragStart - ofVec2f(x,y);
    }
  }
  
  if(hitTest(x, y))
  {
    isMouseOver = true;
    if(isMousePressed)
      isDraggingIn  = true;
  }
  else
  {
    isMouseOver = false;
  }
    mouseDragged(x, y, button);
  return false;
}

float GoofyNode::getX()
{
  if(parent == NULL)
  {
    return pos.x + dragOffset.x;
  }
  else
  {
    return pos.x + parent->getX() - parent->dragOffset.x;
  }
}

float GoofyNode::getY()
{
  if(parent == NULL)
  {
    return pos.y + dragOffset.y;
  }
  else
  {
    return pos.y + parent->getY() - parent->dragOffset.y;
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
  this->name  = name;
  mouseDragStart = ofVec2f(0,0);
  dragOffset = ofVec2f(0,0);
  isDraggingIn  = false;
  parent      = NULL;
  pos.x       = 0;
  pos.y       = 0;
  type        = GOOFY_SIMPLE_NODE;
}

void GoofyNode::update()
{
}

void GoofyNode::draw()
{
  ofPushMatrix();
  ofTranslate(pos - dragOffset);
  drawBackground();
  drawAfterBackground();
  drawNodes();
  ofPopMatrix();
}

void GoofyNode::drawAfterBackground()
{
  
}

void GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos)
{
  GoofyNodePin* newPin = new GoofyNodePin(mode);
  newPin->setup(ofToString(idFunction));
  newPin->setSize(10,10);
  newPin->setPos(pos);
  newPin->pinId = idFunction;
  newPin->parent = this;
  this->addNode(newPin, this->mainStage);
}


void GoofyNode::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  node->parent = this;
  node->setMainStage(mainStage);
  nodes.push_back(node);
}

void GoofyNode::drawBackground()
{
  ofPushStyle();
  ofSetColor(100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNode::activeOutputs()
{
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    switch(nodeOutConnections[a]->type)
    {
      case GOOFY_DELAY:
      {
        GoofyNodeDelay* delay = (GoofyNodeDelay*)nodeOutConnections[a];
        delay->activeFunction(nodeOutConnectionsFunctionId[a]);
        delay = NULL;
        break;
      }
      case GOOFY_LAYER:
      {
        GoofyBridgeToNode* tempLayer = nodeOutConnections[a]->interactiveLayer;
        tempLayer->activeFunction(nodeOutConnectionsFunctionId[a]);
        break;
      }
      case GOOFY_SIMPLE_NODE:
        break;
    }
  }
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