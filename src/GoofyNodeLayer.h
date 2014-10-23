//
//  GoofyNodeLayer.h
//  GoofyNodeTest
//
//  Created by XXX on 22/10/14.
//
//

#ifndef __GoofyNodeTest__GoofyNodeLayer__
#define __GoofyNodeTest__GoofyNodeLayer__

#include "GoofyNode.h"
#include "GoofyBridgeToNode.h"
#include "GoofyNodePin.h"

class GoofyNodeStage;

class GoofyNodeLayer: public GoofyNode
{
public:
                      GoofyNodeLayer();
                      ~GoofyNodeLayer();
  virtual void        setup(string name);
  virtual void        update();
  virtual void        draw();
  virtual void        addNode(GoofyBridgeToNode* layer, GoofyNodeStage* mainStage);
  virtual void        addNode(GoofyNode* node, GoofyNodeStage* mainStage);
  virtual void        mouseDragged(int x, int y, int button);
  void                createPins();
  virtual void        drawBackground();
  
protected:
  void                onPress(int x, int y, int button);
};

#endif /* defined(__GoofyNodeTest__GoofyNodeLayer__) */
