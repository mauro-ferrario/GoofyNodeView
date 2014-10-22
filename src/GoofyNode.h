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



enum GoofyNodeGuiTypes
{
  GOOFY_SIMPLE_NODE,
  GOOFY_STAGE,
  GOOFY_PIN,
  GOOFY_LAYER,
  GOOFY_WIDGET,
  GOOFY_TIMER,
  GOOFY_BUTTON
};

class GoofyNode
{
public:
                      GoofyNode();
                      ~GoofyNode();
  void                setup(string name);
  void                enableMouseEvents();
  void                disableMouseEvents();
  void                setSize(int w, int h);
  bool                hitTest(int tx, int ty);
  float               getX();
  float               getY();
  GoofyNodeGuiTypes   type;
  void                setPos(ofVec2f newPos);
//  virtual void        addNodeOutConnection(GoofyNode* node);
  virtual void        update();
  virtual void        draw();
  virtual void        drawBackground();
  
  
  GoofyNode*          parent;
  
//  vector<GoofyNode*>  nodeOutConnections;
//  vector<float>       nodeOutConnectionsParams;
  
 // void                playMovie();

protected:
  virtual void        onPress(int x, int y, int button);
  float               width;
  float               height;
  ofVec2f             pos;
  bool                isMousePressed;
  bool                isMouseOver;
//  void                drawNodeOutConnections();
  
private:
  void                _mousePressed(ofMouseEventArgs &e);
  void                _mouseReleased(ofMouseEventArgs &e);
  void                _mouseMoved(ofMouseEventArgs &e);
  void                _mouseDragged(ofMouseEventArgs &e);
  string              name;
  
};



#endif /* defined(__ShadowTheatre2_0__GoofyNode__) */
