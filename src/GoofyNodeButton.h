//
//  GoofyNodeButton.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyNodeButton__
#define __ShadowTheatre2_0__GoofyNodeButton__

#include "GoofyNode.h"
#include "ofxMSATimer.h"

class GoofyNodeStage;

class GoofyNodeButton: public GoofyNode
{
public:
                  GoofyNodeButton();
                  GoofyNodeButton(GoofyNodeStage* mainStage);
                  ~GoofyNodeButton();
  void            addNodeOutConnection(GoofyNode* node);
  void            setup(string name);
  void            draw();
  void            update();
 // void            checkTimers();
 // void            startTimers();
  //vector<bool>    timerActive;
  //vector<float>   timeStartTimer;
  //ofxMSATimer     timer;
  //int             timerToCheck;
  
protected:
  void            onPressIn(int x, int y, int  button);
  void            onPressOut(int x, int y, int  button);
  
  /*
  template<class T>
  void bar ( T* fooPtr , void(T::*fooFnPtr)(int), int i )
  {
    (fooPtr->*fooFnPtr)(i);
  }
   */
  
  //template<class T>
  //void (T::*fooFnPtr)();
  //template<class T>
  //T* fooPtr;
  
  
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeButton__) */
