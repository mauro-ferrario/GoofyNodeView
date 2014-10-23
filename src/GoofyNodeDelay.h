//
//  GoofyNodeDelay.h
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodeDelay__
#define __GoofyNodeTest__GoofyNodeDelay__

#include "GoofyNode.h"
#include "ofxMSATimer.h"

class GoofyNodeStage;

class GoofyNodeDelay: public GoofyNode
{
public:
                  GoofyNodeDelay();
                  GoofyNodeDelay(GoofyNodeStage* mainStage);
                  ~GoofyNodeDelay();
  void            addNodeOutConnection(GoofyNode* node);
  void            setup(string name);
  void            update();
  void            activeFunction(int id);

private:
  void            drawAfterBackground();
  void            timerEnded();
  void            checkTimer();
  void            startTimer();
  bool            timerActive;
  float           timeStartTimer;
  float           endTimer;
  ofxMSATimer     timer;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeDelay__) */
