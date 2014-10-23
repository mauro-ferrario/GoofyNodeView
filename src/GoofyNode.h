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
  GOOFY_NODE_PIN_INPUT,
  GOOFY_NODE_PIN_OUTPUT
};

class GoofyNode
{
public:
                      GoofyNode();
                      ~GoofyNode();
  virtual void        setup(string name);
  void                enableMouseEvents();
  void                disableMouseEvents();
  void                setSize(int w, int h);
  bool                hitTest(int tx, int ty);
  virtual void        addNode(GoofyNode* node, GoofyNodeStage* mainStage);
  float               getX();
  float               getY();
  GoofyNodeGuiTypes   type;
  void                setPos(ofVec2f newPos);
  virtual void        update();
  virtual void        draw();
  virtual void        drawAfterBackground();
  virtual void        drawBackground();
  virtual void        createSinglePin(int idFunction,  GoofyNodePinMode mode,  ofVec2f pos);
  virtual void        drawNodes();
  vector<GoofyNode*>  nodes;
  GoofyNode*          parent;
  vector<GoofyNode*>  nodeOutConnections;
  vector<int>         nodeOutConnectionsFunctionId;
  GoofyNodeStage*      mainStage;
  void                setMainStage(GoofyNodeStage* mainStage);
  GoofyBridgeToNode*  interactiveLayer;
  void                activeOutputs();
  bool                isDragging;
  ofVec2f             mouseDragStart;
  ofVec2f             dragOffset;
  void                removeMouseDragListener();
  
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
  
private:
  void                _mousePressed(ofMouseEventArgs &e);
  void                _mouseReleased(ofMouseEventArgs &e);
  void                _mouseMoved(ofMouseEventArgs &e);
  bool                _mouseDragged(ofMouseEventArgs &e);
  string              name;
  
  
};

#endif /* defined(__ShadowTheatre2_0__GoofyNode__) */
