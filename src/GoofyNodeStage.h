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
  void                              update();
  void                              draw();
  void                              setup(string name);
  void                              drawBackground();
  GoofyNode*                        addNode(GoofyBridgeToNode* layer);
  GoofyNode*                        addNode(GoofyNode* node);
  void                              addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage);
  void                              mouseDragged(int x, int y, int button);
  void                              onReleaseIn(int x, int y, int button);
  void                              loadFromXML(ofxXmlSettings* xml);
  int                               countDrag;
  
  void                              removeTempLineConnection();
  void                              createNewLineConnection(GoofyNodePin* pin);
  void                              closeLineConnection(GoofyNodePin* pin);
  bool                              checkLineConnectionPin();
  ofxMSATimer                       timer;
  float                             timerStart;
  bool                              checkRelease;
  bool                              checkMatch(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                              addLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                              addPinConnection(GoofyNodePin* pin);
  void                              addLayer(GoofyBridgeToNode* newLayer);
  GoofyBridgeToNode*                getLayerById(string layerId);
  void                              clearLayers();
  
  GoofyNodeLineConnection*          lineConnection;
  vector<GoofyNodeLineConnection*>  connections;
  vector<GoofyNode*>                tempNode; // Devo rimuovere anche da qui gli elementi rimossi
  vector<GoofyNodeOutConnection*>   tempNodeOutConnection;
  void                              createConnections();
  vector<GoofyBridgeToNode*>        layers;
  void                              removeNode(GoofyNode* node);
  void                              removeNodeLineConnection(GoofyNode* node);
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
