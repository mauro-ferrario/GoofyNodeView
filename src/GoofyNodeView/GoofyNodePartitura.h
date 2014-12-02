//
//  GoofyNodePartitura.h
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodePartitura__
#define __GoofyNodeTest__GoofyNodePartitura__

#include "GoofyNode.h"
#include "ofxMSATimer.h"
#include "ofxTextInputField.h"
#include "GoofyNodePartituraPin.h"

class GoofyNodePartitura: public GoofyNode
{
public:
  GoofyNodePartitura();
  GoofyNodePartitura(GoofyNodeStage* mainStage, string name = "");
  virtual                 ~GoofyNodePartitura();
  void                    addNodeOutConnection(GoofyNode* node);
  void                    setup(GoofyNodeStage* mainStage, string name);
  void                    update();
  void                    draw();
  void                    activeFunction(int id);
  void                    setDelay(float seconds);
  void                    saveSpecificInfo(ofxXmlSettings* xml);
  static GoofyNodePartitura*  createPartitura(ofVec2f pos, GoofyNodeStage* mainStage, float secondsDelay, string name);
  virtual GoofyNode*                createSinglePartituraPin(int idFunction,  GoofyNodePinMode mode,  ofVec2f pos);
  virtual GoofyNode*                createSinglePartituraPin(int idFunction,  GoofyNodePinMode mode,  ofVec2f pos, string name);

  
private:
  void                    drawAfterBackground();
  void                    timerEnded();
  void                    checkTimer();
  void                    startTimer();
  void                    stopTimer();
  void                    pauseTimer();
  void                    resetTimer();
  void                    initTextTimer();
  bool                    timerActive;
  float                   timeStartTimer;
  float                   endTimer;
  float                   secondsDelay;
  ofxMSATimer             timer;
  ofxTextInputField       textTimer;
  bool                    isPause;
  float                   timeStartPause;
  vector<GoofyNode*>      connections;
  ofVec2f                 pointerPos;
  int                     actualPosInTimeline;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeDelay__) */
