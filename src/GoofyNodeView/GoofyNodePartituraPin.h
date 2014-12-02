//
//  GoofyNodePartituraPin.h
//  GoofyNodeTest
//
//  Created by XXX on 18/11/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodePartituraPin__
#define __GoofyNodeTest__GoofyNodePartituraPin__

#include "GoofyNodePin.h"

class GoofyNodePartituraPin : public GoofyNodePin
{
public:
  GoofyNodePartituraPin();
  GoofyNodePartituraPin(GoofyNodeStage* mainStage, string name = "", GoofyNodePinMode mode = GOOFY_NODE_PIN_NOT_DEFINED);
  ~GoofyNodePartituraPin();
  void draw();
  bool  activated;
};

#endif /* defined(__GoofyNodeTest__GoofyNodePartituraPin__) */
