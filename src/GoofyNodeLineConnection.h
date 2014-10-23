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
  void            draw();
  ofVec2f         startPoint;
  ofVec2f         endPoint;
  GoofyNodePin*   firstPin;
  GoofyNodePin*   secondPin;
  bool            editable;
  void            enableMouseEvents();
  void            disableMouseEvents();
  void            _mouseReleased(ofMouseEventArgs &e);
  bool            selected;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeLineConnection__) */
