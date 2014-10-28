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
                      GoofyNodePin(GoofyNodeStage* mainStage, string name = "", GoofyNodePinMode mode = GOOFY_NODE_PIN_NOT_DEFINED);
                      ~GoofyNodePin();
  virtual void        setup(GoofyNodeStage* mainStage, string name);
  virtual void        update();
  virtual void        drawAfterBackground();
  void                drawHole();
  void                drawName();
  GoofyNodePinMode    pinMode;
  int                 pinId;
  void                saveSpecificInfo(ofxXmlSettings* xml);
  
protected:
  void                onReleaseIn(int x, int y, int button);
  void                onPressIn(int x, int y, int button);
  void                onPressOut(int x, int y, int button);
  void                mouseDragged(int x, int y, int button);
};

#endif /* defined(__GoofyNodeTest__GoofyNodePin__) */
