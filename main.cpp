#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
// Definiciones
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

// Funciones prototipoooo
void gotoxy(int x, int y);
void cuadro_p(int xs, int ys, int xi, int yi);
int flecha(int x, int y, int y_Superior, int y_Regreso, int saltos);
void cursor(bool x);
void limpia_linea(int y);
void bloqueo_maximizar();

//Variables Globales
bool salir = false;
int i;

//Atributo para funciones
using namespace std;
int main()
{
    system("mode con: cols=121 lines=29");
    bloqueo_maximizar();
    system("cls");
    cuadro_p(0, 0, 120,28);
    gotoxy(33, 2);
    cout << "------------> BIENVENIDO *USUARIO* <------------" << endl;
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
    system("cls");
}

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
    for (i = 1; i < 120; i++)
    {
        gotoxy(i, ys);
        cout << char(196);
        gotoxy(i, yi);
        cout << char(196);
    }
    for (i = 1; i < 28; i++)
    {
        gotoxy(xs, i);
        cout << char(179);
        gotoxy(xi, i);
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
    cci.dwSize = 50;
    cci.bVisible = x;
    SetConsoleCursorInfo(hCon, &cci);
}
void bloqueo_maximizar()
{
    HWND consoleWindow;
    consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}