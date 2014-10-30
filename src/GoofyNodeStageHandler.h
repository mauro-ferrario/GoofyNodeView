//
//  GoofyNodeStageHandler.h
//  GoofyNodeTest
//
//  Created by XXX on 29/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodeStageHandler__
#define __GoofyNodeTest__GoofyNodeStageHandler__

#include "ofMain.h"
#include "GoofyNodeLayer.h"
#include "GoofyNodePin.h"
#include "ofxMSATimer.h"
#include "GoofyNodeLineConnection.h"

class GoofyNodeStageHandler
{
public:
                                    GoofyNodeStageHandler();
                                    ~GoofyNodeStageHandler();
  void                              removeTempLineConnection();
  void                              createNewLineConnection(GoofyNodePin* pin);
  void                              closeLineConnection(GoofyNodePin* pin);
  void                              closeLineConnection();
  bool                              checkLineConnectionPin();
  bool                              checkMatch(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                              addLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                              addPinConnection(GoofyNodePin* pin);
  void                              addLayer(GoofyBridgeToNode* newLayer);
  GoofyBridgeToNode*                getLayerById(string layerId);
  void                              clearLayers();
  void                              mouseDragged(int x, int y, int button);
  void                              update();
  void                              draw();
  void                              removeNode(GoofyNode* node);
  void                              removeNodeLineConnection(GoofyNode* node);
  void                              createConnections();
  void                              createConnection(GoofyNodeLineConnection* tempLineConnection, GoofyNodePin* pin1, GoofyNodePin* pin2, int pinId);
  ofxMSATimer                       timer;
  float                             timerStart;
  bool                              checkRelease;
  GoofyNodeLineConnection*          lineConnection;
  vector<GoofyNodeLineConnection*>  connections;
  vector<GoofyNode*>                tempNode; // Devo rimuovere anche da qui gli elementi rimossi
  vector<GoofyNodeOutConnection*>   tempNodeOutConnection;
  vector<GoofyBridgeToNode*>        layers;
  string                            logVerboseModule;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeStageHandler__) */
