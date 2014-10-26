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
  virtual GoofyNode*        addNode(GoofyBridgeToNode* layer);
  virtual GoofyNode*        addNode(GoofyNode* node);
  virtual void        mouseDragged(int x, int y, int button);
  void                removeTempLineConnection();
  virtual void        onReleaseIn(int x, int y, int button);
  void                createNewLineConnection(GoofyNodePin* pin);
  void                closeLineConnection(GoofyNodePin* pin);
  bool                checkLineConnectionPin();
  ofxMSATimer         timer;
  float               timerStart;
  bool                checkRelease;
  int                 countDrag;
  bool                checkMatch(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage);
  void                addLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2);
  
  void                addPinConnection(GoofyNodePin* pin);
  long int            nodeCounts;
  
  GoofyNodeLineConnection* lineConnection;
  vector<GoofyNodeLineConnection*> connections;
  vector<GoofyNode*>               tempNode;
  vector<GoofyNodeOutConnection*>  tempNodeOutConnection;
  void                  createConnections();
  vector<GoofyBridgeToNode*> layers;
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
