//
//  GoofyNode.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyNode__
#define __ShadowTheatre2_0__GoofyNode__

#include "ofMain.h"
#include "GoofyBridgeToNode.h"
#include "GoofyNodeOutConnection.h"
#include "ofxXmlSettings.h"

class GoofyNodeStage;


enum GoofyNodeGuiTypes
{
  GOOFY_SIMPLE_NODE,
  GOOFY_STAGE,
  GOOFY_PIN,
  GOOFY_LAYER,
  GOOFY_WIDGET,
  GOOFY_DELAY,
  GOOFY_BUTTON
};

enum GoofyNodePinMode
{
  GOOFY_NODE_PIN_NOT_DEFINED,
  GOOFY_NODE_PIN_INPUT,
  GOOFY_NODE_PIN_OUTPUT
};


class GoofyNode
{
public:
  
                      GoofyNode();
      virtual                ~GoofyNode();
  virtual void        setup(GoofyNodeStage* mainStage = NULL, string name = "");
//  virtual void        setup(string name);
  void                enableKeyboardEvents();
  void                disableKeyboardEvents();
  void                enableMouseEvents();
  void                disableMouseEvents();
  void                setSize(int w, int h);
  bool                hitTest(int tx, int ty);
  GoofyNode*        addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage, ofVec2f pos = ofVec2f(0,0), string name = "");
  GoofyNode*        addNode(GoofyNode* node, GoofyNodeStage* mainStage, ofVec2f pos = ofVec2f(0,0), string name = "");
  float               getX();
  float               getY();
  GoofyNodeGuiTypes   type;
  void                setPos(ofVec2f newPos);
  virtual void        update();
  virtual void        draw();
  virtual void        drawAfterBackground();
  virtual void        drawBackground();
  virtual GoofyNode*        createSinglePin(int idFunction,  GoofyNodePinMode mode,  ofVec2f pos);
  virtual GoofyNode*        createSinglePin(int idFunction,  GoofyNodePinMode mode,  ofVec2f pos, string name);
  virtual void        drawNodes();
  void                removeConnection(GoofyNodeOutConnection* connection);
  vector<GoofyNode*>  nodes;
  GoofyNode*          parent;
  vector<GoofyNodeOutConnection*>  nodeOutConnections;
  static bool                removeEqualElement(GoofyNodeOutConnection* connection1, GoofyNodeOutConnection* connection2);
  bool                checkSameConnection(GoofyNode* node, int pinID);
  GoofyNodeStage*     mainStage;
  void                setMainStage(GoofyNodeStage* mainStage);
  void                activeOutputs();
  bool                isDraggingIn;
  ofVec2f             mouseDragStart;
  ofVec2f             dragOffset;
  void                removeMouseDragListener();
  string              logVerboseModule;
  void                saveInfo(ofxXmlSettings* xml, int tagPos = 0);
  void                saveOutConnections(ofxXmlSettings* xml);
  virtual void        saveSpecificInfo(ofxXmlSettings* xml);
  string              nodeId;
  virtual void        loadFromXML(ofxXmlSettings* xml, int nodeXMLPos = 0);
  bool                selected;
  void                drawSelected();
  void                removeNodeChildren();
  void                removeAllNodeOutConnections(GoofyNode* nodeToRemove);
  string              generateId();
  
  
protected:
  virtual void        onPressIn(int x, int y, int button);
  virtual void        onPressOut(int x, int y, int button);
  virtual void        mouseDragged(int x, int y, int button);
  virtual void        onReleaseIn(int x, int y, int button);
  float               width;
  float               height;
  bool                isMousePressed;
  bool                isMouseOver;
  ofVec2f             pos;
  string              name;
  
private:
  void                _mousePressed(ofMouseEventArgs &e);
  void                _mouseReleased(ofMouseEventArgs &e);
  void                _mouseMoved(ofMouseEventArgs &e);
  bool                _mouseDragged(ofMouseEventArgs &e);
  bool                _keyPressed(ofKeyEventArgs &e);
  ofxXmlSettings*     xml;
};

#endif /* defined(__ShadowTheatre2_0__GoofyNode__) */
