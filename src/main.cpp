#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char** argv )
{
    int resx = 640;
    int resy = 480;
    bool fullscreen=false;

    bool fpslimit;

    //parsear el archivo ini
    ifstream inifile;
    inifile.open("data/config.ini");
    if( inifile.is_open() )
    {
        puts("Analizando config.ini");
        char* linea = new char[100];
        char* llave, *valor;
        while( ! inifile.eof() )
        {
            inifile.getline( linea, 100 );
            //printf("linea leida: %s \n", linea );
            //analizar la linea
            //ignorar lineas que comiencen con caracteres no aceptables
            if ( linea[0] != '/' &&
                 linea[0] != '[' &&
                 linea[0] != '\n' &&  //line feed
                 linea[0] != '\r' &&  //carriage return, solo en windows
                 linea[0] != '\0' &&
                 linea[0] != '#' && //comentario tipo python
                 linea[0 != ';'] ) //comentario en otros lenguajes
            {
                llave = strtok( linea,"=" );
                valor = strtok( NULL, "=");
                printf("llave: %s valor: %s \n", llave, valor);
                if (  strcmp(llave, "resx")==0  )
                    resx = atoi(valor);
                if (  strcmp(llave, "resy")==0  )
                    resy = atoi(valor);
                if (  strcmp(llave, "fullscreen")==0  )
                    fullscreen = atoi(valor)!=0 ;
                if (  strcmp(llave, "fpslimit")==0  )
                     fpslimit = atoi(valor)!=0 ;
            }
        }
    }

    //si le dimos argumentos, ignora lo del ini
    if(argc==3)
    {
        ofSetupOpenGL( atoi(argv[1]) , atoi(argv[2]),OF_WINDOW);

        ofRunApp(new ofApp());
    }
    else
    {
        ofApp * app;
        app = new ofApp();
        ofSetupOpenGL(resx,resy,  fullscreen? OF_FULLSCREEN:  OF_WINDOW);
        app->fpslimit = fpslimit;
        ofRunApp( app);
    }
}
