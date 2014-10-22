//
//  GoofyBridgeToNode.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyBridgeToNode__
#define __ShadowTheatre2_0__GoofyBridgeToNode__

#include "ofMain.h"

class GoofyBridgeToNode
{
  //typedef void (GoofyBridgeToNode::*function_ptr)();
public:
                                GoofyBridgeToNode();
                                ~GoofyBridgeToNode();
  virtual void                  setup();
  //vector<function_ptr>          activeFunc;
  vector<string>                functionNames;
  virtual void                  activeFunction(int id);
  virtual void                  activeFunctionIn(int id);
  virtual void                  defineNodeMethods();
};

#endif /* defined(__ShadowTheatre2_0__GoofyBridgeToNode__) */
