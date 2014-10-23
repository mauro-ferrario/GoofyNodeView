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

class GoofyNodePin;

class LineConnection
{
public:
  ofVec2f startPoint;
  ofVec2f endPoint;
  GoofyNodePin*   firstPin;
  GoofyNodePin*   secondPin;
  bool    editable;
  LineConnection(GoofyNodePin* pin)
  {
    editable = false;
    secondPin = NULL;
    firstPin = pin;
    startPoint  = ofVec2f(pin->getX() + 5, pin->getY() + 5);
  }
  
  void draw()
  {
    startPoint  = ofVec2f(firstPin->getX() + 5, firstPin->getY() + 5);
    if(secondPin != NULL)
      endPoint  = ofVec2f(secondPin->getX() + 5, secondPin->getY() + 5);
    ofPushStyle();
    ofSetColor(255);
    ofLine(startPoint, endPoint);
    ofPopStyle();
  }
};

class GoofyNodeStage: public GoofyNodeLayer
{
public:
                      GoofyNodeStage();
                      ~GoofyNodeStage();
  void                update();
  void                draw();
  void                setup(string name);
  void                drawBackground();
  virtual void        addNode(GoofyBridgeToNode* layer);
  virtual void        addNode(GoofyNode* node);
  virtual void        mouseDragged(int x, int y, int button);
  void                removeTempLineConnection();
  virtual void        onReleaseIn(int x, int y, int button);
  bool                checkLineConnectionPin();
  ofxMSATimer         timer;
  float               timerStart;
  bool                checkRelease;
  
  
  void                addPinConnection(GoofyNodePin* pin);
  
  LineConnection* lineConnection;
  vector<LineConnection*> connections;
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
