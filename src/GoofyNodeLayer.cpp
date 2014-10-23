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

void GoofyNodeLayer::onPress(int x, int y, int button)
{
  
}

void GoofyNodeLayer::addNode(GoofyBridgeToNode* layer, GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
  GoofyNodeLayer* node = new GoofyNodeLayer();
  node->setPos(ofVec2f(ofRandom(0,600),ofRandom(0,600)));
  node->setSize(200,100);
  node->enableMouseEvents();
  node->interactiveLayer = layer;
  GoofyNode::addNode(node, mainStage);
  node->createPins();
}

void GoofyNodeLayer::createPins()
{
  if(interactiveLayer != NULL)
  {
    int totPins = interactiveLayer->functionNames.size();
    cout << "MAIN STAGE " << mainStage << endl;
    for(int a = 0; a < totPins; a++)
    {
      createSinglePin(a, GOOFY_NODE_PIN_INPUT, ofVec2f(15*a, -10));
    }
  }
}

void GoofyNodeLayer::drawBackground()
{
  GoofyNode::drawBackground();
}

void GoofyNodeLayer::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  cout << "CAZZO " << endl;
  this->mainStage = mainStage;
  GoofyNode::addNode(node, mainStage);
}

void GoofyNodeLayer::mouseDragged(int x, int y, int button)
{
  
}