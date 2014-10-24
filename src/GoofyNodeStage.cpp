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
  checkRelease = false;
  countDrag = 0;
  enableMouseEvents();
}

void GoofyNodeStage::drawBackground()
{
  ofPushStyle();
  ofSetColor(255,0,0, 100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNodeStage::addNode(GoofyBridgeToNode* layer)
{
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
    lineConnection = new GoofyNodeLineConnection(pin);
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
    if(lineConnection->firstPin->pinMode == pin->pinMode)
    {
      removeTempLineConnection();
      return;
    }
    lineConnection->editable = true;
    lineConnection->secondPin = pin;
    
    GoofyNodeOutConnection* newOutConnection;
    
    if(lineConnection->firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
    {
      newOutConnection = new GoofyNodeOutConnection(lineConnection->secondPin->parent, lineConnection->secondPin->pinId);
      lineConnection->firstPin->parent->nodeOutConnections.push_back(newOutConnection);
    }
    if(lineConnection->secondPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
    {
      newOutConnection = new GoofyNodeOutConnection(lineConnection->firstPin->parent, lineConnection->firstPin->pinId);
      lineConnection->secondPin->parent->nodeOutConnections.push_back(newOutConnection);
    }
    
    lineConnection->connection = newOutConnection;
    newOutConnection = NULL;
    
    connections.push_back(lineConnection);
    
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
  if(checkRelease)
  {
    if(timer.getElapsedMillis() > timerStart + 1)
    {
      if(checkLineConnectionPin())
        removeTempLineConnection();
      checkRelease = false;
    }
  }
}

bool GoofyNodeStage::checkLineConnectionPin()
{
  if(lineConnection != NULL)
  {
    if(lineConnection->secondPin == NULL)
      return true;
  }
  return false;
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
  GoofyNode::draw();
  if(lineConnection != NULL)
  {
    lineConnection->draw();
  }
  
  vector<GoofyNodeLineConnection*>::iterator it = connections.begin();
  
  while(it != connections.end())
  {
    if((*it)->toRemove)
      connections.erase(it);
    else
    {
      (*it)->draw();
      it++;
    }
    //(GoofyNodeLineConnection*)*it.
  }
  
  for(int a = 0; a < connections.size(); a++)
  {
    connections[a]->draw();
  }
}

void GoofyNodeStage::onReleaseIn(int x, int y, int button)
{
  if(lineConnection != NULL)
  {
    timerStart = timer.getElapsedMillis();
    checkRelease = true;
  }
}
