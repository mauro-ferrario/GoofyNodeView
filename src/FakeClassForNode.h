//
//  FakeClassForNode.h
//  GoofyNodeTest
//
//  Created by XXX on 24/10/14.
//
//

#ifndef __GoofyNodeTest__FakeClassForNode__
#define __GoofyNodeTest__FakeClassForNode__

#include "FakeClass.h"
#include "GoofyBridgeToNode.h"

class FakeClassForNode:public FakeClass, public GoofyBridgeToNode
{
public:
  void          defineNodeMethods();
  void          activeFunction(int id);
};

#endif /* defined(__GoofyNodeTest__FakeClassForNode__) */
