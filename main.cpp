#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <vector>

// Definiciones de Flechas direcionales
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

#define PASSWORD_ADMIN "Admin"
#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3
#define NUM_SUPERVISORES 2

// Funciones prototipoooo
void gotoxy(int x, int y);
void cuadro_p(int xs, int ys, int xi, int yi);
int flecha(int x, int y, int y_Superior, int y_Regreso, int saltos);
void cursor(bool x);
void limpia_linea(int y);
void bloqueo_maximizar();
bool identificacion();
void precione_una_tecla_para_continuar();
void pedir_Datos();
int inicializar_Supervisores();
int actualizar_Supervisores();
int login();
// Variables Globales
bool salir = false;
int i = 0;

// Estructura para representar a los supervisores
struct Persona
{
    char id[10];
    char nombre[20];
    char apellido[20];
    // string area_Trabajo;
    // int nivel_Jerarquico;
    // int trabajadores_Cargo;
} Supervisores[NUM_SUPERVISORES];

// Atributo para funciones
using namespace std;

int main()
{
    bloqueo_maximizar();
    login();
    system("mode con: cols=121 lines=29");
    system("cls");
    cuadro_p(0, 0, 120, 28);
    gotoxy(33, 2);
    cout << "------------> BIENVENIDO *Id_Login* <------------" << endl;
    gotoxy(8, 5);
    cout << "1.- Escoger Alimentos" << endl;
    gotoxy(8, 7);
    cout << "2.- Modificar mis datos" << endl;
    gotoxy(8, 9);
    cout << "3.- Ultimas 10 facturas" << endl;
    gotoxy(8, 11);
    cout << "4.- Gestion de supervisores (Administrador)" << endl;
    gotoxy(8, 13);
    cout << "Salir" << endl;
    int opcion = flecha(4, 5, 13, 5, 2);
    switch (opcion)
    {
    case 5:
        pedir_Datos();
        break;

    default:
        break;
    }
    system("cls");
}

void pedir_Datos()
{
    inicializar_Supervisores();
    for (i = 0; i < NUM_SUPERVISORES; i++)
    {
        system("cls");
        cuadro_p(0, 0, 120, 28);
        gotoxy(40, 2);
        cout << "Ingrese los datos del supervisor " << i + 1 << endl;
        gotoxy(3, 5);
        cout << "Nombre del docente >> ";
        cin.getline(Supervisores[i].nombre, 20, '\n');
        gotoxy(3, 6);
        cout << "Apellido del docente >> ";
        cin.getline(Supervisores[i].nombre, 20, '\n');
    }
    actualizar_Supervisores();
}

void mostrar_Datos()
{
    inicializar_Supervisores();
    for (i = 0; i < NUM_SUPERVISORES; i++)
    {
        system("cls");
        cuadro_p(0, 0, 120, 28);
        gotoxy(40, 2);
        cout << "Ingrese los datos del supervisor " << i + 1 << endl;
        gotoxy(3, 5);
        cout << "Nombre del docente " << i << ": " << Supervisores[i].nombre;
        gotoxy(3, 6);
        cout << "Apellido del docente >> " << i << ": " << Supervisores[i].apellido;
    }
}
// bool identificacion()
// {
//     int identificacion = 0;
//     cout << "Ingrese la identificacion del supervisor > ";
//     cin >> identificacion;
//     for (i = 0; i <= NUM_SUPERVISORES; i++)
//     {
//         if (identificacion == Supervisores[i].id)
//         {
//             return true;
//         }
//     }
//     cout << "No existe esa identificacion en el sistema " << endl;
//     return false;
// }

int flecha(int x, int y, int y_Superior, int y_Regreso, int saltos)
{
    bool salir = false;
    gotoxy(x, y);
    cout << "==>";
    while (salir == false)
    {
        if (kbhit)
        {
            cursor(FALSE);
            char tecla = getch();
            gotoxy(x, y);
            cout << "   ";
            if (tecla == 'w' || tecla == ARRIBA)
            {
                y -= saltos;
            }
            if (tecla == 's' || tecla == ABAJO)
            {
                y += saltos;
            }
            if (y > y_Superior || y < y_Regreso)
                y = y_Regreso;
            if (tecla == 32 || tecla == 13)
                salir = true;
            gotoxy(x, y);
            cout << "==>";
        }
        Sleep(100);
    }
    cursor(TRUE);
    return y;
}

void limpia_linea(int y)
{
    gotoxy(1, y);
    for (i = 0; i < 3; i++)
    {
        cout << "                                       ";
    }
}

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}
void cuadro_p(int xs, int ys, int xi, int yi)
{
    int z; // Utilizo Z porque al poner i me toma el valor de las asignaciones que se hacen acá.
    for (z = xs; z < xi; z++)
    {
        gotoxy(z, ys);
        cout << char(196);
        gotoxy(z, yi);
        cout << char(196);
    }
    for (z = ys; z < yi; z++)
    {
        gotoxy(xs, z);
        cout << char(179);
        gotoxy(xi, z);
        cout << char(179);
    }

    // Esquinas Inferiores
    gotoxy(xs, yi);
    cout << char(192);
    gotoxy(xi, yi);
    cout << char(217);
    // Esquinas superiores
    gotoxy(xs, ys);
    cout << char(218);
    gotoxy(xi, ys);
    cout << char(191);
}

void cursor(bool x)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 10;
    cci.bVisible = x;
    SetConsoleCursorInfo(hCon, &cci);
}
void bloqueo_maximizar()
{
    HWND consoleWindow;
    consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

int inicializar_Supervisores()
{
    FILE *data_supervisores = fopen("dato/datos_supervisores.txt", "rb");
    if (data_supervisores == NULL)
    {
        // El archivo no existe, crearlo y abrirlo en modo de escritura
        data_supervisores = fopen("dato/datos_supervisores.txt", "wb");
        if (data_supervisores == NULL)
        {
            cout << "Error al abrir o crear el archivo de registros de docentes" << endl;
            return 1;
        }
    }
    else
    {
        // Leer la estructura del archivo
        fread(Supervisores, sizeof(struct Persona), NUM_SUPERVISORES, data_supervisores);
    }
    fclose(data_supervisores);
    return 0;
}

int actualizar_Supervisores()
{
    FILE *data_supervisores = fopen("dato/datos_supervisores.txt", "wb");
    if (data_supervisores == NULL)
    {
        cout << "Error al abrir el archivo de registros de docentes" << endl;
        return 1;
    }
    // Escribir la estructura en el archivo
    fwrite(Supervisores, sizeof(struct Persona), NUM_SUPERVISORES, data_supervisores);
    fclose(data_supervisores);
    return 0;
}

void precione_una_tecla_para_continuar()
{
    cursor(0);
    printf(">> Precione una tecla para continuar <<\n");
    system("pause//data>>clear");
    system("cls");
    cursor(1);
}

int login()
{
    system("mode con: cols=57 lines=15");
    vector<string> arrays_Id;

    // Se añaden arrays_Id al vectord
    arrays_Id.push_back("Admin");

    string Id_Login;

    int contador = 0;
    bool ingresa = false;

    do
    {
        system("cls");
        cuadro_p(0, 0, 56, 14);
        gotoxy(20, 2);
        cout << "LOGIN DE SUPERVISORES";
        gotoxy(20, 3);
        cout << "----------------";
        cursor(true);
        gotoxy(6, 6);
        cout << "Identificacion >> ";
        getline(cin, Id_Login);

        for (int i = 0; i < NUM_SUPERVISORES; i++)
        {
            if (Id_Login == Supervisores[i].id)
            {
                ingresa = true;
                break;
            }
            if(Id_Login == PASSWORD_ADMIN){
                ingresa = true;
                break;
            }
        }

        if (!ingresa)
        {
            gotoxy(6, 14);
            cout << "La identificacion es incorrecta";
            gotoxy(6, 12);
            precione_una_tecla_para_continuar();
            contador++;
        }

    } while (ingresa == false && contador < INTENTOS);

    if (ingresa == false)
    {
        gotoxy(4, 12);
        cout << "Usted no pudo ingresar al sistema. ADIOS" << endl;
        Sleep(2000);
    }
    else
    {
        /*
        Aquí va el código del programa cuando el Id_Login ingresa sus credenciales correctas
        */
    }
    return 0;
}