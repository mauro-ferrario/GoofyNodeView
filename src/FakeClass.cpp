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
  cout << "Method 1" << endl;
}

void FakeClass::method2(int val)
{
  cout << "Method 2" << endl;
}

void FakeClass::method3(int val, int val2)
{
  cout << "Method 3" << endl;
}

void FakeClass::defineNodeMethods()
{
  functionNames.push_back("method 1");
  functionNames.push_back("method 2");
  functionNames.push_back("method 3");
}

void FakeClass::activeFunction(int id)
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