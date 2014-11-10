//
//  GoofyNodePin.h
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodePin__
#define __GoofyNodeTest__GoofyNodePin__

#include "GoofyNode.h"


class GoofyNodePin: public GoofyNode
{
public:
                      GoofyNodePin();
                      GoofyNodePin(GoofyNodeStage* mainStage, string name = "", GoofyNodePinMode mode = GOOFY_NODE_PIN_NOT_DEFINED);
                      ~GoofyNodePin();
  virtual void        setup(GoofyNodeStage* mainStage, string name = "");
  virtual void        update();
  void                drawAfterBackground();
  void                drawAfterNodes();
  void                drawHole();
  void                drawName();
  GoofyNodePinMode    pinMode;
  int                 pinId;
  void                saveSpecificInfo(ofxXmlSettings* xml);
  bool                bDrawName;
  
protected:
  void                onReleaseIn(int x, int y, int button);
  void                onPressIn(int x, int y, int button);
  void                onPressOut(int x, int y, int button);
  void                mouseDragged(int x, int y, int button);
};

#endif /* defined(__GoofyNodeTest__GoofyNodePin__) */
