//
//  GoofyNodeOutConnection.cpp
//  GoofyNodeTest
//
//  Created by XXX on 24/10/14.
//
//

#include "GoofyNodeOutConnection.h"
#include "GoofyNode.h"

GoofyNodeOutConnection::GoofyNodeOutConnection(GoofyNode* node, int pinID)
{
  this->node = node;
  this->pinID = pinID;
}

GoofyNodeOutConnection::~GoofyNodeOutConnection()
{
  node = NULL;
}