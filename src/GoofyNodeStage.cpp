//
//  GoofyNodeStage.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeStage.h"

GoofyNodeStage::GoofyNodeStage()
{
  lineConnection = NULL;
}

GoofyNodeStage::~GoofyNodeStage()
{
  
}

void GoofyNodeStage::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_STAGE;
}

void GoofyNodeStage::drawBackground()
{
  ofPushStyle();
  ofSetColor(100, 100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNodeStage::addNode(GoofyBridgeToNode* layer)
{
  cout << "Stage " << this << endl;
  GoofyNodeLayer::addNode(layer, this);
}

void GoofyNodeStage::addNode(GoofyNode* node)
{
  GoofyNodeLayer::addNode(node, this);
}


void GoofyNodeStage::addPinConnection(GoofyNodePin* pin)
{
  if(lineConnection == NULL)
  {
    lineConnection = new LineConnection(pin);
    lineConnection->endPoint = lineConnection->startPoint;
    lineConnection->editable = true;
  }
  else
  {
    if(lineConnection->firstPin->parent == pin->parent)
    {
      removeTempLineConnection();
      return;
    }
    lineConnection->editable = true;
    lineConnection->secondPin = pin;
    lineConnection->endPoint = ofVec2f(pin->getX()+5, pin->getY()+5);
    connections.push_back(lineConnection);
    
    if(lineConnection->firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
    {
      lineConnection->firstPin->parent->nodeOutConnections.push_back(lineConnection->secondPin->parent);
    }
    if(lineConnection->secondPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
    {
      lineConnection->secondPin->parent->nodeOutConnections.push_back(lineConnection->firstPin->parent);
    }
    
    lineConnection = NULL;
  }
}

void GoofyNodeStage::removeTempLineConnection()
{
  delete lineConnection;
  lineConnection = NULL;
}

void GoofyNodeStage::update()
{
}

void GoofyNodeStage::mouseDragged(int x, int y, int button)
{
  if(lineConnection != NULL)
  {
    if(lineConnection->editable)
      lineConnection->endPoint = ofVec2f(x,y);
  }
}

void GoofyNodeStage::draw()
{
  GoofyNodeLayer::draw();
  if(lineConnection != NULL)
  {
    lineConnection->draw();
  }
  for(int a = 0; a < connections.size(); a++)
  {
    connections[a]->draw();
  }
}
