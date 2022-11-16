#pragma once

#include "ofMain.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //variables de las raquetas y pelota
        ofVec2f * posPelota;
        ofVec2f * velPelota;
        float radioPelota=20;
        ofVec2f * posPlayer1;
        ofVec2f * posPlayer2;

        //estado del input
        bool w,s;


		
};