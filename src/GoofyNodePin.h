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
                      GoofyNodePin(GoofyNodePinMode mode);
                      ~GoofyNodePin();
  virtual void        setup(string name);
  virtual void        update();
  virtual void        drawAfterBackground();
  void                drawHole();
  GoofyNodePinMode    pinMode;
  int                 pinId;
  
protected:
  void                onReleaseIn(int x, int y, int button);
  void                onPressIn(int x, int y, int button);
  void                onPressOut(int x, int y, int button);
  void                mouseDragged(int x, int y, int button);
};

#endif /* defined(__GoofyNodeTest__GoofyNodePin__) */
