//
//  GoofyNodeButton.h
//  ShadowTheatre2_0
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __ShadowTheatre2_0__GoofyNodeButton__
#define __ShadowTheatre2_0__GoofyNodeButton__

#include "GoofyNode.h"
#include "GoofyNodeDelay.h"

class GoofyNodeStage;

class GoofyNodeButton: public GoofyNode
{
public:
                  GoofyNodeButton();
                  GoofyNodeButton(GoofyNodeStage* mainStage);
                  ~GoofyNodeButton();
  void            addNodeOutConnection(GoofyNode* node);
  void            setup(string name);
  void            drawAfterBackground();
  void            update();
  static GoofyNodeButton* createButton(ofVec2f pos, GoofyNodeStage* mainStage, string name = "button");
  
protected:
  void            onReleaseIn(int x, int y, int  button);
};



#endif /* defined(__ShadowTheatre2_0__GoofyNodeButton__) */
