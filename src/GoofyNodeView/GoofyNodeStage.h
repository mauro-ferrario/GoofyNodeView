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
#include "GoofyNodeStageHandler.h"

class GoofyNodeStage: public GoofyNodeLayer, public GoofyNodeStageHandler
{
public:
                                    GoofyNodeStage();
                                    GoofyNodeStage(string name, int width, int height);
                                    ~GoofyNodeStage();
  void                              update();
  void                              draw();
  void                              setup(string name, int width, int height);
  void                              drawBackground();
  GoofyNode*                        addNode(GoofyBridgeToNode* layer);
  GoofyNode*                        addNode(GoofyNode* node);
  void                              addNode(GoofyNodeGuiTypes type, GoofyNodeStage* mainStage);
  void                              mouseDragged(int x, int y, int button);
  void                              onReleaseIn(int x, int y, int button);
  void                              loadFromXML(ofxXmlSettings* xml);
  int                               countDrag;
  void                              removeNode(GoofyNode* node);
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
