//
//  GoofyNodeLineConnection.h
//  GoofyNodeTest
//
//  Created by XXX on 23/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodeLineConnection__
#define __GoofyNodeTest__GoofyNodeLineConnection__

#include "ofMain.h"
#include "GoofyNodePin.h"

class GoofyNodeLineConnection
{
public:
                            GoofyNodeLineConnection(GoofyNodePin* pin);
                            GoofyNodeLineConnection(GoofyNodePin* pin1, GoofyNodePin* pin2);
                            ~GoofyNodeLineConnection();
  void                      setup(GoofyNodePin* pin);
  void                      setup(GoofyNodePin* pin1, GoofyNodePin* pin2);
  void                      draw();
  void                      remove();
  void                      enableMouseEvents();
  void                      disableMouseEvents();
  void                      _mouseReleased(ofMouseEventArgs &e);
  void                      _keyReleased(ofKeyEventArgs &e);
  bool                      isCloseToTheLine(int x, int y);
  ofVec2f                   startPoint;
  ofVec2f                   endPoint;
  GoofyNodePin*             firstPin;
  GoofyNodePin*             secondPin;
  bool                      editable;
  bool                      selected;
  bool                      toRemove;
  GoofyNodeOutConnection*   connection;
  string                    logVerboseModule;
  float                     maxSelectedRange;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeLineConnection__) */
