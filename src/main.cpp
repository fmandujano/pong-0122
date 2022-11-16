#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char** argv )
{
    int resx = 640;
    int resy = 480;

    if(argc==3)
    {
        ofSetupOpenGL( atoi(argv[1]) , atoi(argv[2]),OF_WINDOW);
    }
    else
    {
        ofSetupOpenGL(resx,resy, OF_WINDOW);
    }
	ofRunApp(new ofApp());
}
