//
//  FakeClassForNode.cpp
//  GoofyNodeTest
//
//  Created by XXX on 24/10/14.
//
//

#include "FakeClassForNode.h"

void FakeClassForNode::defineNodeMethods()
{
  addMethod("method 1");
  addMethod("method 2");
  addMethod("method 3");
}

void FakeClassForNode::activeFunction(int id)
{
  switch(id)
  {
    case 0:
      method1();
      break;
    case 1:
      method2(0);
      break;
    case 2:
      method3(0,0);
      break;
  }
}