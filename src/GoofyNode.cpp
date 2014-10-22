//
//  GoofyNode.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNode.h"



GoofyNode::GoofyNode()
{
  
}

GoofyNode::~GoofyNode()
{
  
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
      cout << "Mouse pressed in" << name << endl;
      onPress(x, y, button);
    }
  }
  else
  {
    isMousePressed = false;	// update flag
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

void GoofyNode::drawNodeOutConnections()
{
  ofPushStyle();
  ofSetColor(255);
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    ofLine(pos, nodeOutConnections[a]->pos);
  }
  ofPopStyle();
}*/

void GoofyNode::drawBackground()
{
  ofPushStyle();
  ofSetColor(100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNode::onPress(int x, int y, int button)
{
  
}