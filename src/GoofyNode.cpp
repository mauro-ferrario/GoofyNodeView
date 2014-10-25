//
//  GoofyNode.cpp
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#include "GoofyNode.h"
#include "GoofyNodePin.h"
#include "GoofyNodeStage.h"
#include "GoofyNodeDelay.h"
#include "GoofyNodeButton.h"

GoofyNode::GoofyNode()
{
  logVerboseModule = "GoofyNode:";
}

GoofyNode::~GoofyNode()
{
  
}

void GoofyNode::setMainStage(GoofyNodeStage* mainStage)
{
  this->mainStage = mainStage;
}

void GoofyNode::enableMouseEvents()
{
  ofAddListener(ofEvents().mousePressed, this, &GoofyNode::_mousePressed, 1000 - type);
  ofAddListener(ofEvents().mouseMoved, this, &GoofyNode::_mouseMoved, 1000 - type);
  ofAddListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged, 1000 - type);
  ofAddListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased, 1000 - type);
}

void GoofyNode::disableMouseEvents()
{
  ofRemoveListener(ofEvents().mousePressed, this, &GoofyNode::_mousePressed);
  ofRemoveListener(ofEvents().mouseMoved, this, &GoofyNode::_mouseMoved);
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased);
}

void GoofyNode::removeMouseDragListener()
{
  ofRemoveListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged);
}

void GoofyNode::setSize(int w, int h)
{
  width   = w;
  height  = h;
}

void GoofyNode::drawNodes()
{
  for(int a = 0; a < nodes.size(); a++)
  {
    nodes[a]->update();
    nodes[a]->draw();
  }
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
      if(type != GOOFY_PIN  && type != GOOFY_STAGE)
      {
        mouseDragStart = ofVec2f(x, y);
      }
      isMousePressed = true;
      onPressIn(x, y, button);
    }
  }
  else
  {
    onPressOut(x, y, button);
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
  
  mainStage->countDrag = 0;
  
  if(isDraggingIn && dragOffset.length() != 0)
  {
    if(type != GOOFY_PIN  && type != GOOFY_STAGE)
    {
      pos -= dragOffset;
      dragOffset = ofVec2f(0,0);
    }
  }
  
  if(hitTest(x, y))
  {
    onReleaseIn(x, y, button);
  }
  else
  {
  }
  isMousePressed = false;
  isDraggingIn = false;
}

void GoofyNode::_mouseMoved(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;
  
  if(hitTest(x, y))
  {
    isMouseOver = true;
  }
  else
  {
    isMouseOver = false;
  }
}

bool GoofyNode::_mouseDragged(ofMouseEventArgs &e)
{
  int x = e.x;
  int y = e.y;
  int button = e.button;

  
  if(isDraggingIn)
  {
    if(type != GOOFY_PIN && type != GOOFY_STAGE)
    {
      dragOffset = mouseDragStart - ofVec2f(x,y);
    }
  }
  
  if(hitTest(x, y))
  {
    if(!isDraggingIn)
    {
      mainStage->countDrag++;
      if(mainStage->countDrag > 1 && type != GOOFY_PIN  && type != GOOFY_STAGE)
        return true;
    }
    
    isMouseOver = true;
    if(isMousePressed)
      isDraggingIn  = true;
    
  }
  else
  {
    isMouseOver = false;
  }
  mouseDragged(x, y, button);
}

float GoofyNode::getX()
{
  if(parent == NULL)
  {
    return pos.x + dragOffset.x;
  }
  else
  {
    return pos.x + parent->getX() - parent->dragOffset.x;
  }
}

float GoofyNode::getY()
{
  if(parent == NULL)
  {
    return pos.y + dragOffset.y;
  }
  else
  {
    return pos.y + parent->getY() - parent->dragOffset.y;
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
  logVerboseModule = "";
  this->name  = name;
  mouseDragStart = ofVec2f(0,0);
  dragOffset = ofVec2f(0,0);
  isDraggingIn  = false;
  parent      = NULL;
  pos.x       = 0;
  pos.y       = 0;
  type        = GOOFY_SIMPLE_NODE;
}

void GoofyNode::update()
{
}

void GoofyNode::draw()
{
  ofPushMatrix();
  ofTranslate(pos - dragOffset);
  drawBackground();
  drawAfterBackground();
  drawNodes();
  ofPopMatrix();
}

void GoofyNode::drawAfterBackground()
{
  
}

void GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos)
{
  createSinglePin(idFunction, mode, pos, ofToString(idFunction));
}

void GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos, string name)
{
  GoofyNodePin* newPin = new GoofyNodePin(mode);
  newPin->setup(name);
  newPin->setSize(10,10);
  newPin->setPos(pos);
  newPin->pinId = idFunction;
  newPin->parent = this;
  this->addNode(newPin, this->mainStage);
}

void GoofyNode::addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage)
{
  switch(type)
  {
    case GOOFY_STAGE:
    {
      ofLogVerbose(logVerboseModule, "can't add this type!");
      break;
    }
    case GOOFY_PIN:
    {
      if(this->type == GOOFY_STAGE)
      {
        ofLogVerbose(logVerboseModule, "can't add pin to this element!");
      }
      else
      {
        createSinglePin(0, GOOFY_NODE_PIN_NOT_DEFINED, ofVec2f(0,0));
      }
      break;
    }
    case GOOFY_DELAY:
    {
      GoofyNodeDelay* delay = new GoofyNodeDelay(this->mainStage);
      delay->setup("");
      delay->setPos(ofVec2f(10,10));
      this->addNode(delay, this->mainStage);
      break;
    }
    case GOOFY_BUTTON:
    {
      createSingleButton();
      break;
    }
    default:
    {
      ofLogVerbose(logVerboseModule, "can't add this type!");
      break;
    }
  }
}

void GoofyNode::createSingleButton() // Questo potrebbe essere un metodo dinamico della classe button
{
  GoofyNodeButton* btn = new GoofyNodeButton(this->mainStage);
  btn->setup("button");
  btn->setPos(ofVec2f(10,10));
  addNode(btn, this->mainStage);
}

void GoofyNode::addNode(GoofyNode* node, GoofyNodeStage* mainStage)
{
  node->parent = this;
  node->setMainStage(mainStage);
  node->nodeId = ofToString(ofGetYear())+ofToString(ofGetMonth())+ofToString(ofGetDay())+ofToString(ofGetHours())+ofToString(ofGetMinutes())+ofToString(ofGetSeconds())+"-"+ofToString(mainStage->nodeCounts);
  mainStage->nodeCounts++;
  nodes.push_back(node);
}

void GoofyNode::drawBackground()
{
  ofPushStyle();
  ofSetColor(100);
  ofRect(0,0, width, height);
  ofPopStyle();
}

void GoofyNode::activeOutputs()
{
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    switch(nodeOutConnections[a]->node->type)
    {
      case GOOFY_DELAY:
      {
        GoofyNodeDelay* delay = (GoofyNodeDelay*)nodeOutConnections[a]->node;
        delay->activeFunction(nodeOutConnections[a]->pinID);
        delay = NULL;
        break;
      }
      case GOOFY_LAYER:
      {
        GoofyBridgeToNode* tempLayer = nodeOutConnections[a]->node->interactiveLayer;
        tempLayer->activeFunction(nodeOutConnections[a]->pinID);
        break;
      }
      case GOOFY_SIMPLE_NODE:
        break;
    }
  }
}

bool removeEqualElement(GoofyNodeOutConnection* connection1, GoofyNodeOutConnection* connection2)
{
  if(connection1 == connection2)
    return true;
  return false;
}

void GoofyNode::removeConnection(GoofyNodeOutConnection* connection)
{
  delete connection;
  nodeOutConnections.erase(std::remove(nodeOutConnections.begin(), nodeOutConnections.end(), connection), nodeOutConnections.end());
  connection = NULL;
}

bool GoofyNode::checkSameConnection(GoofyNode* node, int pinID)
{
  vector<GoofyNodeOutConnection*>::iterator it = nodeOutConnections.begin();
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    if(nodeOutConnections[a]->node == node && (nodeOutConnections[a]->pinID == pinID))
      return true;
  }
  
//  if(nodeOutConnections.size() > 0)
//  {
//    while(it != nodeOutConnections.end());
//    {
//      //if((*it)->node == node && ((*it)->pinID == pinID))
//        //return true;
//      it++;
//    }
//  }
  return false;
}

void GoofyNode::saveInfo(ofxXmlSettings* xml, int tagPos)
{
  xml->addTag("node");
  xml->pushTag("node", tagPos);
  xml->addValue("type", type);
  xml->addValue("id", nodeId);
  xml->addTag("position");
  xml->pushTag("position",0);
  xml->addValue("x", getX());
  xml->addValue("y", getY());
  xml->popTag();
  
  
  saveOutConnections(xml);
  
  xml->addTag("nodes");
  xml->pushTag("nodes", 0);
  
  for(int a = 0; a < nodes.size(); a++)
  {
    nodes[a]->saveInfo(xml, a);
  }
  xml->popTag();
  saveSpecificInfo(xml);
  xml->popTag();
  xml = NULL;
}

void GoofyNode::saveOutConnections(ofxXmlSettings* xml)
{
  int pos = xml->addTag("outConnections");
  xml->pushTag("outConnections", pos);
  for(int a = 0; a < nodeOutConnections.size(); a++)
  {
    int contOutConnection = xml->addTag("outConnection");
    xml->pushTag("outConnection", contOutConnection);
    xml->addValue("nodeId", ofToString(nodeOutConnections[a]->node->nodeId));
    xml->addValue("pinId", nodeOutConnections[a]->pinID);
    xml->popTag();
  }
  xml->popTag();
}

void GoofyNode::saveSpecificInfo(ofxXmlSettings* xml)
{
  xml = NULL;
}

void GoofyNode::onPressIn(int x, int y, int button)
{
  
}

void GoofyNode::onPressOut(int x, int y, int button)
{
  
}

void GoofyNode::mouseDragged(int x, int y, int button)
{
  
}

void GoofyNode::onReleaseIn(int x, int y, int button)
{
  
}