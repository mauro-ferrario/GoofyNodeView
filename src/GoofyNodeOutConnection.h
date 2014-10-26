//
//  GoofyNodeOutConnection.h
//  GoofyNodeTest
//
//  Created by XXX on 24/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodeOutConnection__
#define __GoofyNodeTest__GoofyNodeOutConnection__

#include "ofMain.h"

class GoofyNode;

class GoofyNodeOutConnection
{
public:
                GoofyNodeOutConnection(GoofyNode* nodeIn, GoofyNode* nodeOut, int pinID);
                GoofyNodeOutConnection(string nodeInId, string nodeOutId, int pinID);
                ~GoofyNodeOutConnection();
  GoofyNode*    nodeOut;
  GoofyNode*    nodeIn;
  string        nodeInId;
  string        nodeOutId;
  int           pinID;
};

#endif /* defined(__GoofyNodeTest__GoofyNodeOutConnection__) */
