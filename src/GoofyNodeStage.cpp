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
  lineConnection    = NULL;
  logVerboseModule  = "GoofyNodeStage";
  nodeCounts        = 0;
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

void GoofyNodeStage::createNewLineConnection(GoofyNodePin* pin)
{
  lineConnection = new GoofyNodeLineConnection(pin);
  lineConnection->endPoint = lineConnection->startPoint;
  lineConnection->editable = true;
  pin = NULL;
}

void GoofyNodeStage::addLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2)
{
  GoofyNodeLineConnection* tempLineConnection = new GoofyNodeLineConnection(pin1, pin2);
  connections.push_back(tempLineConnection);
  pin1 = NULL;
  pin2 = NULL;
  tempLineConnection = NULL;
}

void GoofyNodeStage::addPinConnection(GoofyNodePin* pin)
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

void GoofyNodeStage::closeLineConnection(GoofyNodePin* pin)
{
  lineConnection->editable = false;
  lineConnection->secondPin = pin;
  pin = NULL;
  GoofyNodeOutConnection* newOutConnection;
  if(lineConnection->firstPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    newOutConnection = new GoofyNodeOutConnection(lineConnection->firstPin->parent, lineConnection->secondPin->parent, lineConnection->secondPin->pinId);
    lineConnection->firstPin->parent->nodeOutConnections.push_back(newOutConnection);
  }
  if(lineConnection->secondPin->pinMode == GOOFY_NODE_PIN_OUTPUT)
  {
    newOutConnection = new GoofyNodeOutConnection(lineConnection->secondPin->parent, lineConnection->firstPin->parent, lineConnection->firstPin->pinId);
    lineConnection->secondPin->parent->nodeOutConnections.push_back(newOutConnection);
  }
  lineConnection->connection = newOutConnection;
  newOutConnection = NULL;
  connections.push_back(lineConnection);
  lineConnection = NULL;
}


bool GoofyNodeStage::checkMatch(GoofyNodePin* pin1, GoofyNodePin* pin2)
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
      ofLogVerbose(logVerboseModule, "same connection already done");
    if(!tempPassed)
      passed++;
  }
  else
  {
    bool tempPassed = !pin2->parent->checkSameConnection(pin1->parent, pin1->pinId);
    if(!tempPassed)
      ofLogVerbose(logVerboseModule, "same connection already done");
    if(!tempPassed)
      passed++;
  }
  pin1 = NULL;
  pin2 = NULL;  
  return passed == 0 ? true : false;
}

void GoofyNodeStage::removeTempLineConnection()
{
  ofLogVerbose(logVerboseModule, "delete lineConnection");
  delete lineConnection;
  lineConnection = NULL;
}

void GoofyNodeStage::createConnections()
{
  vector<GoofyNodeOutConnection*>::iterator it = tempNodeOutConnection.begin();
  while(it != tempNodeOutConnection.end())
  {
    //addLineConnection
    cout << "**************" << endl;
    cout << (*it)->nodeInId << endl;
    cout << (*it)->nodeOutId<< endl;
    cout << (*it)->pinID << endl;
    cout << "Dentro" << endl;
    
    
   
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
    
    GoofyNodeOutConnection* newOutConnection = new GoofyNodeOutConnection(pin1->parent, pin2->parent, (*it)->pinID);
    
    
    GoofyNodeLineConnection* newConnection = new GoofyNodeLineConnection(pin1, pin2);
    pin1->parent->nodeOutConnections.push_back(newOutConnection);
    newConnection->connection = newOutConnection;
    connections.push_back(newConnection);
    newConnection = NULL;
    newOutConnection = NULL;
    it++;
  }
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
  
 // cout << "TOT CONNECTIONS =" << connections.size() << endl;
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

void GoofyNodeStage::addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage)
{
  GoofyNode::addNode(type, mainStage);
}
