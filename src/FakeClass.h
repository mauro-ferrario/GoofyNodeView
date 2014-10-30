
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

class FakeClass
{
public:
  FakeClass(){}
  void          method1(){  cout << "Method 1" << endl; }
  void          method2(int val){  cout << "Method 2" << endl; }
  void          method3(int val, int val2){  cout << "Method 3" << endl; }
};

#endif /* defined(__GoofyNodeTest__FakeClass__) */
  