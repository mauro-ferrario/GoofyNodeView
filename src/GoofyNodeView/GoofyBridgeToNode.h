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
public:
                                GoofyBridgeToNode();
                                ~GoofyBridgeToNode();
  virtual void                  setup();
  virtual void                  activeFunction(int id);
  virtual void                  defineNodeMethods();
  void                          initId();
  void                          addMethod(string methodName);
  string                        bridgeId;
  vector<string>                functionNames;
  string                        name;
};

#endif /* defined(__ShadowTheatre2_0__GoofyBridgeToNode__) */
