//
//  GoofyNodeStage.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyNodeStage__
#define __ShadowTheatre2_0__GoofyNodeStage__

#include "GoofyNodeLayer.h"

class GoofyNodeStage: public GoofyNodeLayer
{
public:
              GoofyNodeStage();
              ~GoofyNodeStage();
  void        setup(string name);
  void        drawBackground();
};

#endif /* defined(__ShadowTheatre2_0__GoofyNodeStage__) */
