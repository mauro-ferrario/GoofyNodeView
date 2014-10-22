
//
//  FakeClass.h
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __GoofyNodeTest__FakeClass__
#define __GoofyNodeTest__FakeClass__

#include "ofMain.h"
#include "GoofyBridgeToNode.h"

class FakeClass : public GoofyBridgeToNode
{
public:
                FakeClass();
  virtual void  setup();
  void          method1();
  void          method2(int val);
  void          method3(int val, int val2);
  void          defineNodeMethods();
};

#endif /* defined(__GoofyNodeTest__FakeClass__) */
