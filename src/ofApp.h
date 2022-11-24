#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxGui.h"
#define BUFFER_SIZE 100

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawMenu();
        void drawServer();
        void drawClient();

        //metodos de los botones
        void createServer();
        void connectClient();

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

        //variables de configuracion
        bool fpslimit=true;

        //menu principal
        ofxPanel mainPanel;
        ofxButton btnServer;
        ofxButton btnClient;

        //variables de las raquetas y pelota
        ofVec2f * posPelota;
        ofVec2f * velPelota;
        float radioPelota=20;
        ofVec2f * posPlayer1;
        ofVec2f * posPlayer2;

        //estado del input
        bool w,s;

        //modos de la aplicacion
        enum EAppState
        {
            mainmenu, server, client
        };
        EAppState appState;

        //variables de red
        ofxUDPManager udpManager;
        int gamePort = 6666;
        char buffer[BUFFER_SIZE];

};
