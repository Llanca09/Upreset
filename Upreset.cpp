#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <limits>
#include <math.h>
#include <conio.h>
#include <chrono>
#include <string>
#include <cstring>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <windows.h>
#include <time.h>
#include <iomanip> 

using namespace std;

#define color SetConsoleTextAttribute

#define AMIGOS_MAXIMOS 32
#define SOLICITUDES_MAXIMOS 32

struct creapregunta {
    char crea_pregunta[512];
    int opc_preg;
};

struct verpregunta {
    char respon_pregunta[512];
    bool encontrado;
    int opc_preg;
};


struct Profilecv {
    char fullnameprofile[128]; // strings de C++ no son compatibles con C
    bool encontrado;
    int age;
    char nivelacademico[32];    // repetir
    char carrera[64]; // repetir
    char empresaname[32]; // repetir
    char time[16];           // repetir
    char cargo[32];     // repetir
    char Pais[32];
    char city[32];
    int opc_exp;
  
};

struct profileUser {
    char fullnameprofile[128]; // no repetir
    int ageprofile;           // repetir
    char nivelacademico[32];    // repetir
    char carrera[64]; // repetir
    char empresaname[32]; // repetir
    char time[16];           // repetir
    char cargo[32];     // repetir
    char Pais[32];
    char city[32];
    int opc_exp;

    char solicitudes[SOLICITUDES_MAXIMOS][32];
    int numerosolicitudes;
};


struct Profile {
  char username[32]; // strings de C++ no son compatibles con C
  bool encontrado;
  int age;
  char city[32];
};
// esta estructura ocupa 68 bytes
struct User {
    char fullname[64]; // repetir
    char email[32];    // no repetir
    char password[32]; // repetir
    char username[32]; // no repetir
    int age;           // repetir
    char city[32];     // repetir

    char friends[AMIGOS_MAXIMOS][32];
    int friendsCount;
};
// esta estructura ocupa 192 bytes

fstream archivocreapregunta;
creapregunta currentpregunta;

fstream archivoprofile;
profileUser currentprofile;

fstream archivo;
User currentUser;

void pregunta_crea();


//void portada();
void crearprofile();
bool existename(char fullnameprofile[128]);
bool enviarsolicitud(Profilecv profile);
void actualizarProfile(char username[32], Profilecv fullnameprofile);
bool existeprofile(char fullnameprofile[128]);

void mostrar_inicio();
void mostrar_menu();
void limpiar_buffer();
void limpiar_pantalla();
void Biblioteca_virtual();
void Comunidad_grupos();
void Foro_perfil();
void Clases_virtuales();
void Conferencias_debates();
void Foro_ayuda();
void Grupos_extracurriculares();

bool existeCorreo(char email[32]);
bool existeUsuario(char username[32]);
bool agregarComoAmigo(Profile profile);
void actualizarUsuario(char username[32], User user);


int main (void) {


    //system("COLOR B0"); 
    //int op;
    int matriz[26][118]= {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,0,8,0,8,8,8,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,8,0,8,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,0,8,0,8,8,8,0,8,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,2,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,8,0,0,0,8,0,8,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,7,7,7,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,4,0,0,0,0,0,0 },
        {0,0,0,0,1,1,2,2,2,2,2,1,1,0,0,0,0,1,1,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,8,0,8,8,8,0,8,0,0,0,0,0,0,0,0,0,0,1,1,0,0,7,7,7,7,7,0,0,0,2,2,2,4,4,4,2,2,2,2,4,0,1,0,0,0,0,0},
        {0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,1,1,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,3,3,3,3,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,5,5,5,5,5,0,0,2,2,2,4,4,0,0,0,0,2,2,4,0,1,1,0,0,0,0 },
        {0,0,1,1,1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,2,2,4,4,0,0,0,0,2,2,4,0,1,1,1,1,0,0,0},
        {0,0,1,2,1,1,1,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,7,7,7,7,7,7,7,5,0,2,2,4,0,0,0,0,0,2,4,0,0,0,0,1,1,1,0,0},
        {0,0,1,2,2,2,1,1,2,1,1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,1,0,0,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,7,7,0,7,7,7,7,5,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1,1,1,2,1,2,2,1,1,0,0,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,3,3,3,3,0,3,3,3,3,0,0,3,3,3,3,3,0,3,3,3,3,3,3,0,3,3,3,3,3,0,3,3,3,3,3,3,3,0,0,0,6,6,6,0,0,7,7,7,7,5,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,1,1,1,2,1,0,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,4,4,4,3,0,3,4,4,4,3,0,3,4,4,4,3,0,3,4,4,4,4,3,0,3,4,4,4,3,0,0,0,0,3,4,4,4,0,0,0,1,1,1,6,6,7,7,7,5,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,1,1,0,0,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,4,0,0,3,0,3,4,0,0,3,0,3,4,0,0,0,0,3,4,0,0,0,0,0,3,4,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,6,6,1,1,6,6,5,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,1,1,2,2,2,2,2,2,2,1,1,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,0,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,4,0,0,3,0,3,4,0,0,3,0,3,4,0,0,0,0,3,4,0,0,0,0,0,3,4,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,7,6,1,1,1,6,6,6,6,6,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,1,1,0,0},
        {0,0,0,1,1,1,2,2,2,1,1,2,2,2,2,2,1,1,2,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,3,3,3,3,0,3,3,3,3,0,0,3,3,3,3,0,0,3,3,3,3,3,3,0,3,3,3,3,0,0,0,0,0,3,4,0,0,0,0,0,0,7,7,7,6,6,6,1,1,1,1,6,6,6,6,6,0,0,2,2,2,2,2,2,4,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,2,2,1,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,4,0,0,0,0,3,3,0,0,0,0,3,4,0,0,0,0,0,0,0,0,4,3,0,3,4,0,0,0,0,0,0,0,3,4,0,0,0,0,0,7,7,7,7,7,5,0,6,6,1,1,1,1,1,1,6,6,6,6,2,2,2,2,2,4,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,1,1,2,2,1,0,0,0,3,3,4,0,0,0,0,3,3,0,0,3,4,0,0,0,0,3,4,3,0,0,0,3,4,0,0,0,0,0,0,0,0,4,3,0,3,4,0,0,0,0,0,0,0,3,4,0,0,0,0,0,7,7,7,7,5,0,0,0,0,6,6,6,6,1,1,1,1,1,1,6,6,6,6,1,4,0,1,6,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,1,1,1,0,0,0,3,3,4,4,4,4,4,3,3,0,0,3,4,0,0,0,0,3,4,0,3,0,0,3,4,0,0,3,0,0,0,0,0,4,3,0,3,4,0,0,0,0,0,0,0,3,4,0,0,0,0,0,7,7,7,7,5,0,0,0,5,0,2,2,2,6,6,6,6,1,1,1,1,1,1,1,1,6,1,6,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,2,2,2,1,1,0,0,1,1,2,2,2,2,2,1,0,0,0,3,3,3,3,3,3,3,3,3,0,0,3,4,0,0,0,0,3,4,0,0,3,0,3,4,4,4,3,0,3,4,4,4,4,3,0,3,4,4,4,3,0,0,0,0,3,4,0,0,0,0,0,7,7,7,7,5,0,0,5,5,0,2,2,2,0,0,0,0,6,6,6,6,6,6,6,6,1,1,6,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,1,1,2,1,1,0,0,0,0,3,3,3,3,3,3,3,3,3,0,0,3,4,0,0,0,0,3,4,0,0,3,0,3,3,3,3,3,0,3,3,3,3,3,3,0,3,3,3,3,3,0,0,0,0,3,4,0,0,0,0,0,7,7,7,7,5,5,5,5,0,0,4,2,2,2,0,0,0,0,0,2,2,6,6,6,6,6,6,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,5,0,0,1,1,0,4,2,2,2,2,2,2,2,2,2,2,4,0,0,6,6,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,1,1,1,1,0,4,2,2,2,2,2,2,2,4,4,0,6,6,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,4,4,4,4,4,4,4,0,0,1,6,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


     HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, 6 );
    for ( int i = 0 ; i < 26 ; i++)
    {
        for ( int j = 0 ; j < 118 ; j++)
        {
            if (matriz[i][j]== 1 )
            {
                HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute (hConsole, 1 );
                cout<<( char ) 219  ;
            } else  if (matriz[i][j]== 2 )
            {
                SetConsoleTextAttribute (hConsole, 9 );
                cout <<( char ) 219 ;

            } else  if (matriz[i][j]== 0 ){
                SetConsoleTextAttribute (hConsole, 15 );
                cout <<( char ) 219 ;

            } else  if (matriz[i][j]== 3 )
            {
                SetConsoleTextAttribute (hConsole, 1 );
                cout <<( char ) 219 ;

            }else  if (matriz[i][j]== 4 )
            {
                SetConsoleTextAttribute (hConsole, 8 );
                cout <<( char ) 219 ;

            }else  if (matriz[i][j]== 5 )
            {
                SetConsoleTextAttribute (hConsole, 12 );
                cout <<( char ) 219 ;

            }else  if (matriz[i][j]== 6 )
            {
                SetConsoleTextAttribute (hConsole, 0 );
                cout <<( char ) 219 ;

            }else  if (matriz[i][j]== 8 )
            {
                SetConsoleTextAttribute (hConsole, 15 );
                cout <<( char ) 221 ;

            }else  if (matriz[i][j]== 7 )
            {
                SetConsoleTextAttribute (hConsole, 6 );
                cout <<( char ) 219 ;

            }else {
                cout << "       " ;
            }

        }
        cout<<endl;
	}

    limpiar_buffer();
    limpiar_pantalla();

    string correo;
    string usuario;
    string contrasena;

    mostrar_inicio();
    limpiar_buffer();
    limpiar_pantalla();
    //mostrar_menu();
    
    return 0;
}


Profile busqueda() {
    ifstream file("datos.bin");
    Profile perfil;
    User usuario;
    bool usuarioEncontrado = false;
    char searchName[32];

    cout << "Introduzca el nombre que desea buscar: ";
    cin.getline(searchName, sizeof(searchName));
    cout << endl;

    while (file.read((char*)&usuario, sizeof(User))) {
        strcpy(perfil.username, usuario.username);
        perfil.age = usuario.age;
        strcpy(perfil.city, usuario.city);

        if (strcmp(perfil.username, searchName) == 0) {
            // Perfil encontrado!!!!!
            // está guardado dentro de la variable "perfil" de tipo "Profile"
            usuarioEncontrado = true;
            cout << "Nombre: " << perfil.username << endl;
            cout << "Edad: " << perfil.age << endl;
            cout << "Ciudad: " << perfil.city << endl;
            perfil.encontrado = true;
            cout << endl;
            break;
        }
    }

    file.close();

    if (!usuarioEncontrado) {
        cout << "No se encontró el usuario" << endl;
        perfil.encontrado = false;
    }
    return perfil;
}


User obtenerUsuario(char usernameBuscado[32]) {
    ifstream file("datos.bin");
    bool usuarioFueEncontrado = false;
    User usuario;

    while (file.read((char*)&usuario, sizeof(User))) {
        if (strcmp(usuario.username, usernameBuscado) == 0) {
            // Usuario encontrado!!!
            usuarioFueEncontrado = true;
            break;
        }
    }
    file.close();

    if (usuarioFueEncontrado) {
        return usuario;
    }
    else {
        User usuarioVacio;
        strcpy(usuarioVacio.username, "");
        return usuarioVacio;
    }
}


void crearprofile() {

    ofstream archivoprofileEscritura;
    archivoprofileEscritura.open("profile.bin", ios::out | ios::app | ios::binary);

    if (archivoprofileEscritura.is_open()) {
        bool nameYaRegistrado = false;
        do {
            cout << "Ingresa su nombre completo: ";
            cin.getline(currentprofile.fullnameprofile, 128);
            nameYaRegistrado = existename(currentprofile.fullnameprofile);

            if (nameYaRegistrado) {
                cout << "Este nombre ya está registrado" << endl;
            }
        } while (nameYaRegistrado);

        cout <<  "Ingresa tu edad: ";
        cin >> currentprofile.ageprofile;
        limpiar_buffer();
        cout <<  "Ingresa tu nivel academico: ";
        cin.getline(currentprofile.nivelacademico, 32);
        cout <<  "Ingresa tu carrera: ";
        cin.getline(currentprofile.carrera, 32);
        cout <<  "Ingresa tu Pais de residencia: ";
        cin.getline(currentprofile.Pais, 32);
        cout <<  "Ingresa tu Ciudad de residencia: ";
        cin.getline(currentprofile.city, 32);

        do {
        
        cout <<  "Cuenta con experiencia laboral ? " << endl;
        cout <<  "(1). Si" << endl;
        cout <<  "(2). No" << endl;
        cout <<  "> ";
        cin >> currentprofile.opc_exp;

        } while (currentprofile.opc_exp !=1 && currentprofile.opc_exp !=2);
        
        limpiar_buffer();

        if (currentprofile.opc_exp == 1) {
            cout <<  "Ingresa el nombre de la empresa : ";
            cin.getline(currentprofile.empresaname, 32);
            cout <<  "Ingresa el tiempo de trabajo (meses): ";
            cin >> currentprofile.time;
            limpiar_buffer();
            cout <<  "Ingresa el cargo : ";
            cin.getline(currentprofile.cargo, 32);
        }

        cout << "Registro exitoso!" << endl;

        archivoprofileEscritura.write((char*)&currentprofile, sizeof(profileUser));
        archivoprofileEscritura.close();
    }

    limpiar_buffer();
    limpiar_pantalla();
    Foro_perfil();
}


bool existename(char fullnameprofile[128]) {
    archivoprofile.open("profile.bin", ios::in | ios::binary);
    bool siExiste = false;
    if (archivoprofile.is_open()) {
        profileUser profileLectura;
        while (archivoprofile.read((char*)&profileLectura, sizeof(profileUser))) {
            if (strcmp(profileLectura.fullnameprofile, fullnameprofile) == 0) {
                siExiste = true;
                break;
            }
        }
    }
    archivoprofile.close();
    return siExiste;
}


bool existeprofile(char fullnameprofile[128]){
    profileUser c;
    ifstream entrada;
    entrada.open("profile.bin", ios::in | ios::binary);
    if (entrada.good()){
        while(entrada.read((char*)&c,sizeof(profileUser))){// bucle que recorre cada identificaci�n
            //strcmp -> string comparison o comparacion de cadenas
            if (strcmp(fullnameprofile,c.fullnameprofile)==0){
                entrada.close();
                return true;
            }
        }
        entrada.close(); // cerrar el archivo
        return false;
    }else{
        return false;
    }

}


void registerUser() {

    ofstream archivoEscritura;
    archivoEscritura.open("datos.bin", ios::out | ios::app | ios::binary);

    if (archivoEscritura.is_open()) {
        bool correoYaRegistrado = false;
        do {
            cout << "Ingresa el correo electronico: ";
            cin.getline(currentUser.email, 32);
            correoYaRegistrado = existeCorreo(currentUser.email);

            if (correoYaRegistrado) {
                cout << "Este correo ya está registrado" << endl;
            }
        } while (correoYaRegistrado);

        bool usuarioYaRegistrado = false;
        do {
            cout << "Ingresa tu nombre de usuario: ";
            cin.getline(currentUser.username, 32);
            usuarioYaRegistrado = existeUsuario(currentUser.username);

            if (usuarioYaRegistrado) {
                cout << "Este usuario ya está registrado" << endl;
            }
        } while (usuarioYaRegistrado);

        bool contrasenaDebil = false;
        do {
            cout <<  "Ingresa tu contraseña: ";
            cin.getline(currentUser.password, 32);
            if (strlen(currentUser.password) < 5) {
                contrasenaDebil = true;
                cout << "Tu contraseña es muy corta" << endl;
            }
            else {
                contrasenaDebil = false;
            }
        } while (contrasenaDebil);

        cout <<  "Ingresa tu nombre: ";
        cin.getline(currentUser.fullname, 64);
        cout <<  "Ingresa tu edad: ";
        cin >> currentUser.age;
        limpiar_buffer();
        cout <<  "Ingresa tu ciudad: ";
        cin.getline(currentUser.city, 32);
        cout << "Registro exitoso!" << endl;

        archivoEscritura.write((char*)&currentUser, sizeof(User));
        archivoEscritura.close();
        limpiar_buffer();
        limpiar_pantalla();
    }
}

bool login(char user[32], char password[32]) {
    archivo.open("datos.bin", ios::in | ios::binary);
    bool inicioExitoso = false;
    if (archivo.is_open()){
        User loginUser;
        //cout << "Ingresa tu nombre de usuario: ";    cin >> tempU;
        //cout << "Ingresa tu contraseña: "; cin >> tempP;
        while (archivo.read((char*)&loginUser, sizeof(User))) {
            // cout << "Probando " << loginUser.username << " " << loginUser.password << endl;
            // cout << "Comparando con " << user << " " << password << endl;

            if (strcmp(loginUser.username, user) == 0 && strcmp(loginUser.password, password) == 0) {
                inicioExitoso = true;
                break;
            }
        }

        if (inicioExitoso) {
            cout << "Inicio de sesión exitoso!" << endl;
            memcpy(&currentUser, &loginUser, sizeof(User));
            system("pause");
            // limpiar_pantalla();
            // mostrar_menu();
        }
        else {
            cout<<"\nNo se encontro la cuenta\n";
            // mostrar_inicio();
        }
    }
    archivo.close();
    return inicioExitoso;
}

void mostrar_inicio() {
    int opc_inicio;
    //char correo[32];
    char usuario[32];
    char contrasena[32];
    

    cout << "------------------------------------------------------"<< endl;
    cout << "--------------- BIENVENIDO A UPRESET -----------------"<< endl;
    cout << "------ Bet on a preset to your university life -------"<< endl;
    cout << "------------------------------------------------------"<< endl;
    cout << endl;

    do {
        cout << "=================================="<< endl;
        cout << "===== Seleccione una opcion ======"<< endl;
        cout << "=================================="<< endl;
        cout << "== (1). Iniciar seccion =========="<< endl;
        cout << "== (2). Registrarse =============="<< endl;
        cout << "== (3). Mostrar usuarios ========="<< endl;
        cout << "== (4). Salir ===================="<< endl;
        cout << "=================================="<< endl;
        cout << ">";
        cin >> opc_inicio;
    } while (opc_inicio != 1 && opc_inicio != 2 && opc_inicio != 3 && opc_inicio != 4);

    limpiar_pantalla();

    if (opc_inicio == 1){
        cout << "=================================="<< endl;
        cout << "= Inicie seccion para continuar =="<< endl;
        cout << "=================================="<< endl;
        cout << "Usuario : ";
        limpiar_buffer();
        cin.getline(usuario, 32);
        cout << endl;
        cout << "Contrasena : ";
        cin.getline(contrasena, 32);
        cout << endl;
        bool inicioExitoso = login(usuario, contrasena);
        limpiar_pantalla();
        if (inicioExitoso) {
            limpiar_buffer();
            mostrar_menu();
        }
        else {
            cout << "No se encontro la cuenta" << endl;
            limpiar_buffer();
            mostrar_inicio();
        }
    } 

    else if (opc_inicio == 2) {
        cout << "=================================="<< endl;
        cout << "=== Registrate para continuar ===="<< endl;
        cout << "=================================="<< endl;
        cout << endl;
        limpiar_buffer();
        registerUser();

        if (login(currentUser.username, currentUser.password)) {
            mostrar_menu();
        }
        else {
            cout << "Ha ocurrido un error" << endl;
        }
    }  

    else if (opc_inicio == 3) {
        limpiar_buffer();
        limpiar_pantalla();

        archivo.open("datos.bin", ios::in | ios::binary);
        if (archivo.is_open()) {
            User usuarioLectura;
            // recorremos todos los usuarios y los guarda en la variable "usuarioLectura"
            while (archivo.read((char*)&usuarioLectura, sizeof(User))) {
                cout << "username: " << usuarioLectura.username << endl;
                cout << "password: " << usuarioLectura.password << endl;
                cout << "email: " << usuarioLectura.email << endl;
                cout << "age: " << usuarioLectura.age << endl;
                cout << "city: " << usuarioLectura.city << endl;
                cout << "fullname: " << usuarioLectura.fullname << endl;
                cout << "\nAmigos " << "(" << usuarioLectura.friendsCount << "):" << endl;
                for (int i = 0; i < usuarioLectura.friendsCount; i++) {
                    cout << "- amigo " << i + 1 << ": " << usuarioLectura.friends[i] << endl;
                }
                cout << endl;
            }
        }
        archivo.close();

        int opc_atras;
            
            do {
            cout << endl;
            cout << "=================================="<< endl;
            cout << "== (1). Volver a inicio =========="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_atras;
            } while (opc_atras !=1);

            if (opc_atras == 1) {
                limpiar_pantalla();
                limpiar_buffer();
                mostrar_inicio();
                
            }

    }

    else if (opc_inicio == 4) {
        limpiar_buffer();
        limpiar_pantalla();

        cout << "=================================="<< endl;
        cout << "==== CREADOR Y COLABORADORES ====="<< endl;
        cout << "=================================="<< endl;
        cout << "==== Anthony Llanca =============="<< endl;
        cout << "=================================="<< endl;
        cout << "==== Kenny Martinez =============="<< endl;
        cout << "==== Jose Sernaque ==============="<< endl;
        cout << "==== Christian Guerrero =========="<< endl;
        cout << "==== Felipe Triveño =============="<< endl;
        cout << "==== Carlos Sosa ================="<< endl;
        cout << "==== Paolo Flores ================"<< endl;
        cout << "==== Sebastian Cueto ============="<< endl;
        cout << "=================================="<< endl;
        cout << "======= HASTA LA PROXIMA ========="<< endl;
        cout << "=================================="<< endl;
        
    }
    
}

void mostrar_menu() {
    int opc_menu;
    do {
        cout << "=================================="<< endl;
        cout << "============== MENU =============="<< endl;
        cout << "=================================="<< endl;
        cout << "== (1). Biblioteca virtual ======="<< endl;
        cout << "== (2). Comunidad y grupos ======="<< endl;
        cout << "== (3). Foro de perfiles ========="<< endl;
        cout << "== (4). Clases virtuales ========="<< endl;
        cout << "== (5). Conferencias y debates ==="<< endl;
        cout << "== (6). Foro de ayuda ============"<< endl;
        cout << "== (7). Cerrar session ==========="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_menu;
        cout << endl;

        limpiar_pantalla();
    } while (opc_menu != 1 && opc_menu != 2 && opc_menu != 3 && opc_menu != 4 && opc_menu != 5 && opc_menu != 6 && opc_menu != 7);

    if (opc_menu == 1) {
        limpiar_buffer();
        Biblioteca_virtual();
    }
    else if (opc_menu == 2) {
        limpiar_buffer();
        Comunidad_grupos();
    }
    else if (opc_menu == 3) {
        limpiar_buffer();
        Foro_perfil();
    }
    else if (opc_menu == 4) {
        limpiar_buffer();
        Clases_virtuales();
    }
    else if (opc_menu == 5) {
        limpiar_buffer();
        Conferencias_debates();
    }
    else if (opc_menu == 6) {
        limpiar_buffer();
        Foro_ayuda();
    }
    else if (opc_menu == 7) {
        limpiar_buffer();
        mostrar_inicio();
    }
    
}

void Biblioteca_virtual() {
    int opc_bv;

    do {
        cout << "=================================="<< endl;
        cout << "=== Bienvenido a la Biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "===== Seleccione una opcion ======"<< endl;
        cout << "=================================="<< endl;
        cout << "== (1). Cursos generales ========="<< endl;
        cout << "== (2). Sylabo de asignaturas ===="<< endl;
        cout << "== (3). PPTs info de cursos ======"<< endl;
        cout << "== (4). Libros para ingenieria ==="<< endl;
        cout << "== (5). Examenes y Pc pasados ===="<< endl;
        cout << "== (6). Documentos cientificos ==="<< endl;
        cout << "== (7). Volver al menu ==========="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_bv;
        cout << endl;
    } while (opc_bv != 1 && opc_bv != 2 && opc_bv != 3 && opc_bv != 4 && opc_bv != 5 && opc_bv != 6 && opc_bv != 7);
    
    limpiar_pantalla();

    if (opc_bv == 1) {
        int cg;
        do {
        cout << "========================================="<< endl;
        cout << "=========== Cursos generales ============"<< endl;
        cout << "========================================="<< endl;
        cout << "== (1). Calculo I y II =================="<< endl;
        cout << "== (2). Algebra ========================="<< endl;
        cout << "== (3). Geometria Analitica ============="<< endl;
        cout << "== (4). Fisica I y II ==================="<< endl;
        cout << "== (5). Quimica I y II =================="<< endl;
        cout << "== (6). Introduccion a la progamacion ==="<< endl;
        cout << "== (7). Volver a la biblioteca =========="<< endl;
        cout << "========================================="<< endl;
        cout << "> ";
        cin >> cg;
        cout << endl;

        limpiar_pantalla();

        } while (cg != 1 && cg != 2 && cg != 3 && cg != 4 && cg != 5 && cg != 6 && cg != 7);

        if (cg == 1) {
            int calculo;
            do {
            cout << "========================================="<< endl;
            cout << "========= Seleccione una opcion ========="<< endl;
            cout << "========================================="<< endl;
            cout << "== (1). Calculo I ======================="<< endl;
            cout << "== (2). Calculo II ======================"<< endl;
            cout << "== (3). Volver a la biblioteca =========="<< endl;
            cout << "========================================="<< endl;
            cout << "> ";
            cin >> calculo;
            cout << endl;

            limpiar_pantalla();

            } while (calculo != 1 && calculo != 2 && calculo != 3);

            if (calculo == 1) {
                int tema;
                do {
                cout << "========================================="<< endl;
                cout << "========== Seleccione un tema ==========="<< endl;
                cout << "========================================="<< endl;
                cout << "== (1). Relaciones ======================"<< endl;
                cout << "== (2). Funciones ======================="<< endl;
                cout << "== (3). Limites ========================="<< endl;
                cout << "== (4). Continuidad ====================="<< endl;
                cout << "== (5). Derivadas ======================="<< endl;
                cout << "== (6). Razon de cambio ================="<< endl;
                cout << "== (7). Volver a la biblioteca =========="<< endl;
                cout << "========================================="<< endl;
                cout << "> ";
                cin >> tema;
                cout << endl;
                limpiar_pantalla();

                } while (tema != 1 && tema != 2 && tema != 3 && tema != 4 && tema != 5 && tema != 6 && tema != 7);
            
                if (tema == 7) {
                limpiar_pantalla();
                limpiar_buffer();
                Biblioteca_virtual();
                return;

                }

                int opc_volver_biblioteca;

                    do {
                    
                    cout << "=================================="<< endl;
                    cout << "== Aun no hay material aquí ======"<< endl;
                    cout << "== (1). Volver a la biblioteca ==="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> opc_volver_biblioteca;;
                    } while (opc_volver_biblioteca != 1);
                    
                    if (opc_volver_biblioteca == 1) {
                        limpiar_pantalla();
                        limpiar_buffer();
                        Biblioteca_virtual();
                        return;
                    }


            } else if (calculo == 2) {
                int tema; 
                do {
                    cout << "========================================="<< endl;
                    cout << "========== Seleccione un tema ==========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Antiderivadas ==================="<< endl;
                    cout << "== (2). Integracion de funciones ========"<< endl;
                    cout << "== (3). Suma de Riemann ================="<< endl;
                    cout << "== (4). Continuidad ====================="<< endl;
                    cout << "== (5). Integracion definida ============"<< endl;
                    cout << "== (6). Areas, vol, long y superficies =="<< endl;
                    cout << "== (7). Integrales ======================"<< endl;
                    cout << "== (8). Volver a la biblioteca =========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> tema;
                    cout << endl;

                    limpiar_pantalla();

                    } while (tema != 1 && tema != 2 && tema != 3 && tema != 4 && tema != 5 && tema != 6 && tema != 7 && tema != 8);
                    
                    if (tema == 8) {
                        limpiar_pantalla();
                        limpiar_buffer();
                        Biblioteca_virtual();
                        return;
                    }

                    int opc_volver_biblioteca;

                    do {
                    
                    cout << "=================================="<< endl;
                    cout << "== Aun no hay material aquí ======"<< endl;
                    cout << "== (1). Volver a la biblioteca ==="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> opc_volver_biblioteca;;
                    } while (opc_volver_biblioteca != 1);
                    
                    if (opc_volver_biblioteca == 1) {
                        limpiar_pantalla();
                        limpiar_buffer();
                        Biblioteca_virtual();
                        return;
                    }
                    
                    limpiar_pantalla();

                } else if (calculo == 3) {
                    limpiar_pantalla();
                    limpiar_buffer();
                    Biblioteca_virtual();
                    return;
            }
                        
        } else if (cg == 2) {
            int tema;

            do {
                
                cout << "========================================="<< endl;
                cout << "========== Seleccione un tema ==========="<< endl;
                cout << "========================================="<< endl;
                cout << "== (1). Logica =========================="<< endl;
                cout << "== (2). Induccion, sum y combinatoria ==="<< endl;
                cout << "== (3). Binomio de Newton ==============="<< endl;
                cout << "== (4). Numeros reales =================="<< endl;
                cout << "== (5). Maximo entero ==================="<< endl;
                cout << "== (6). TDR ============================="<< endl;
                cout << "== (7). Volver a la biblioteca =========="<< endl;
                cout << "========================================="<< endl;
                cout << "> ";
                cin >> tema;
                cout << endl;

            } while (tema != 1 && tema != 2 && tema != 3 && tema != 4 && tema != 5 && tema != 6 && tema != 7 );
            
            if (tema == 7) {
                limpiar_pantalla();
                limpiar_buffer();
                Biblioteca_virtual();
                return;
            }

            limpiar_pantalla();
            limpiar_buffer();


            int opc_volver_biblioteca;

            do {
                    
                    cout << "=================================="<< endl;
                    cout << "== Aun no hay material aquí ======"<< endl;
                    cout << "== (1). Volver a la biblioteca ==="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> opc_volver_biblioteca;;
                    } while (opc_volver_biblioteca != 1);
                    
                    if (opc_volver_biblioteca == 1) {
                        limpiar_pantalla();
                        limpiar_buffer();
                        Biblioteca_virtual();
                        return;
                    }


               
        } else if (cg == 3) {
            int opc_volver_biblioteca;

            do {
            
            cout << "=================================="<< endl;
            cout << "== Aun no hay material aquí ======"<< endl;
            cout << "== (1). Volver a la biblioteca ==="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_volver_biblioteca;;
            } while (opc_volver_biblioteca != 1);
            
            if (opc_volver_biblioteca == 1) {
                limpiar_pantalla();
                limpiar_buffer();
                Biblioteca_virtual();
                return;
            }
        
        } else if (cg == 4) {
            int opc_volver_biblioteca;

            do {
            
            cout << "=================================="<< endl;
            cout << "== Aun no hay material aquí ======"<< endl;
            cout << "== (1). Volver a la biblioteca ==="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_volver_biblioteca;;
            } while (opc_volver_biblioteca != 1);
            
            if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
            }
        
        } else if (cg == 5) {
            int opc_volver_biblioteca;

            do {
            
            cout << "=================================="<< endl;
            cout << "== Aun no hay material aquí ======"<< endl;
            cout << "== (1). Volver a la biblioteca ==="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_volver_biblioteca;;
            } while (opc_volver_biblioteca != 1);
            
            if (opc_volver_biblioteca == 1) {
                limpiar_pantalla();
                limpiar_buffer();
                Biblioteca_virtual();
                return;
            }

        } else if (cg == 6) {
            int opc_volver_biblioteca;

            do {
            
            cout << "=================================="<< endl;
            cout << "== Aun no hay material aquí ======"<< endl;
            cout << "== (1). Volver a la biblioteca ==="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_volver_biblioteca;;
            } while (opc_volver_biblioteca != 1);
            
            if (opc_volver_biblioteca == 1) {
                limpiar_pantalla();
                limpiar_buffer();
                Biblioteca_virtual();
                return;
            }
        
        } else if (cg == 7) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }

        
    } else if (opc_bv == 2) {
        int opc_volver_biblioteca;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Aun no hay material aquí ======"<< endl;
        cout << "== (1). Volver a la biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_volver_biblioteca;;
        } while (opc_volver_biblioteca != 1);
        
        if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }
        
    } else if (opc_bv == 3) {
        int opc_volver_biblioteca;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Aun no hay material aquí ======"<< endl;
        cout << "== (1). Volver a la biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_volver_biblioteca;;
        } while (opc_volver_biblioteca != 1);
        
        if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }

    } else if (opc_bv == 4) {
        int opc_volver_biblioteca;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Aun no hay material aquí ======"<< endl;
        cout << "== (1). Volver a la biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_volver_biblioteca;;
        } while (opc_volver_biblioteca != 1);
        
        if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }

    } else if (opc_bv == 5) {
        int opc_volver_biblioteca;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Aun no hay material aquí ======"<< endl;
        cout << "== (1). Volver a la biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_volver_biblioteca;;
        } while (opc_volver_biblioteca != 1);
        
        if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }

    } else if (opc_bv == 6) {
        int opc_volver_biblioteca;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Aun no hay material aquí ======"<< endl;
        cout << "== (1). Volver a la biblioteca ==="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_volver_biblioteca;;
        } while (opc_volver_biblioteca != 1);
        
        if (opc_volver_biblioteca == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Biblioteca_virtual();
            return;
        }

    } else if (opc_bv == 7) {
        mostrar_menu();
    }
    
    
}

void Comunidad_grupos() {
    int opc_cg;

    do{
        cout << "==================================="<< endl;
        cout << "= Bienvenido a Comunidad y Grupos ="<< endl;
        cout << "==================================="<< endl;
        cout << "===== Seleccione una opcion ======="<< endl;
        cout << "==================================="<< endl;
        cout << "== (1). Buscar usuario ============"<< endl;
        cout << "== (2). Mensajeria ================"<< endl;
        cout << "== (3). Grupos  ==================="<< endl;
        cout << "== (4). Privacidad digital ========"<< endl;
        cout << "== (5). Volver al menu ============"<< endl;
        cout << "==================================="<< endl;
        cout << "> ";
        cin >> opc_cg;
        cout << endl;

        limpiar_pantalla();

    } while (opc_cg != 1 && opc_cg != 2 && opc_cg != 3 && opc_cg != 4 && opc_cg != 5);
    
    limpiar_buffer();

    if (opc_cg == 1) {
        // Aqui podras buscar a los usuarios de la plataforma para poder agregarlos como amigos
        
        Profile usuarioBuscado = busqueda();
        if (!usuarioBuscado.encontrado) {
            Comunidad_grupos();
            return;
        }
        if (strcmp(usuarioBuscado.username, currentUser.username) == 0) {
            // te has encontrado a ti mismo
            int opc_perfil;
            
            do {
            
            cout << "=================================="<< endl;
            cout << "== Estas viendo tu perfil ========"<< endl;
            cout << "== (1). Volver a buscar =========="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_perfil;
            } while (opc_perfil !=1);

            if (opc_perfil == 1) {
                limpiar_pantalla();
                limpiar_buffer();
                Comunidad_grupos();
                return;
            }
        }

        else {
            int opc_busqueda;

            do {
            
            cout << "=================================="<< endl;
            cout << "== (1). Agregar como amigo ======="<< endl;
            cout << "== (2). Volver a buscar =========="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_busqueda;
            cout << endl;

            } while (opc_busqueda != 1 && opc_busqueda != 2);

            if (opc_busqueda == 1) {
                // agregar como amigo
                bool agregadoConExito = agregarComoAmigo(usuarioBuscado);
                limpiar_pantalla();
                if (agregadoConExito) {
                    cout << "Has agregado a " << usuarioBuscado.username << " a tus amigos!!!" << endl;
                }
                else {
                    cout << "No has podido agregar a " << usuarioBuscado.username
                         << ". Tal vez ya lo tengas agregado o llegasete al maximo" << endl;
                }
                Comunidad_grupos();
            }
            else if (opc_busqueda == 2) {
                limpiar_pantalla();
                limpiar_buffer();
                Comunidad_grupos();
            }

        }

    }
    else if (opc_cg == 2) {
        int opc_atras_cg;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Función aun no implementada ==="<< endl;
        cout << "== (1). Volver ==================="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_atras_cg;
        } while (opc_atras_cg != 1);
        
        if (opc_atras_cg == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Comunidad_grupos();
            return;
        }
    }
    else if (opc_cg == 3) {
        int opc_atras_cg;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Función aun no implementada ==="<< endl;
        cout << "== (1). Volver ==================="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_atras_cg;
        } while (opc_atras_cg != 1);
        
        if (opc_atras_cg == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Comunidad_grupos();
            return;
        }
    }
    else if (opc_cg == 4) {
        int opc_atras_cg;

        do {
        
        cout << "=================================="<< endl;
        cout << "== Función aun no implementada ==="<< endl;
        cout << "== (1). Volver ==================="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_atras_cg;
        } while (opc_atras_cg != 1);
        
        if (opc_atras_cg == 1) {
            limpiar_pantalla();
            limpiar_buffer();
            Comunidad_grupos();
            return;
        }
    }
    else if (opc_cg == 5) {
        limpiar_buffer();
        limpiar_pantalla();
        mostrar_menu();
        
    }
}

void Foro_perfil() {

    int opc_portada;

    do {
        cout << "=================================="<< endl;
        cout << "===== Seleccione una opcion ======"<< endl;
        cout << "=================================="<< endl;
        cout << "== (1). Crear perfil ============="<< endl;
        cout << "== (2). Buscar perfiles =========="<< endl;
        cout << "== (3). Volver al menu ==========="<< endl;
        cout << "=================================="<< endl;
        cout << ">";
        cin >> opc_portada;
    } while (opc_portada != 1 && opc_portada != 2 && opc_portada != 3 );

    limpiar_pantalla();
    limpiar_buffer();

    if (opc_portada == 1) {
        crearprofile();
    } else if (opc_portada == 2) {

        int opc_buscaperfil;

        do {
            cout << "=================================="<< endl;
            cout << "===== Seleccione una opcion ======"<< endl;
            cout << "=================================="<< endl;
            cout << "== (1). Buscar por nombre ========"<< endl;
            cout << "== (2). Atras ===================="<< endl;
            cout << "=================================="<< endl;
            cout << ">";
            cin >> opc_buscaperfil;

        } while (opc_buscaperfil != 1 && opc_buscaperfil != 2 );

        if (opc_buscaperfil == 1) {

            limpiar_buffer();
            limpiar_pantalla();
            
            ifstream file("profile.bin");
            Profilecv perfilcv;
            profileUser fullnamenew;
            bool profileEncontrado = false;
            char fullnamecv[128];

            cout << "================================================="<< endl;
            cout << "Introduzca el nombre que desea buscar: ";
            cin.getline(fullnamecv, sizeof(fullnamecv));
            cout << "================================================="<< endl;
            cout << endl;
            

        while (file.read((char*)&fullnamenew, sizeof(profileUser))) {
            strcpy(perfilcv.fullnameprofile, fullnamenew.fullnameprofile);
            perfilcv.age = fullnamenew.ageprofile;
            strcpy(perfilcv.nivelacademico, fullnamenew.nivelacademico);
            strcpy(perfilcv.carrera, fullnamenew.carrera);
            strcpy(perfilcv.Pais, fullnamenew.Pais);
            strcpy(perfilcv.city, fullnamenew.city);
            strcpy(perfilcv.empresaname, fullnamenew.empresaname);
            strcpy(perfilcv.time, fullnamenew.time);
            strcpy(perfilcv.cargo, fullnamenew.cargo);
            perfilcv.opc_exp = fullnamenew.opc_exp;

            if (strcmp(perfilcv.fullnameprofile, fullnamecv) == 0) {
                // Perfil encontrado!!!!!
                // está guardado dentro de la variable "perfil" de tipo "Profile"

                profileEncontrado = true;
                    cout << "Nombre: " << perfilcv.fullnameprofile << endl;
                    cout << "Edad: " << perfilcv.age << endl;
                    cout << "Nivel academico: " << perfilcv.nivelacademico << endl;
                    cout << "Carrara: " << perfilcv.carrera << endl;
                    cout << "Pais de residencia: " << perfilcv.Pais << endl;
                    cout << "Ciudad: " << perfilcv.city << endl;

                    if (perfilcv.opc_exp == 1) {
                        limpiar_buffer();
                        cout << "Experiencia laboral: " << endl;
                        cout << "Nombre de la empresa: " << perfilcv.empresaname << endl;
                        cout << "Tiempo de trabajo (meses): " << perfilcv.time << endl;
                        cout << "Cargo: " << perfilcv.cargo << endl;
                }
                perfilcv.encontrado = true;
                cout << endl;
                break;
            }
            file.close();

            if (!profileEncontrado) {

                int opc_noencontrado;
                do {
                
                cout << "=================================="<< endl;
                cout << "===== Seleccione una opcion ======"<< endl;
                cout << "=================================="<< endl;
                cout << "== No se encontró el perfil ======"<< endl;
                cout << "== (1). Atras ===================="<< endl;
                cout << "=================================="<< endl;
                cout << ">";
                cin >> opc_noencontrado;

                } while (opc_noencontrado !=1);
                if (opc_noencontrado == 1) {
                    perfilcv.encontrado = false;
                    limpiar_buffer();
                    limpiar_pantalla();
                    Foro_perfil();
                }
        
            }
            return;
        
        }
        
    
        archivoprofile.close();
        

        int opc_solicitud;

        do {
            
            cout << "======================================"<< endl;
            cout << "======= Seleccione una opcion ========"<< endl;
            cout << "======================================"<< endl;
            cout << "== (1). Enviar solicitud de trabajo =="<< endl;
            cout << "== (2). Atras ========================"<< endl;
            cout << "======================================"<< endl;
            cout << "> ";
            cin >> opc_solicitud;
            cout << endl;

        } while (opc_solicitud != 1 && opc_solicitud != 2);

            if (opc_solicitud == 1) {
                limpiar_buffer();
                limpiar_pantalla();


                int confirmarsolicitud;
                char nameempresasolicitud[64];
                char cargoempresasolicitud[64];
                char descripcionempresasolicitud[128];
                char contactoempresasolicitud[64];


                cout << "============================================="<< endl;
                cout << "=========== Formato de solicitud ============"<< endl;
                cout << "============================================="<< endl;
                cout << "== (1). Introduzca el nombre de la empresa =="<< endl;
                cout << "> ";
                cin >> nameempresasolicitud[64];
                cout << endl;
                limpiar_buffer();
                cout << "============================================="<< endl;
                cout << "== (2). Ingrese el cargo que asumirá ========"<< endl;
                cout << "> ";
                cin >> cargoempresasolicitud[64];
                cout << endl;
                limpiar_buffer();
                cout << "============================================="<< endl;
                cout << "== (3). Ingrese una breve descripción ======="<< endl;
                cout << "> ";
                cin >> descripcionempresasolicitud[128];
                cout << endl;
                limpiar_buffer();
                cout << "============================================="<< endl;
                cout << "== (3). Ingrese una forma de contacto ======="<< endl;
                cout << "> ";
                cin >> contactoempresasolicitud[64];
                cout << endl;
                limpiar_buffer();
                cout << "============================================="<< endl;

                cout << endl;
                cout << endl;

                do {
                    cout << "======================================"<< endl;
                    cout << "======= Seleccione una opcion ========"<< endl;
                    cout << "======================================"<< endl;
                    cout << "== (1). Confirmar solicitud =========="<< endl;
                    cout << "== (2). Atras ========================"<< endl;
                    cout << "======================================"<< endl;
                    cout << "> ";
                    cin >> confirmarsolicitud;
                    cout << endl;
                } while (confirmarsolicitud != 1 && confirmarsolicitud != 2);

                if (confirmarsolicitud == 1) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    cout << "Solicitud de trabajo enviada con exito !!! " << endl;
                    cout << endl;
                    Foro_perfil();
                } else if (confirmarsolicitud == 2) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    Foro_perfil();
                }
                

            } else if (opc_solicitud == 2) {
                limpiar_buffer();
                limpiar_pantalla();
                Foro_perfil();

            }
        
        } else if (opc_buscaperfil == 2) {
            limpiar_buffer();
            limpiar_pantalla();
            Foro_perfil();
        }

    } else if (opc_portada == 3) {
        limpiar_buffer();
        limpiar_pantalla();
        mostrar_menu();
    }
    

}

void Clases_virtuales() {
    int opc_cv;

    do {
        cout << "=================================="<< endl;
        cout << "===== Seleccione una opcion ======"<< endl;
        cout << "=================================="<< endl;
        cout << "== (1). En vivo =================="<< endl;
        cout << "== (2). Grabaciones =============="<< endl;
        cout << "== (3). Volver al menu ==========="<< endl;
        cout << "=================================="<< endl;
        cout << "> ";
        cin >> opc_cv;
    } while (opc_cv != 1 && opc_cv != 2 && opc_cv != 3);
    
    if (opc_cv == 1) {
        limpiar_pantalla();
        limpiar_buffer();

        int opc_cv;

        do {
            cout << "=================================="<< endl;
            cout << "===== Seleccione una opcion ======"<< endl;
            cout << "=================================="<< endl;
            cout << "== (1). Cursos generales ========="<< endl;
            cout << "== (2). Cursos de carrera ========"<< endl;
            cout << "== (3). Volver al menu ==========="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_cv;
        } while (opc_cv != 1 && opc_cv != 2 && opc_cv != 3);

            if (opc_cv == 1) {

                limpiar_pantalla();
                limpiar_buffer();
                
                int opc_cv_;

                do {
                    cout << "========================================="<< endl;
                    cout << "=========== Cursos generales ============"<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Calculo I y II =================="<< endl;
                    cout << "== (2). Algebra ========================="<< endl;
                    cout << "== (3). Geometria Analitica ============="<< endl;
                    cout << "== (4). Fisica I y II ==================="<< endl;
                    cout << "== (5). Quimica I y II =================="<< endl;
                    cout << "== (6). Introduccion a la progamacion ==="<< endl;
                    cout << "== (7). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> opc_cv_;
                    cout << endl;

                    limpiar_pantalla();

                } while (opc_cv_ != 1 && opc_cv_ != 2 && opc_cv_ != 3 && opc_cv_ != 4 && opc_cv_ != 5 && opc_cv_ != 6 && opc_cv_ != 7);
                
                int calculo_;

                if (opc_cv_ == 1) {
                    

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Calculo I ======================="<< endl;
                    cout << "== (2). Calculo II ======================"<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> calculo_;
                    cout << endl;

                    limpiar_pantalla();

                    } while (calculo_ != 1 && calculo_ != 2 && calculo_ != 3);

                    if (calculo_ == 1) {
                    int calculo_1;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> calculo_1;
                    } while (calculo_1 != 1);

                    if (calculo_1 == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }
                    


                    } else if (calculo_ == 2) {
                    int calculo_2;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> calculo_2;
                    } while (calculo_2 != 1);

                    if (calculo_2 == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

                    }


                } else if (opc_cv_ == 2) {
                    int algebra_;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> algebra_;
                    } while (algebra_ != 1);

                    if (algebra_ == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }
                
                } else if (opc_cv_ == 3) {
                    int geometria;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> geometria;
                    } while (geometria != 1);

                    if (geometria == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();

                    }

                } else if (opc_cv_ == 4) {
                    int fisica;

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Fisica I ========================"<< endl;
                    cout << "== (2). Fisica II ======================="<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> fisica;
                    cout << endl;

                    limpiar_pantalla();

                    } while (fisica != 1 && fisica != 2 && fisica != 3);

                    if (fisica == 1) {
                    int fisica_1;

                    limpiar_buffer();

                    do {
    
                        cout << "=================================="<< endl;
                        cout << "== No hay clase en este momento =="<< endl;
                        cout << "== (1). Volver atras ============="<< endl;
                        cout << "=================================="<< endl;
                        cout << "> ";
                        cin >> fisica_1;
                        } while (fisica_1 != 1);

                        if (fisica_1 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }
                    

                    } else if (fisica == 2) {
                    int fisica_2;

                    limpiar_buffer();

                    do {
    
                        cout << "=================================="<< endl;
                        cout << "== No hay clase en este momento =="<< endl;
                        cout << "== (1). Volver atras ============="<< endl;
                        cout << "=================================="<< endl;
                        cout << "> ";
                        cin >> fisica_2;
                        } while (fisica_2 != 1);

                        if (fisica_2 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }

                    }

                } else if (opc_cv_ == 5) {
                    int quimica;

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Quimica I ======================="<< endl;
                    cout << "== (2). Quimica II ======================"<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> quimica;
                    cout << endl;

                    limpiar_pantalla();

                    } while (quimica != 1 && quimica != 2 && quimica != 3);

                    if (quimica == 1) {
                    int quimica_1;

                    limpiar_buffer();

                    do {
    
                        cout << "=================================="<< endl;
                        cout << "== No hay clase en este momento =="<< endl;
                        cout << "== (1). Volver atras ============="<< endl;
                        cout << "=================================="<< endl;
                        cout << "> ";
                        cin >> quimica_1;
                        } while (quimica_1 != 1);

                        if (quimica_1 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }
                    

                    } else if (quimica == 2) {
                    int quimica_2;

                    limpiar_buffer();

                    do {
    
                        cout << "=================================="<< endl;
                        cout << "== No hay clase en este momento =="<< endl;
                        cout << "== (1). Volver atras ============="<< endl;
                        cout << "=================================="<< endl;
                        cout << "> ";
                        cin >> quimica_2;
                        } while (quimica_2 != 1);

                        if (quimica_2 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }

                    }

                } else if (opc_cv_ == 6) {
                    int intro_progra;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> intro_progra;
                    } while (intro_progra != 1);

                    if (intro_progra == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

                } else if (opc_cv_ == 7) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    Clases_virtuales();
                }
                
                
            } else if (opc_cv == 2) {

                limpiar_pantalla();
                limpiar_buffer();
                
                int selec_carrera;

                do {
                    cout << "=========================================================="<< endl;
                    cout << "================== Selecciona tu carrera ================="<< endl;
                    cout << "=========================================================="<< endl;
                    cout << "== (1). Ingeniería de Sistemas ==========================="<< endl;
                    cout << "== (2). Ingeniería de Software ==========================="<< endl;
                    cout << "== (3). Ingeniería Biomédica ============================="<< endl;
                    cout << "== (4). Ingeniería Electrónica ==========================="<< endl;
                    cout << "== (5). Ingeniería Eléctrica ============================="<< endl;
                    cout << "== (6). Ingeniería de Telecomunicaciones ================="<< endl;
                    cout << "== (7). Ingeniería Geográfica ============================"<< endl;
                    cout << "== (8). Ingeniería Geológica ============================="<< endl;
                    cout << "== (9). Ingeniería Civil ================================="<< endl;
                    cout << "== (10). Ingeniería Metalúrgica =========================="<< endl;
                    cout << "== (11). Ingeniería de Minas ============================="<< endl;
                    cout << "== (12). Ingeniería Ambiental ============================"<< endl;
                    cout << "== (13). Ingeniería Textil y Confecciones ================"<< endl;
                    cout << "== (14). Ingeniería Industrial ==========================="<< endl;
                    cout << "== (15). Ingeniería de Seguridad y Salud en el Trabajo ==="<< endl;
                    cout << "== (16). Ingeniería Química =============================="<< endl;
                    cout << "== (17). Ingeniería Agroindustrial ======================="<< endl;
                    cout << "== (18). Ingeniería Mecánica de Fluidos =================="<< endl;
                    cout << "== (19). Volver atras ===================================="<< endl;
                    cout << "=========================================================="<< endl;
                    cout << "> ";
                    cin >> selec_carrera;
                    cout << endl;

                    limpiar_pantalla();

                } while (selec_carrera != 1 && selec_carrera != 2 && selec_carrera != 3 && selec_carrera != 4 && selec_carrera != 5 && selec_carrera != 6 && selec_carrera != 7 && selec_carrera != 8 && selec_carrera != 9 && selec_carrera != 10 && selec_carrera != 11 && selec_carrera != 12 && selec_carrera != 13 && selec_carrera != 13 && selec_carrera != 14 && selec_carrera != 15 && selec_carrera != 16 && selec_carrera != 17 && selec_carrera != 18 && selec_carrera != 19 );

                if (selec_carrera == 19) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    Clases_virtuales();
                }
                
                int selec_carrera_;

                    limpiar_buffer();

                    do {
    
                    cout << "=================================="<< endl;
                    cout << "== No hay clase en este momento =="<< endl;
                    cout << "== (1). Volver atras ============="<< endl;
                    cout << "=================================="<< endl;
                    cout << "> ";
                    cin >> selec_carrera_;
                    } while (selec_carrera_ != 1);

                    if (selec_carrera_ == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

            }
        

    } else if (opc_cv == 2) {
        
        limpiar_pantalla();
        limpiar_buffer();

        int opc_cv;

        do {
            cout << "=================================="<< endl;
            cout << "===== Seleccione una opcion ======"<< endl;
            cout << "=================================="<< endl;
            cout << "== (1). Cursos generales ========="<< endl;
            cout << "== (2). Cursos de carrera ========"<< endl;
            cout << "== (3). Volver al menu ==========="<< endl;
            cout << "=================================="<< endl;
            cout << "> ";
            cin >> opc_cv;
        } while (opc_cv != 1 && opc_cv != 2 && opc_cv != 3);

            if (opc_cv == 1) {

                limpiar_pantalla();
                limpiar_buffer();

                int opc_cv_;

                do {
                    cout << "========================================="<< endl;
                    cout << "=========== Cursos generales ============"<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Calculo I y II =================="<< endl;
                    cout << "== (2). Algebra ========================="<< endl;
                    cout << "== (3). Geometria Analitica ============="<< endl;
                    cout << "== (4). Fisica I y II ==================="<< endl;
                    cout << "== (5). Quimica I y II =================="<< endl;
                    cout << "== (6). Introduccion a la progamacion ==="<< endl;
                    cout << "== (7). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> opc_cv_;
                    cout << endl;

                    limpiar_pantalla();

                } while (opc_cv_ != 1 && opc_cv_ != 2 && opc_cv_ != 3 && opc_cv_ != 4 && opc_cv_ != 5 && opc_cv_ != 6 && opc_cv_ != 7);
                
                int calculo_;

                if (opc_cv_ == 1) {
                    
                    limpiar_buffer();

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Calculo I ======================="<< endl;
                    cout << "== (2). Calculo II ======================"<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> calculo_;
                    cout << endl;

                    limpiar_pantalla();

                    } while (calculo_ != 1 && calculo_ != 2 && calculo_ != 3);

                    if (calculo_ == 1) {
                    int calculo_1;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> calculo_1;
                    } while (calculo_1 != 1);

                    if (calculo_1 == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }
                    


                    } else if (calculo_ == 2) {
                    int calculo_2;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> calculo_2;
                    } while (calculo_2 != 1);

                    if (calculo_2 == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

                    }


                } else if (opc_cv_ == 2) {
                    int algebra_;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> algebra_;
                    } while (algebra_ != 1);

                    if (algebra_ == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }
                
                } else if (opc_cv_ == 3) {
                    int geometria;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> geometria;
                    } while (geometria != 1);

                    if (geometria == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();

                    }

                } else if (opc_cv_ == 4) {
                    int fisica;

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Fisica I ========================"<< endl;
                    cout << "== (2). Fisica II ======================="<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> fisica;
                    cout << endl;

                    limpiar_pantalla();

                    } while (fisica != 1 && fisica != 2 && fisica != 3);

                    if (fisica == 1) {
                    int fisica_1;

                    limpiar_buffer();

                    do {
    
                        cout << "========================================"<< endl;
                        cout << "== No hay grabaciones en este momento =="<< endl;
                        cout << "== (1). Volver atras ==================="<< endl;
                        cout << "========================================"<< endl;
                        cout << "> ";
                        cin >> fisica_1;
                        } while (fisica_1 != 1);

                        if (fisica_1 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }
                    

                    } else if (fisica == 2) {
                    int fisica_2;

                    limpiar_buffer();

                    do {
    
                        cout << "========================================"<< endl;
                        cout << "== No hay grabaciones en este momento =="<< endl;
                        cout << "== (1). Volver atras ==================="<< endl;
                        cout << "========================================"<< endl;
                        cout << "> ";
                        cin >> fisica_2;
                        } while (fisica_2 != 1);

                        if (fisica_2 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }

                    }

                } else if (opc_cv_ == 5) {
                    int quimica;

                    do {
                    cout << "========================================="<< endl;
                    cout << "========= Seleccione una opcion ========="<< endl;
                    cout << "========================================="<< endl;
                    cout << "== (1). Quimica I ======================="<< endl;
                    cout << "== (2). Quimica II ======================"<< endl;
                    cout << "== (3). Volver atras ===================="<< endl;
                    cout << "========================================="<< endl;
                    cout << "> ";
                    cin >> quimica;
                    cout << endl;

                    limpiar_pantalla();

                    } while (quimica != 1 && quimica != 2 && quimica != 3);

                    if (quimica == 1) {
                    int quimica_1;

                    limpiar_buffer();

                    do {
    
                        cout << "========================================"<< endl;
                        cout << "== No hay grabaciones en este momento =="<< endl;
                        cout << "== (1). Volver atras ==================="<< endl;
                        cout << "========================================"<< endl;
                        cout << "> ";
                        cin >> quimica_1;
                        } while (quimica_1 != 1);

                        if (quimica_1 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }
                    

                    } else if (quimica == 2) {
                    int quimica_2;

                    limpiar_buffer();

                    do {
    
                        cout << "========================================"<< endl;
                        cout << "== No hay grabaciones en este momento =="<< endl;
                        cout << "== (1). Volver atras ==================="<< endl;
                        cout << "========================================"<< endl;
                        cout << "> ";
                        cin >> quimica_2;
                        } while (quimica_2 != 1);

                        if (quimica_2 == 1) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Clases_virtuales();
                        }

                    }

                } else if (opc_cv_ == 6) {
                    int intro_progra;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> intro_progra;
                    } while (intro_progra != 1);

                    if (intro_progra == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

                } else if (opc_cv_ == 7) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    Clases_virtuales();
                }
                
                
            } else if (opc_cv == 2) {

                limpiar_pantalla();
                limpiar_buffer();

                int selec_carrera;

                do {
                    cout << "=========================================================="<< endl;
                    cout << "================== Selecciona tu carrera ================="<< endl;
                    cout << "=========================================================="<< endl;
                    cout << "== (1). Ingeniería de Sistemas ==========================="<< endl;
                    cout << "== (2). Ingeniería de Software ==========================="<< endl;
                    cout << "== (3). Ingeniería Biomédica ============================="<< endl;
                    cout << "== (4). Ingeniería Electrónica ==========================="<< endl;
                    cout << "== (5). Ingeniería Eléctrica ============================="<< endl;
                    cout << "== (6). Ingeniería de Telecomunicaciones ================="<< endl;
                    cout << "== (7). Ingeniería Geográfica ============================"<< endl;
                    cout << "== (8). Ingeniería Geológica ============================="<< endl;
                    cout << "== (9). Ingeniería Civil ================================="<< endl;
                    cout << "== (10). Ingeniería Metalúrgica =========================="<< endl;
                    cout << "== (11). Ingeniería de Minas ============================="<< endl;
                    cout << "== (12). Ingeniería Ambiental ============================"<< endl;
                    cout << "== (13). Ingeniería Textil y Confecciones ================"<< endl;
                    cout << "== (14). Ingeniería Industrial ==========================="<< endl;
                    cout << "== (15). Ingeniería de Seguridad y Salud en el Trabajo ==="<< endl;
                    cout << "== (16). Ingeniería Química =============================="<< endl;
                    cout << "== (17). Ingeniería Agroindustrial ======================="<< endl;
                    cout << "== (18). Ingeniería Mecánica de Fluidos =================="<< endl;
                    cout << "== (19). Volver atras ===================================="<< endl;
                    cout << "=========================================================="<< endl;
                    cout << "> ";
                    cin >> selec_carrera;
                    cout << endl;

                    limpiar_pantalla();

                } while (selec_carrera != 1 && selec_carrera != 2 && selec_carrera != 3 && selec_carrera != 4 && selec_carrera != 5 && selec_carrera != 6 && selec_carrera != 7 && selec_carrera != 8 && selec_carrera != 9 && selec_carrera != 10 && selec_carrera != 11 && selec_carrera != 12 && selec_carrera != 13 && selec_carrera != 13 && selec_carrera != 14 && selec_carrera != 15 && selec_carrera != 16 && selec_carrera != 17 && selec_carrera != 18 && selec_carrera != 19 );

                if (selec_carrera == 19) {
                    limpiar_buffer();
                    limpiar_pantalla();
                    Clases_virtuales();
                }
                
                int selec_carrera_;

                    limpiar_buffer();

                    do {
    
                    cout << "========================================"<< endl;
                    cout << "== No hay grabaciones en este momento =="<< endl;
                    cout << "== (1). Volver atras ==================="<< endl;
                    cout << "========================================"<< endl;
                    cout << "> ";
                    cin >> selec_carrera_;
                    } while (selec_carrera_ != 1);

                    if (selec_carrera_ == 1) {
                        limpiar_buffer();
                        limpiar_pantalla();
                        Clases_virtuales();
                    }

            }

    } else if (opc_cv == 3) {
            limpiar_pantalla();
            limpiar_buffer();
            mostrar_menu();
            return;
        }
    
}

void Conferencias_debates() {
    int opc_cd;

    do {
    
    cout << "========================================="<< endl;
    cout << "========= Seleccione una opcion ========="<< endl;
    cout << "========================================="<< endl;
    cout << "== (1). Conferencias ===================="<< endl;
    cout << "== (2). Debates ========================="<< endl;
    cout << "== (3). Volver al menu =================="<< endl;
    cout << "========================================="<< endl;
    cout << "> ";
    cin >> opc_cd;
    } while (opc_cd != 1 && opc_cd != 2 && opc_cd != 3);
    
    if (opc_cd == 1) {
        limpiar_buffer();
        limpiar_pantalla();
        int conferencias;

            limpiar_buffer();

            do {
    
            cout << "========================================"<< endl;
            cout << "== No hay conferencias en este momento ="<< endl;
            cout << "== (1). Volver al menu ================="<< endl;
            cout << "========================================"<< endl;
            cout << "> ";
            cin >> conferencias;
            } while (conferencias != 1);

            if (conferencias == 1) {
                limpiar_buffer();
                limpiar_pantalla();
                mostrar_menu();
            }
        

    } else if (opc_cd == 2) {
        limpiar_buffer();
        limpiar_pantalla();
        int debates;

            limpiar_buffer();

            do {
    
            cout << "========================================"<< endl;
            cout << "== No hay debates en este momento ======"<< endl;
            cout << "== (1). Volver al menu ================="<< endl;
            cout << "========================================"<< endl;
            cout << "> ";
            cin >> debates;
            } while (debates != 1);

            if (debates == 1) {
                limpiar_buffer();
                limpiar_pantalla();
                mostrar_menu();
            }
        
        
    } else if (opc_cd == 3) {
        limpiar_pantalla();
        limpiar_buffer();
        mostrar_menu();
        return;
    }
}

void Foro_ayuda() {
    int opc_fa;

    do {
    
    cout << "========================================="<< endl;
    cout << "========= Seleccione una opcion ========="<< endl;
    cout << "========================================="<< endl;
    cout << "== (1). Atención psicológica ============"<< endl;
    cout << "== (2). Preguntas y respuestas =========="<< endl;
    cout << "== (3). Volver al menu =================="<< endl;
    cout << "========================================="<< endl;
    cout << "> ";
    cin >> opc_fa;
    } while (opc_fa != 1 && opc_fa != 2 && opc_fa != 3);
    
    if (opc_fa == 1) {
        int psico;

        limpiar_buffer();
        limpiar_pantalla();

        do {
    
        cout << "========================================="<< endl;
        cout << "========= Seleccione una opcion ========="<< endl;
        cout << "========================================="<< endl;
        cout << "== (1). Solicitar un especialista ======="<< endl;
        cout << "== (2). Volver a atras =================="<< endl;
        cout << "========================================="<< endl;
        cout << "> ";
        cin >> psico;
        } while (psico != 1 && psico != 2);

        if (psico == 1) {
            limpiar_buffer();
            limpiar_pantalla();

            int volver_psico;


            do {
            
            cout << "========================================="<< endl;
            cout << "========= Solicitud enviada !!! ========="<< endl;
            cout << "== Pronto nos comunicaremos con usted ==="<< endl;
            cout << "== (1). Volver a atras =================="<< endl;
            cout << "========================================="<< endl;
            cout << "> ";
            cin >> volver_psico;
            } while (volver_psico != 1);

            limpiar_buffer();
            limpiar_pantalla();
            Foro_ayuda();

        } else if (psico == 2) {
            limpiar_buffer();
            limpiar_pantalla();
            Foro_ayuda();

        }  

    } else if (opc_fa == 2) {

        limpiar_buffer();
        limpiar_pantalla();

        int pyr;

        do {
            cout << "========================================="<< endl;
            cout << "========= Seleccione una opcion ========="<< endl;
            cout << "========================================="<< endl;
            cout << "== (1). Ver preguntas ==================="<< endl;
            cout << "== (2). Crear pregunta =================="<< endl;
            cout << "== (3). Volver a atras =================="<< endl;
            cout << "========================================="<< endl;
            cout << "> ";
            cin >> pyr;
        } while (pyr != 1 && pyr != 2 && pyr != 3);

        if (pyr == 1) {
            limpiar_buffer();
            limpiar_pantalla();

            ifstream file("preguntas.bin");
            verpregunta verpregunta_;
            creapregunta pregunta;
            bool preguntaEncontrado = false;

            while (file.read((char*)&pregunta, sizeof(creapregunta))) {
                strcpy(verpregunta_.respon_pregunta, pregunta.crea_pregunta);
                verpregunta_.opc_preg = pregunta.opc_preg;

                preguntaEncontrado = true;
                if (verpregunta_.opc_preg == 1) {
                        limpiar_buffer();
                        cout << "========================================="<< endl;
                        cout << "=============== PREGUNTAS ==============="<< endl;
                        cout << "========================================="<< endl;
                        cout << "Pregunta 01 : " << verpregunta_.respon_pregunta << endl;
                        cout << endl;

                        int responder_pregunta;
                        do {
                        
                        cout << "========================================="<< endl;
                        cout << "== (1). Responder la pregunta ==========="<< endl;
                        cout << "== (2). volver atras ===================="<< endl;
                        cout << "========================================="<< endl;
                        cout << "> ";
                        cin >> responder_pregunta;

                        } while (responder_pregunta != 1 && responder_pregunta != 2);

                        if (responder_pregunta == 1) {
                            limpiar_buffer();
                            char respondiendo[512];
                            cout << "=========================================="<< endl;
                            cout << "== Escriba su respuesta =================="<< endl;
                            cin >> respondiendo[512];
                            
                            limpiar_buffer();
                            limpiar_pantalla();
                            cout << " Respuesta enviada con exito !!! "<< endl;
                            Foro_ayuda();

                        } else if (responder_pregunta == 2) {
                            limpiar_buffer();
                            limpiar_pantalla();
                            Foro_ayuda();
                        }
                        

                }
                verpregunta_.encontrado = true;
                cout << endl;
                break;

            }
            file.close();

            if (!preguntaEncontrado) {

                int opc_no_encontrado;
                do {
                
                cout << "=========================================="<< endl;
                cout << "== No hay preguntas en este momento ======"<< endl;
                cout << "== (1). Atras ============================"<< endl;
                cout << "=========================================="<< endl;
                cout << ">";
                cin >> opc_no_encontrado;

                } while (opc_no_encontrado !=1);
                if (opc_no_encontrado == 1) {
                    verpregunta_.encontrado = false;
                    limpiar_buffer();
                    limpiar_pantalla();
                    Foro_ayuda();
                }
        
            }
            return;

        } else if (pyr == 2) {
            pregunta_crea();

        } else if (pyr == 3) {
            limpiar_buffer();
            limpiar_pantalla();
            Foro_ayuda();
        }
        
        
        
        

    } else if (opc_fa == 3) {
        limpiar_pantalla();
        mostrar_menu();
        //return;
    }

}


void pregunta_crea() {

    ofstream archivocreapregunta;
    archivocreapregunta.open("preguntas.bin", ios::out | ios::app | ios::binary);

    if (archivocreapregunta.is_open()) {
        //int opc_preg;

        do {
        
            cout << "========================================="<< endl;
            cout << "========= Seleccione una opcion ========="<< endl;
            cout << "========================================="<< endl;
            cout << "== (1). Empezar a crear una pregunta ===="<< endl;
            cout << "== (2). volver atras ===================="<< endl;
            cout << "========================================="<< endl;
            cout <<  "> ";
            cin >> currentpregunta.opc_preg;

        } while (currentpregunta.opc_preg !=1 && currentpregunta.opc_preg !=2);

        if (currentpregunta.opc_preg == 1) {
            limpiar_buffer();
            cout << "========================================="<< endl;
            cout << "Ingresa tu pregunta : ";
            cout <<  "> ";
            cin.getline(currentpregunta.crea_pregunta, 512);


            cout << "Pregunta creada con exitoso!" << endl;

            archivocreapregunta.write((char*)&currentpregunta, sizeof(creapregunta));
            archivocreapregunta.close();

        } else if (currentpregunta.opc_preg == 2) {
            limpiar_pantalla();
            limpiar_buffer();
            Foro_ayuda();
        }


        limpiar_buffer();
        limpiar_pantalla();
        Foro_ayuda();
    }

}


bool existeCorreo(char correo[32]) {
    archivo.open("datos.bin", ios::in | ios::binary);
    bool siExiste = false;
    if (archivo.is_open()) {
        User usuarioLectura;
        while (archivo.read((char*)&usuarioLectura, sizeof(User))) {
            if (strcmp(usuarioLectura.email, correo) == 0) {
                siExiste = true;
                break;
            }
        }
    }
    archivo.close();
    return siExiste;
}

bool existeUsuario(char usuario[32]) {
    archivo.open("datos.bin", ios::in | ios::binary);
    bool siExiste = false;
    if (archivo.is_open()) {
        User usuarioLectura;
        while (archivo.read((char*)&usuarioLectura, sizeof(User))) {
            if (strcmp(usuarioLectura.username, usuario) == 0) {
                siExiste = true;
                break;
            }
        }
    }
    archivo.close();
    return siExiste;
}


bool amigoYaAgregado(char usuario[32]) {
    for (int i = 0; i < currentUser.friendsCount; i++) {
        if (strcmp(currentUser.friends[i], usuario) == 0) {
            return true;
        }
    }
    return false;
}


bool agregarComoAmigo(Profile nuevoAmigo) {
    if (currentUser.friendsCount < AMIGOS_MAXIMOS && !amigoYaAgregado(nuevoAmigo.username)) {
        memcpy(currentUser.friends[currentUser.friendsCount], nuevoAmigo.username, 32);
        currentUser.friendsCount++;

        User usuarioAgregado = obtenerUsuario(nuevoAmigo.username);

        memcpy(usuarioAgregado.friends[usuarioAgregado.friendsCount], currentUser.username, 32);
        usuarioAgregado.friendsCount++;
        actualizarUsuario(usuarioAgregado.username, usuarioAgregado);
        actualizarUsuario(currentUser.username, currentUser);
        return true;
    }
    return false;
}


void actualizarUsuario(char username[32], User usuarioActualizado) {
    // Actualizar un nuevo usuario en la base de datos
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);

    if (archivo.is_open()) {
        User usuarioLectura;
        while (archivo.read((char*)&usuarioLectura, sizeof(User))) {
            if (strcmp(usuarioLectura.username, username) == 0) {
                archivo.seekp(-sizeof(User), ios::cur);
                archivo.write((char*)&usuarioActualizado, sizeof(User));
                break;
            }
        }
    }
    archivo.close();
}


void limpiar_pantalla() {
#if defined(_WIN32) || defined(_WINDOWS)
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

void limpiar_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}