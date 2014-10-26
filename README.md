GoofyNodeView
=============

A basic node interface for openFrameworks.



###Addons dependencies

- ofxMSATimer
- ofxTextInputField
- ofxXmlSettings

###How to use

If you need one node for your class, you just need to create a new class from your class and add inheritance from GoofyBridgeToNode.

###Create a node from your class

FakeClass:


	#include "ofMain.h"	
	class FakeClass
	{
	public:
	  FakeClass(){}
	   void          method1(){  cout << "Method 1" << endl}
	   void          method2(int val){  cout << "Method 2" << endl}
	   void          method3(int val, int val2){  cout << "Method 3" << endl}
	 };
	 
 
FakeClassForNode.h
 
 
 
	#include "FakeClass.h"
	#include "GoofyBridgeToNode.h"
	class FakeClassForNode:public FakeClass, public GoofyBridgeToNode
	{
	public:
	  void          defineNodeMethods();
	  void          activeFunction(int id);
	};

FakeClassForNode.cpp
 
 	#include "FakeClassForNode.h"
	
	void FakeClassForNode::defineNodeMethods()
	{
	  // Add method names. They will be show like pins
	  addMethod("method 1");
	  addMethod("method 2");
	  addMethod("method 3");
	}
	
	void FakeClassForNode::activeFunction(int id)
	{
	  // Create one case for each method name
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