//
//  GoofyNodeStage.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyNodeStage__
#define __ShadowTheatre2_0__GoofyNodeStage__

#include "GoofyNodeLayer.h"
#include "GoofyNodePin.h"
#include "ofxMSATimer.h"
#include "GoofyNodeLineConnection.h"

class GoofyNodePin;

class GoofyNodeStage: public GoofyNodeLayer
{
public:
                      GoofyNodeStage();
                      ~GoofyNodeStage();
  void                update();
  void                draw();
  void                setup(string name);
  void                drawBackground();
  virtual void        addNode(GoofyBridgeToNode* layer);
  virtual void        addNode(GoofyNode* node);
  virtual void        mouseDragged(int x, int y, int button);
  void                removeTempLineConnection();
  virtual void        onReleaseIn(int x, int y, int button);
  bool                checkLineConnectionPin();
  ofxMSATimer         timer;
  float               timerStart;
  bool                checkRelease;
  int                 countDrag;
  
  
  void                addPinConnection(GoofyNodePin* pin);
  
  GoofyNodeLineConnection* lineConnection;
  vector<GoofyNodeLineConnection*> connections;
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
