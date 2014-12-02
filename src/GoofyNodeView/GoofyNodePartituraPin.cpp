//
//  GoofyNodePartituraPin.cpp
//  GoofyNodeTest
//
//  Created by XXX on 18/11/14.
//
//

#include "GoofyNodePartituraPin.h"
#include "GoofyNodeStage.h"

GoofyNodePartituraPin::GoofyNodePartituraPin()
{
  GoofyNodePartituraPin(NULL);
}

GoofyNodePartituraPin::GoofyNodePartituraPin(GoofyNodeStage* mainStage, string name, GoofyNodePinMode mode)
{
  activated = false;
  GoofyNodePin::GoofyNodePin(mainStage, name, mode);
  this->type = GOOFY_PARTITURA_PIN;
}

GoofyNodePartituraPin::~GoofyNodePartituraPin()
{
  
}

void GoofyNodePartituraPin::draw()
{
  ofPushMatrix();
  ofPushStyle();
  ofFill();
  if(activated)
    ofSetColor(255,0,0);
  else
    ofSetColor(255);
  ofCircle(this->pos, 3);
  ofPopStyle();
  ofPopMatrix();
}