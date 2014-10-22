//
//  FakeClass.cpp
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#include "FakeClass.h"



FakeClass::FakeClass()
{
}

void FakeClass::setup()
{
  GoofyBridgeToNode::setup();
}

void FakeClass::method1()
{
  
}

void FakeClass::method2(int val)
{
  
}

void FakeClass::method3(int val, int val2)
{
  
}

void FakeClass::defineNodeMethods()
{
  functionNames.push_back("method 1");
  functionNames.push_back("method 2");
  functionNames.push_back("method 3");
}