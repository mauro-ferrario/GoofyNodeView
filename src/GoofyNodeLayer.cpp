//
//  GoofyNodeLayer.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNodeLayer.h"
#include "GoofyNodeStage.h"

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
  setSize(200,100);
  enableMouseEvents();
}

void GoofyNodeLayer::update()
{
  
}

void GoofyNodeLayer::onPress(int x, int y, int button)
{
  
}

void GoofyNodeLayer::saveSpecificInfo(ofxXmlSettings* xml)
{
  if(interactiveLayer != NULL)
    xml->addValue("interactiveLayerId", interactiveLayer->id);
  xml = NULL;
}

void GoofyNodeLayer::addNode(GoofyBridgeToNode* layer, GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
  GoofyNodeLayer* node = new GoofyNodeLayer();
  node->setup("Layer");
  node->setPos(ofVec2f(ofRandom(0,600),ofRandom(0,600)));
  node->interactiveLayer = layer;
  GoofyNode::addNode(node, mainStage);
  node->createPins();
}

void GoofyNodeLayer::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
  GoofyNode::addNode(node, mainStage);
}

void GoofyNodeLayer::createPins()
{
  if(interactiveLayer != NULL)
  {
    int totPins = interactiveLayer->functionNames.size();
    for(int a = 0; a < totPins; a++)
    {
      createSinglePin(a, GOOFY_NODE_PIN_INPUT, ofVec2f(15*a, -10),interactiveLayer->functionNames[a]);
    }
  }
}

void GoofyNodeLayer::mouseDragged(int x, int y, int button)
{
  
}