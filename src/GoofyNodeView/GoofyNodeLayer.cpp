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
  GoofyNodeLayer(NULL, NULL);
}

GoofyNodeLayer::GoofyNodeLayer(GoofyNodeStage* mainStage, GoofyBridgeToNode* layer, string name)
{
  interactiveLayer = layer;
  setup(mainStage, name);
}

GoofyNodeLayer::~GoofyNodeLayer()
{
  
}

void GoofyNodeLayer::setup(GoofyNodeStage* mainStage, string name)
{
  GoofyNode::setup(mainStage, GOOFY_LAYER, name);
  setSize(200,100);
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
  {
    xml->setValue("id", interactiveLayer->id);
    xml->addValue("interactiveLayerId", interactiveLayer->id);
  }
  xml = NULL;
}

GoofyNode* GoofyNodeLayer::addNode(GoofyBridgeToNode* layer, GoofyNodeStage* mainStage)
{
  GoofyNodeLayer* node = new GoofyNodeLayer(mainStage, layer, "Layer");
  node->setPos(ofVec2f(ofRandom(0,600),ofRandom(0,600)));
  GoofyNode::addNode(node, mainStage);
  node->createPins();
  node->nodeId = layer->id;
  layer = NULL;
  mainStage = NULL;
  return (GoofyNode*)node;
}

GoofyNode* GoofyNodeLayer::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  return GoofyNode::addNode(node, mainStage);
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