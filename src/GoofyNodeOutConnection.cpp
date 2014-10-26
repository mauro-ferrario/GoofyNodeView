//
//  GoofyNodeOutConnection.cpp
//  GoofyNodeTest
//
//  Created by XXX on 24/10/14.
//
//

#include "GoofyNodeOutConnection.h"
#include "GoofyNode.h"

GoofyNodeOutConnection::GoofyNodeOutConnection(GoofyNode* nodeIn, GoofyNode* nodeOut, int pinID)
{
  this->nodeIn  = nodeIn;
  this->nodeOut = nodeOut;
  this->pinID   = pinID;
}

GoofyNodeOutConnection::GoofyNodeOutConnection(string nodeInId, string nodeOutId, int pinID)
{
  this->nodeInId = nodeInId;
  this->nodeOutId = nodeOutId;
  this->pinID = pinID;
}

GoofyNodeOutConnection::~GoofyNodeOutConnection()
{
  nodeOut = NULL;
  nodeIn = NULL;
}