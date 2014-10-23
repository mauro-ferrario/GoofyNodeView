#pragma once

#include "ofMain.h"
#include "FakeClass.h"
#include "GoofyNodeStage.h"
#include "GoofyNodeButton.h"
#include "GoofyNodeDelay.h"




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
  FakeClass* fake1;
  GoofyNodeStage* nodeView;
  GoofyNodeButton* button;
  GoofyNodeDelay* delay1;
  GoofyNodeDelay* delay2;

  
		
};
