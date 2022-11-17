#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //inicializar los valores de pos y vel
    posPelota = new ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    velPelota = new ofVec2f(100,100);

    posPlayer1 = new ofVec2f(20, 100);
    posPlayer2 = new ofVec2f(ofGetWidth()-15-20, 100);

    //configurar el menu
    mainPanel.setup();
    mainPanel.add( btnServer.setup("Crear partida")  );
    mainPanel.add( btnClient.setup("Conectar a partida") );
    mainPanel.setPosition( ofGetWidth()/2 - mainPanel.getWidth()/2 ,
                              ofGetHeight()/2 - mainPanel.getHeight()/2);
    btnClient.addListener( this, &ofApp::connectClient   );
    btnServer.addListener( this, &ofApp::createServer );  //operador de dereferencia
    appState = EAppState::mainmenu;

}

void ofApp::createServer()
{
    puts("soy un servidor!");
    appState = EAppState::server;
    //crear el socket
    udpManager.Create();
    udpManager.Bind( gamePort);
    udpManager.SetNonBlocking(true);
}

void ofApp::connectClient()
{
    puts("soy un cliente!");
    appState = EAppState::client;

    //crear socket
    udpManager.Create();

    //establecer conexion
    string serverIP = ofSystemTextBoxDialog("Ingresa IP del servidor");
    udpManager.Connect(  serverIP.c_str()  , gamePort);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if( appState==EAppState::mainmenu)
    {
        //nada!
    }
    else if(appState==EAppState::server)
    {
        //mover raqueta del player 1
        if(w) posPlayer1->y -= 100 * ofGetLastFrameTime();
        if(s) posPlayer1->y += 100 * ofGetLastFrameTime();

        //simulacion del mov de pelota
        posPelota->x += velPelota->x * ofGetLastFrameTime();
        posPelota->y += velPelota->y * ofGetLastFrameTime();

        //colisiones
        if( posPelota->x < 0 || posPelota->x > ofGetWidth() )
        {
            velPelota->x *= -1;
        }
        if( posPelota->y < 0 || posPelota->y > ofGetHeight() )
        {
            velPelota->y *= -1;
        }

        //recibir datos del cliente
        memset( buffer, 0, BUFFER_SIZE);
        if( udpManager.Receive(buffer, BUFFER_SIZE)>0 )
        {
            printf("%s \n ", buffer);

            //hay que convertir buffer en posPlayer2
        }
    }
    else if(appState==EAppState::client)
    {
        //mover raqueta del player 1
        if(w) posPlayer2->y -= 100 * ofGetLastFrameTime();
        if(s) posPlayer2->y += 100 * ofGetLastFrameTime();

        //enviar posicion de la paleta 2
        memset( buffer, 0, BUFFER_SIZE);
        //serializacion del vector de pos del player 2
        sprintf( buffer,  "%f, %f", posPlayer2->x, posPlayer2->y );
        udpManager.Send(buffer, BUFFER_SIZE);
    }




}

//--------------------------------------------------------------
void ofApp::draw()
{
    if(appState==EAppState::mainmenu)
        drawMenu();
    else if (appState==EAppState::server)
        drawServer();
    else if (appState==EAppState::client)
        drawClient();
}

void ofApp::drawMenu()
{
    mainPanel.draw();
}
void ofApp::drawServer()
{
    ofBackground(8,8,8);
    //escribis que es el servidor
    ofDrawBitmapString("PLAYER 1 - SERVER ", 15,15);

    ofDrawCircle( posPelota->x, posPelota->y, radioPelota );
    ofDrawRectangle(posPlayer1->x, posPlayer1->y, 15, 150);
    ofDrawRectangle(posPlayer2->x, posPlayer2->y, 15, 150);
}
void ofApp::drawClient()
{

    ofBackground(8,8,8);
    //escribis que es el cliente
    ofDrawBitmapString("PLAYER 2 - CLIENT ", 15,15);
    ofDrawCircle( posPelota->x, posPelota->y, radioPelota );
    ofDrawRectangle(posPlayer1->x, posPlayer1->y, 15, 150);
    ofDrawRectangle(posPlayer2->x, posPlayer2->y, ofGetWidth()-15-20, 150);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == 'w')
    {
        w = true;
    }
    if( key == 's')
    {
        s = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if( key == 'w')
    {
        w = false;
    }
    if( key == 's')
    {
        s = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
