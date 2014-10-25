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
#include "ofxTextInputField.h"

class GoofyNodeStage;

class GoofyNodeDelay: public GoofyNode
{
public:
                    GoofyNodeDelay();
                    GoofyNodeDelay(GoofyNodeStage* mainStage);
                    ~GoofyNodeDelay();
  void              addNodeOutConnection(GoofyNode* node);
  void              setup(string name);
  void              update();
  void              draw();
  void              activeFunction(int id);
  void              setDelay(float seconds);
  void              saveSpecificInfo(ofxXmlSettings* xml);

private:
  void              drawAfterBackground();
  void              timerEnded();
  void              checkTimer();
  void              startTimer();
  void              stopTimer();
  void              pauseTimer();
  void              resetTimer();
  void              initTextTimer();
  bool              timerActive;
  float             timeStartTimer;
  float             endTimer;
  float             secondsDelay;
  ofxMSATimer       timer;
  ofxTextInputField textTimer;
  bool              isPause;
  float             timeStartPause;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeDelay__) */
