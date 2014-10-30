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
  GoofyNodeStage("", ofGetWindowWidth(), ofGetWindowHeight());
}

GoofyNodeStage::GoofyNodeStage(string name, int width, int height)
{
  mainStage         = this;
  GoofyNode::logVerboseModule  = "GoofyNodeStage";
  countDrag         = 0;
  setup(name, width, height);
}

GoofyNodeStage::~GoofyNodeStage()
{
  
}

void GoofyNodeStage::setup(string name, int width, int height)
{
  setSize(width, height);
  GoofyNode::setup(mainStage, GOOFY_STAGE, name);
}

void GoofyNodeStage::drawBackground()
{
  ofPushStyle();
  ofSetColor(255,0,0, 100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

GoofyNode* GoofyNodeStage::addNode(GoofyBridgeToNode* layer)
{
  return GoofyNodeLayer::addNode(layer, this);
}

GoofyNode* GoofyNodeStage::addNode(GoofyNode* node)
{
  return GoofyNodeLayer::addNode(node, this);
}

void GoofyNodeStage::loadFromXML(ofxXmlSettings* xml)
{
  GoofyNode::loadFromXML(xml);
  GoofyNodeStageHandler::createConnections();
  GoofyNodeStageHandler::clearLayers();
}

void GoofyNodeStage::update()
{
  GoofyNodeStageHandler::update();
}

void GoofyNodeStage::mouseDragged(int x, int y, int button)
{
  GoofyNodeStageHandler::mouseDragged(x, y, button);
}

void GoofyNodeStage::draw()
{
  GoofyNode::draw();
  GoofyNodeStageHandler::draw();
  vector<GoofyNodeLineConnection*>::iterator it = connections.begin();
  while(it != connections.end())
  {
    if((*it)->toRemove)
    {
      delete (*it);
      (*it) = NULL;
      connections.erase(it);
    }
    else
    {
      (*it)->draw();
      it++;
    }
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

void GoofyNodeStage::removeNode(GoofyNode* node)
{
  removeNodeLineConnection(node);
  node->removeNodeChildren();
  vector<GoofyNode*>::iterator itNodes = nodes.begin();
  
  while(itNodes != nodes.end())
  {
    if((*itNodes) == node)
    {
      nodes.erase(itNodes);
    }
    else
      itNodes++;
  }
  delete node;
  node = NULL;
}

