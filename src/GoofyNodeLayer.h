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

class GoofyNodeLayer: public GoofyNode
{
public:
                      GoofyNodeLayer();
                      ~GoofyNodeLayer();
  virtual void        setup(string name);
  virtual void        update();
  virtual void        draw();
  void                addNode(GoofyNode* node);
  void                addNode(GoofyBridgeToNode* layer);
  void                createPins();
  void                createSinglePin(int idFunction,  GoofyNodePinMode mode);
  virtual void        drawBackground();
  GoofyBridgeToNode*  interactiveLayer;
  vector<GoofyNode*>  nodes;
  void                drawNodes();
  
protected:
  void                onPress(int x, int y, int button);
};

#endif /* defined(__GoofyNodeTest__GoofyNodeLayer__) */
