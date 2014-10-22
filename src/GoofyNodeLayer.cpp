//
//  GoofyNodeLayer.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeLayer.h"

GoofyNodeLayer::GoofyNodeLayer()
{
}

GoofyNodeLayer::~GoofyNodeLayer()
{
  
}

void GoofyNodeLayer::setup(string name)
{
  GoofyNode::setup(name);
  type = GOOFY_LAYER;
}

void GoofyNodeLayer::update()
{
  
}

void GoofyNodeLayer::draw()
{
  ofPushMatrix();
  ofTranslate(pos);
  drawBackground();
  drawNodes();
  ofPopMatrix();
}

void GoofyNodeLayer::drawNodes()
{
  for(int a = 0; a < nodes.size(); a++)
  {
    nodes[a]->update();
    nodes[a]->draw();
  }
}

void GoofyNodeLayer::onPress(int x, int y, int button)
{
  
}

void GoofyNodeLayer::addNode(GoofyNode* node)
{
  node->parent = this;
  nodes.push_back(node);
}

void GoofyNodeLayer::addNode(GoofyBridgeToNode* layer)
{
  GoofyNodeLayer* node = new GoofyNodeLayer();
  node->setPos(ofVec2f(ofRandom(0,600),ofRandom(0,600)));
  node->setSize(200,100);
  node->interactiveLayer = layer;
  node->createPins();
  addNode(node);
}

void GoofyNodeLayer::createPins()
{
  if(interactiveLayer != NULL)
  {
    int totPins = interactiveLayer->functionNames.size();
    for(int a = 0; a < totPins; a++)
      createSinglePin(a, GOOFY_NODE_PIN_INPUT);
  }
}

void GoofyNodeLayer::createSinglePin(int idFunction, GoofyNodePinMode mode)
{
  GoofyNodePin* newPin = new GoofyNodePin(mode);
  newPin->setup(ofToString(idFunction));
  newPin->setSize(10,10);
  newPin->setPos(ofVec2f(idFunction*15, -10));
  newPin->enableMouseEvents();
  addNode(newPin);
}

void GoofyNodeLayer::drawBackground()
{
  GoofyNode::drawBackground();
}