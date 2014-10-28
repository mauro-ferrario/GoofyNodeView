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
  disableMouseEvents();
  disableKeyboardEvents();
  parent    = NULL;
  mainStage = NULL;
}

void GoofyNode::removeAllNodeOutConnections(GoofyNode* nodeToRemove)
{
  int totConnections = nodeOutConnections.size();
  for(int a = totConnections-1; a>=0; a--)
  {
    if(nodeOutConnections[a]->nodeOut == nodeToRemove)
    {
      removeConnection(nodeOutConnections[a]);
    }
  }
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
  ofRemoveListener(ofEvents().mousePressed, this, &GoofyNode::_mousePressed, 1000 - type);
  ofRemoveListener(ofEvents().mouseMoved, this, &GoofyNode::_mouseMoved, 1000 - type);
  ofRemoveListener(ofEvents().mouseDragged, this, &GoofyNode::_mouseDragged, 1000 - type);
  ofRemoveListener(ofEvents().mouseReleased, this, &GoofyNode::_mouseReleased, 1000 - type);
}

void GoofyNode::enableKeyboardEvents()
{
  ofAddListener(ofEvents().keyPressed, this, &GoofyNode::_keyPressed,100);
}

void GoofyNode::disableKeyboardEvents()
{
  ofRemoveListener(ofEvents().keyPressed, this, &GoofyNode::_keyPressed,100);
}

void GoofyNode::removeNodeChildren()
{
  int totNodes = nodes.size();
  for(int a = totNodes - 1; a >= 0; a--)
  {
    cout << nodes[a]->type << endl;
    nodes[a]->removeNodeChildren();
    mainStage->removeNodeLineConnection(nodes[a]);
    delete nodes[a];
    nodes[a] = NULL;
  }
  nodes.clear();
}

bool GoofyNode::_keyPressed(ofKeyEventArgs &e)
{
  if(e.key == OF_KEY_BACKSPACE && selected &&type != GOOFY_STAGE)
  {
    mainStage->removeNode(this);
  }
  return false;
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
    if(nodes[a])
    {
      nodes[a]->update();
      nodes[a]->draw();
    }
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
    selected = true;
    onReleaseIn(x, y, button);
  }
  else
  {
    selected = false;
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
  logVerboseModule  = "";
  this->name        = name;
  mouseDragStart    = ofVec2f(0,0);
  dragOffset        = ofVec2f(0,0);
  isDraggingIn      = false;
  parent            = NULL;
  pos.x             = 0;
  pos.y             = 0;
  type              = GOOFY_SIMPLE_NODE;
  selected          = false;
  enableKeyboardEvents();
}

void GoofyNode::update()
{
}

void GoofyNode::draw()
{
  ofPushStyle();
  ofPushMatrix();
  ofTranslate(pos - dragOffset);
  drawBackground();
  drawAfterBackground();
  drawNodes();
  if(selected&&type != GOOFY_STAGE)
    drawSelected();
  ofPopMatrix();
}

void GoofyNode::drawSelected()
{
  ofPushStyle();
  ofSetColor(255,100);
  ofRect(0,0,width, height);
  ofPopStyle();
}

void GoofyNode::drawAfterBackground()
{
  
}

GoofyNode* GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos)
{
  return createSinglePin(idFunction, mode, pos, ofToString(idFunction));
}

GoofyNode* GoofyNode::createSinglePin(int idFunction, GoofyNodePinMode mode, ofVec2f pos, string name)
{
  GoofyNodePin* newPin = new GoofyNodePin(mode);
  newPin->setup(name);
  newPin->setPos(pos);
  newPin->pinId = idFunction;
  newPin->parent = this;
  this->addNode(newPin, this->mainStage);
  return newPin;
}

GoofyNode* GoofyNode::addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage, ofVec2f pos, string name)
{
  GoofyNode* node;
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
        node = createSinglePin(0, GOOFY_NODE_PIN_NOT_DEFINED, ofVec2f(0,0));
      }
      break;
    }
    case GOOFY_DELAY:
    {
      break;
    }
    case GOOFY_BUTTON:
    {
      node = addNode(GoofyNodeButton::createButton(pos, this->mainStage, name), this->mainStage);
      break;
    }
    default:
    {
      ofLogVerbose(logVerboseModule, "can't add this type!");
      break;
    }
  }
  return node;
}

GoofyNode* GoofyNode::addNode(GoofyNode* node, GoofyNodeStage* mainStage, ofVec2f pos, string name)
{
  node->parent = this;
  node->setMainStage(mainStage);
  if(node->nodeId == "")
  {
    node->nodeId = generateId();
  }
  if(node->type != GOOFY_PIN)
    mainStage->tempNode.push_back(node);
  nodes.push_back(node);
  return node;
}

string GoofyNode::generateId()
{
  return ofToString(ofGetYear())+ofToString(ofGetMonth())+ofToString(ofGetDay())+ofToString(ofGetHours())+ofToString(ofGetMinutes())+ofToString(ofGetSeconds())+"-"+ofToString(mainStage->tempNode.size());
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
    switch(nodeOutConnections[a]->nodeOut->type)
    {
      case GOOFY_DELAY:
      {
        GoofyNodeDelay* delay = (GoofyNodeDelay*)nodeOutConnections[a]->nodeOut;
        delay->activeFunction(nodeOutConnections[a]->pinID);
        delay = NULL;
        break;
      }
      case GOOFY_LAYER:
      {
        GoofyNodeLayer* tempNodeLayer = (GoofyNodeLayer*)(nodeOutConnections[a]->nodeOut);
        GoofyBridgeToNode* tempLayer = tempNodeLayer->interactiveLayer;
        tempLayer->activeFunction(nodeOutConnections[a]->pinID);
        tempNodeLayer = NULL;
        tempLayer = NULL;
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
    if(nodeOutConnections[a]->nodeOut == node && (nodeOutConnections[a]->pinID == pinID))
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
    xml->addValue("nodeId", ofToString(nodeOutConnections[a]->nodeOut->nodeId));
    xml->addValue("pinId", nodeOutConnections[a]->pinID);
    xml->popTag();
  }
  xml->popTag();
}

void GoofyNode::loadFromXML(ofxXmlSettings* xml, int nodeXMLPos)
{
  xml->pushTag("node", nodeXMLPos);
  int type = xml->getValue("type", 0);
  string tempId =  xml->getValue("id","");
  if(type == GOOFY_STAGE)
    this->nodeId = xml->getValue("id","");
  //cout << "ID FROM XML" << this->nodeId << endl;
  ofVec2f pos;
  pos.x = xml->getValue("position:x", 0);
  pos.y = xml->getValue("position:y", 0);
  if(type == GOOFY_STAGE)
  {
    mainStage = (GoofyNodeStage*)this;
  }
  else
  {
    if(type == GOOFY_BUTTON)
      addNode((GoofyNodeGuiTypes)type, mainStage, pos)->nodeId =  xml->getValue("id","");
    else if(type == GOOFY_DELAY)
    {
      float delay =  xml->getValue("delay",0);
      addNode(GoofyNodeDelay::createDelay(pos, this->mainStage, delay, name), this->mainStage)->nodeId =  xml->getValue("id","");
    }
    else if(type == GOOFY_LAYER)
    {
      // Sono per forza nello stage
      GoofyNodeStage* stage = (GoofyNodeStage*)this;
      GoofyBridgeToNode* interactiveLayer;
      string idToFind = xml->getValue("interactiveLayerId","");
      GoofyBridgeToNode* foundLayer = mainStage->getLayerById(idToFind);
      if(foundLayer)
      {
        interactiveLayer = foundLayer;
        GoofyNode* tempNode = stage->addNode(interactiveLayer);
        tempNode->nodeId = xml->getValue("interactiveLayerId","");
      }
      else
      {
        ofLogVerbose(logVerboseModule, "interactive layer not found!");
      }
      foundLayer        = NULL;
      interactiveLayer  = NULL;
    }
  }
  
  
  int totOutConnections = xml->getNumTags("outConnections");
  
  if(totOutConnections > 0)
  {
   // cout << "Create connections " << endl;
    xml->pushTag("outConnections");
    int totConnection = xml->getNumTags("outConnection");
    for(int i = 0; i < totConnection; i++)
    {
      //cout << "Boh " << i << endl;
      xml->pushTag("outConnection",i);
     // cout << xml->getValue("nodeId", "") << endl;;
     // cout << xml->getValue("pinId", 0) << endl;
      GoofyNodeOutConnection* tempOutConnection = new GoofyNodeOutConnection(tempId, xml->getValue("nodeId", ""), xml->getValue("pinId", 0));
      
      mainStage->tempNodeOutConnection.push_back(tempOutConnection);
      tempOutConnection = NULL;
      xml->popTag();
    }
    xml->popTag();
  }
  
  if(type == GOOFY_STAGE); // || type == GOOFY_LAYER)
  {
    xml->pushTag("nodes");
    int nodes = xml->getNumTags("node");;
    if(nodes > 0)
    {
      for(int i = 0; i < nodes; i++)
      {
        loadFromXML(xml, i);
      }
    }
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