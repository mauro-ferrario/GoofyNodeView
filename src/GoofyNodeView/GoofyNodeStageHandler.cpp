//
//  GoofyNodeStageHandler.cpp
//  GoofyNodeTest
//
//  Created by XXX on 29/10/14.
//
//

#include "GoofyNodeStageHandler.h"

GoofyNodeStageHandler::GoofyNodeStageHandler()
{
  lineConnection    = NULL;
  checkRelease      = false;
}

GoofyNodeStageHandler::~GoofyNodeStageHandler()
{
  
}

void GoofyNodeStageHandler::removeTempLineConnection()
{
  ofLogVerbose(logVerboseModule, "delete lineConnection");
  delete lineConnection;
  lineConnection = NULL;
}

void GoofyNodeStageHandler::createNewLineConnection(GoofyNodePin* pin)
{
  lineConnection = new GoofyNodeLineConnection(pin);
  lineConnection->endPoint = lineConnection->startPoint;
  lineConnection->editable = true;
  pin = NULL;
}

void GoofyNodeStageHandler::draw()
{
  if(lineConnection != NULL)
  {
    lineConnection->draw();
  }
}

void GoofyNodeStageHandler::update()
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

void GoofyNodeStageHandler::mouseDragged(int x, int y, int button)
{
  if(lineConnection != NULL)
  {
    if(lineConnection->editable)
      lineConnection->endPoint = ofVec2f(x,y);
  }
}

void GoofyNodeStageHandler::closeLineConnection(GoofyNodePin* secondPin)
{
  lineConnection->editable = false;
  lineConnection->secondPin = secondPin;
  secondPin = NULL;
  closeLineConnection();
}

void GoofyNodeStageHandler::closeLineConnection()
{
  GoofyNodeOutConnection* newOutConnection;
  GoofyNodePin* inPin;
  GoofyNodePin* outPin;
  
  if(lineConnection->firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    outPin  = lineConnection->firstPin;
    inPin   = lineConnection->secondPin;
  }
  if(lineConnection->secondPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    outPin  = lineConnection->secondPin;
    inPin   = lineConnection->firstPin;
  }
  
  newOutConnection = new GoofyNodeOutConnection(outPin->parent, inPin->parent, inPin->pinId);
  outPin->parent->nodeOutConnections.push_back(newOutConnection);
  
  lineConnection->connection = newOutConnection;
  connections.push_back(lineConnection);
  inPin             = NULL;
  outPin            = NULL;
  newOutConnection  = NULL;
  lineConnection    =  NULL;
}

bool GoofyNodeStageHandler::checkLineConnectionPin()
{
  if(lineConnection != NULL)
  {
    if(lineConnection->secondPin == NULL)
      return true;
  }
  return false;
}

bool GoofyNodeStageHandler::checkMatch(GoofyNodePin* pin1, GoofyNodePin* pin2)
{
  int passed = 0;
  if(pin1->parent == pin2->parent)
  {
    ofLogVerbose(logVerboseModule, "same pin parent");
    passed++;
  }
  if(pin1->pinMode == pin2->pinMode)
  {
    ofLogVerbose(logVerboseModule, "same pin mode");
    passed++;
  }
  if(pin1->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    bool tempPassed = !pin1->parent->checkSameConnection(pin2->parent, pin2->pinId);
    if(!tempPassed)
    {
      ofLogVerbose(logVerboseModule, "same connection already done");
      passed++;
    }
  }
  else
  {
    bool tempPassed = !pin2->parent->checkSameConnection(pin1->parent, pin1->pinId);
    if(!tempPassed)
    {
      ofLogVerbose(logVerboseModule, "same connection already done");
      passed++;
    }
  }
  pin1 = NULL;
  pin2 = NULL;
  return passed == 0 ? true : false;
}

void GoofyNodeStageHandler::addLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2)
{
  GoofyNodeLineConnection* tempLineConnection = new GoofyNodeLineConnection(pin1, pin2);
  connections.push_back(tempLineConnection);
  pin1 = NULL;
  pin2 = NULL;
  tempLineConnection = NULL;
}

void GoofyNodeStageHandler::addPinConnection(GoofyNodePin* pin)
{
  if(lineConnection == NULL)
  {
    ofLogVerbose(logVerboseModule, "addPinConnection: first point");
    createNewLineConnection(pin);
  }
  else
  {
    if(!checkMatch(lineConnection->firstPin, pin))
    {
      removeTempLineConnection();
      return;
    }
    else
    {
      ofLogVerbose(logVerboseModule, "addPinConnection: second point");
      closeLineConnection(pin);
    }
    pin = NULL;
  }
}

void GoofyNodeStageHandler::addLayer(GoofyBridgeToNode* newLayer)
{
  layers.push_back(newLayer);
  newLayer = NULL;
}

GoofyBridgeToNode* GoofyNodeStageHandler::getLayerById(string layerId)
{
  int totLayers = layers.size();
  for(int a = 0; a < totLayers; a++)
  {
    if(layers[a]->bridgeId == layerId)
    {
      return layers[a];
    }
  }
  return NULL;
}

void GoofyNodeStageHandler::clearLayers()
{
  int totLayers = layers.size();
  for(int a = 0; a < totLayers; a++)
    layers[a] = NULL;
  layers.clear();
}

void GoofyNodeStageHandler::createConnections()
{
  vector<GoofyNodeOutConnection*>::iterator it = tempNodeOutConnection.begin();
  while(it != tempNodeOutConnection.end())
  {
    GoofyNodePin* pin1;
    GoofyNodePin* pin2;
    
    for(int a = 0; a < tempNode.size(); a++)
    {
      if(tempNode[a]->nodeId == (*it)->nodeInId)
      {
        pin1 = (GoofyNodePin*)tempNode[a]->nodes[0];
      }
      if(tempNode[a]->nodeId == (*it)->nodeOutId)
      {
        pin2 = (GoofyNodePin*)tempNode[a]->nodes[(*it)->pinID];
      }
    }
    createConnection(NULL, pin1, pin2, (*it)->pinID);
    it++;
  }
  int totTempNodes = tempNode.size();
  for(int a = totTempNodes-1; a>=0; a--)
  {
    tempNode[a] = NULL;
  }
  tempNode.clear();
}

void GoofyNodeStageHandler::createConnection(GoofyNodeLineConnection* tempLineConnection, GoofyNodePin* pin1, GoofyNodePin* pin2, int pinId)
{
  GoofyNodeOutConnection* newOutConnection = new GoofyNodeOutConnection(pin1->parent, pin2->parent, pinId);
  if(tempLineConnection == NULL)
    tempLineConnection = new GoofyNodeLineConnection(pin1, pin2);
  pin1->parent->nodeOutConnections.push_back(newOutConnection);
  tempLineConnection->connection = newOutConnection;
  connections.push_back(tempLineConnection);
  tempLineConnection = NULL;
  newOutConnection = NULL;
}


void GoofyNodeStageHandler::removeNodeLineConnection(GoofyNode* node)
{
  vector<GoofyNodeLineConnection*>::iterator it = connections.begin();
  while(it != connections.end())
  {
    if((*it)->firstPin->parent == node || (*it)->secondPin->parent == node)
    {
      if((*it)->firstPin->parent == node)
      {
        (*it)->secondPin->parent->removeAllNodeOutConnections(node);
      }
      else if((*it)->secondPin->parent == node)
      {
        (*it)->firstPin->parent->removeAllNodeOutConnections(node);
      }
      (*it)->connection = NULL;
      delete (*it);
      (*it) = NULL;
      connections.erase(it);
    }
    else
      it++;
  }
}
