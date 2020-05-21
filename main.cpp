/********************************************************************
*                         SISTEMA INVENTARI                       	*
*                           Version 1.0                             *
*      				Ernest Benaiges i Gallego         				*
********************************************************************/

#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <fstream>

#define Color_Red 12
#define Color_Def 15
#define Color_Yellow 14
#define Color_Green 10
#define Delay_us 0
#define Cursor 16
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define Max_Chars 12

using namespace std;

COORD coord = {0,0};
char KEY_PAD;

struct Article_Struct
{
    char Name[Max_Chars];
    float Price;
    float Cost;
    int Pieces;
    float Value;
};

struct Article_Struct *Pointer_Articles[100];

void gotoxy(int x,int y);
void Show_Title (void);
int Wait_Option (void);
int New_Product (void);
int Delete_Product (void);
int Buy_Product (void);
int Sell_Product (void);
int Report_Product (void);
int Get_Elements_Number (void);
void Init_Structure_Elements (int Article);
int Save_File (void);
int Load_File (void);
void Show_Error (char *Pointer_String, int Show_Delay_us);

int Counter_Articles = 0;
char File_Name [Max_Chars];
float Total_Inventary = 0;

int main()
{
    for (int i = 0; i<Max_Chars ; i++)
    {
        File_Name[i] = 0;
    }

    for(;;)
    {
        switch (Wait_Option ())
        {
            case 1:
                New_Product ();
            break;

            case 2:
                Delete_Product ();
            break;

            case 3:
                Buy_Product ();
            break;

            case 4:
                Sell_Product ();
            break;

            case 5:
                Report_Product ();
            break;

            case 6:
                Save_File ();
            break;

            case 7:
                Load_File ();
            break;

            case 8:
                return EXIT_SUCCESS;
            break;
        }
    }
}

/********************************************************************
*                       Funcion:  gotoxy                           *
* Argumentos de entrada:                                           *
* - Enteros: Coordenadas X e Y en la pantalla.                     *
* Argumentos de salida:                                            *
* -----------------                                                *
* Esta función mueve el cursor a una coordenada específica.        *
********************************************************************/
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/********************************************************************
*                     Función: Select_Option                        *
* Esta función solo presenta el programa al usuario.                *
********************************************************************/
void Show_Title (void)
{
    int X = 0;
    int Y = 0;

    system("cls");

char Line1[] = {"  ----------------------------------------------------------------------------   "};
    char Line2[] = {" |                         SISTEMA INVENTARI V.1                              |  "};
    char Line3[] = {" |                                                                            |  "};
    char Line4[] = {" |                         PROJECTE   DAS2   M13                              |  "};
    char Line5[] = {" |                        ERNEST BENAIGES GALLEGO                             |  "};
    char Line6[] = {"  ----------------------------------------------------------------------------   "};


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    gotoxy (X,Y+2);
    for (unsigned int i= 0; i < sizeof(Line1); i++)
    {
        cout << Line1[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+3);
    for (unsigned int i= 0; i < sizeof(Line2); i++)
    {
        cout << Line2[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+4);
    for (unsigned int i= 0; i < sizeof(Line3); i++)
    {
        cout << Line3[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+5);
    for (unsigned int i= 0; i < sizeof(Line4); i++)
    {
        cout << Line4[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+6);
    for (unsigned int i= 0; i < sizeof(Line5); i++)
    {
        cout << Line5[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+7);
    for (unsigned int i= 0; i < sizeof(Line6); i++)
    {
        cout << Line6[i];
        Sleep(Delay_us);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
}

/********************************************************************
*                   Función: Wait_Option                            *
* Argumentos de entrada:                                            *
*                                                                   *
* Argumentos de salida:                                             *
* - Valor entero relacionado con un menú de opciones. *             *
* Esta función espera hasta que el usuario ingrese una opción.      *
********************************************************************/
int Wait_Option (void)
{
    int Cursor_Pos = 14;

    system("cls");
    Show_Title ();

    gotoxy(30,10);
    cout << "Selecciona una opcio.";

    gotoxy(5,14);
    cout << "(1) NOU PRODUCTE.";

    gotoxy(5,16);
    cout << "(2) ELIMINAR PRODUCTE.";

    gotoxy(5,18);
    cout << "(3) COMPRAR PRODUCTE.";

    gotoxy(5,20);
    cout << "(4) VENDRE PRODUCTE.";

    gotoxy(5,22);
    cout << "(5) MOSTRAR REPORT.";

    gotoxy(5,24);
    cout << "(6) DESAR REPORT.";

    gotoxy(5,26);
    cout << "(7) CARREGAR REPORT.";

    gotoxy(5,28);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << "(8) SORTIR." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(17,30);
    cout << "Utilitza el teclat per seleccionar o prem ESC per SORTIR. " << endl;

    gotoxy(3,Cursor_Pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << (char)Cursor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(64,30);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos >= 16) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos <= 26) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 14: return 1; break;
                        case 16: return 2; break;
                        case 18: return 3; break;
                        case 20: return 4; break;
                        case 22: return 5; break;
                        case 24: return 6; break;
                        case 26: return 7; break;
                        case 28: return 8; break;
                    }
                }
                break;

                case KEY_ESC: return 8; break;

            }

            for (int i = 0; i<16 ; i+=2)
            {
                gotoxy(3,14+i);
                cout << (char) 0;
            }

            gotoxy(3,Cursor_Pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
            cout << (char)Cursor;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
            gotoxy(64,30);
        }
    }while (KEY_PAD!=27);

    return 8;
}

/********************************************************************
*                    Función: New_Product 							*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función agrega productos al inventario.                    	*
********************************************************************/
int New_Product (void)
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    float Cost = 0, Price = 0;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> NOU PRODUCTE <<" << endl;
    gotoxy(5,13);
    cout << "Nom Producte : " << endl;
    gotoxy(5,15);
    cout << "Cost Producte : " << endl;
    gotoxy(4,17);
    cout << "Preu Product : " << endl;
    gotoxy(6,19);
    cout << "<< DESAR >> " << endl;
    gotoxy(5,21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(25,25);
    cout << "Utilitza el teclat per seleccionar una opcio." << endl;

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 20) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            //cin.getline (Name,Max_Chars,'\n');

                            cin >> Name;
                            cin.clear();
                            cin.ignore(10, '\n');

                            for (int i=0; i<Max_Chars ; i++)
                            {
                                Name[i] = toupper(Name[i]);
                                if (Name[i] == 0) break;
                            }
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";
                        break;

                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Cost;
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";
                        break;

                        case 17:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Price;
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";
                        ; break;

                        case 19:
                            if (Cost == 0 || Price == 0 || Name[0] == 0)
                            {
                                Show_Error ((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS!'.  ", 1500);
                            }
                            else
                            {
                                Pointer_Articles[Counter_Articles] = new Article_Struct;
                                Init_Structure_Elements(Counter_Articles);
                                int Local_Articles = Get_Elements_Number();

                                for (int i=0; i<Max_Chars ; i++)
                                {
                                    Pointer_Articles[Local_Articles]->Name[i] = Name[i];
                                    if (Name[i] == 0) break;
                                }
                                Pointer_Articles[Local_Articles]->Cost = Cost;
                                Pointer_Articles[Local_Articles]->Price = Price;
                                Pointer_Articles[Local_Articles]->Pieces = 0;
                                Pointer_Articles[Local_Articles]->Value *= Cost;

                                if (Counter_Articles == Local_Articles) Counter_Articles++;

                                return 0;
                            }
                        break;

                        case 21: return 0 ; break;

                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);

      return 0;
}

/********************************************************************
*                   Función: Delete_Product 						*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función elimina productos al inventario.              		*
********************************************************************/
int Delete_Product (void)
{
    int Cursor_Pos = 16;
    int Delete_Register = 0;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> ELIMINAR PRODUCTE <<" << endl;
    gotoxy(1,11);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,12);
    cout << "|No.|";
    cout << "      NOM     |";
    cout << "     COMPRAR     |";
    cout << "     VENDRE    |";
    cout << "  DISPONIBLES  |";
    cout << "     PREU    |";
    gotoxy(1,13);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(57,9);
    cout << "ELIMINAR Reg. No:" ;

    for (int j = 0 ; j < Counter_Articles ; j++)
    {
        gotoxy(3,14+j);
        cout << j+1;
        gotoxy(10,14+j);
        for (int i = 0 ; i<Max_Chars ; i++)
        {
            cout << Pointer_Articles[j]->Name[i];
            if (Pointer_Articles[j]->Name[i] == 0)
            {
                break;
            }
        }
        cout.precision(2);
        gotoxy(26,14+j);
        cout << fixed << Pointer_Articles[j]->Cost;
        gotoxy(40,14+j);
        cout << fixed << Pointer_Articles[j]->Price;
        gotoxy(55,14+j);
        cout << fixed << Pointer_Articles[j]->Pieces;
        gotoxy(70,14+j);
        cout << fixed << Pointer_Articles[j]->Value;
    }

    gotoxy(Cursor_Pos,9);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_LEFT:
                {
                    if (Cursor_Pos == 74) Cursor_Pos = Cursor_Pos = 16;

                }
                break;

                case KEY_RIGHT:
                {
                    if (Cursor_Pos == 16) Cursor_Pos = Cursor_Pos = 74;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 74:
                            gotoxy(Cursor_Pos-1,9);
                            cout << (char)Cursor;
                            cin >> Delete_Register;
                            if (Delete_Register>Counter_Articles)
                            {
                                Show_Error ((char *) "ERROR: EL Nº DE REGISTRE NO ES VALID.", 1500);
                                Cursor_Pos = 16;
                            }
                            else
                            {
                                for (int i=0; i<Max_Chars ; i++)
                                {
                                    Pointer_Articles[Delete_Register-1]->Name[i] = 0;
                                }
                                Pointer_Articles[Delete_Register-1]->Cost = 0;
                                Pointer_Articles[Delete_Register-1]->Price = 0;
                                Pointer_Articles[Delete_Register-1]->Pieces = 0;
                                Pointer_Articles[Delete_Register-1]->Value = 0;
                                //delete[] Pointer_Articles[Delete_Register-1];
                                gotoxy(19,9);
                                cout << "FET.";
                                Cursor_Pos = 16;
                            }
                        break;

                        case 16: return 0; break;
                    }
                }
            }
            gotoxy(Cursor_Pos,9);
        }
      }while (KEY_PAD!=27);

      return 0;
}


/********************************************************************
*                    Función: Buy_Product 							*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función gestiona las compras de inventario.                  *
********************************************************************/
int Buy_Product (void)
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    int Quantity_Prod;
    bool Found_Article = false;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> COMPRAR PRODUCTE <<";
    gotoxy(5,13);
    cout << "Nom Producte :";
    gotoxy(4,15);
    cout << "Quantitat Producte :";
    gotoxy(7,17);
    cout << "<< DESAR >> ";
    gotoxy(5,19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            //cin.getline (Name,Max_Chars,'\n');

                            cin >> Name;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "FET";
                        break;

                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Quantity_Prod;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "FET";
                        break;

                        case 17:
                            if (Quantity_Prod == 0 || Name[0] == 0)
                            {
                                Show_Error((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS'.", 1500);
                            }
                            else
                            {
                                int j;
                                int i;
                                for (j = 0 ; j < Counter_Articles ; j++)
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)
                                    {
                                        if (Pointer_Articles[j]->Name[i] != toupper(Name[i]) || Pointer_Articles[j]->Name[i] == 0)
                                        {
                                            break;
                                        }
                                    }

                                    if (i == strlen(Name))
                                    {
                                        Found_Article = true;
                                        break;
                                    }
                                }

                                if (Found_Article)
                                {
                                    Pointer_Articles[j]->Pieces += Quantity_Prod;
                                    Pointer_Articles[j]->Value = Pointer_Articles[j]->Cost * Pointer_Articles[j]->Pieces;
                                    return 0;
                                }
                                else
                                {
                                    Show_Error((char *) "ERROR: ARTICLE NO TROBAT A L'INVENTARI'", 1500);
                                }
                            }
                        break;

                        case 19: return 0; break;
                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}

/********************************************************************
*                    Función: Sale_Product 							*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función gestiona las ventas de inventario.                   *
********************************************************************/
int Sell_Product (void)
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    int Quantity_Prod;
    bool Found_Article = false;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> VENDRE PRODUCTE <<" << endl;
    gotoxy(5,13);
    cout << "Nom Producte :" << endl;
    gotoxy(4,15);
    cout << "Quantitat Prod :" << endl;
    gotoxy(5,17);
    cout << "<< DESAR >> ";
    gotoxy(5,19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;

                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            //cin.getline (Name,Max_Chars,'\n');

                            cin >> Name;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";
                        break;

                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Quantity_Prod;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";
                        break;

                        case 17:
                            if (Quantity_Prod == 0 || Name[0] == 0)
                            {
                                Show_Error((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS'.",1500);
                            }
                            else
                            {
                                int j;
                                int i;
                                for (j = 0 ; j < Counter_Articles ; j++)
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)
                                    {
                                        if (Pointer_Articles[j]->Name[i] != toupper(Name[i]) || Pointer_Articles[j]->Name[i] == 0)
                                        {
                                            break;
                                        }
                                    }

                                    if (i == strlen(Name))
                                    {
                                        Found_Article = true;
                                        break;
                                    }
                                }

                                if (Found_Article)
                                {
                                    if (Quantity_Prod <= Pointer_Articles[j]->Pieces)
                                    {
                                        Pointer_Articles[j]->Pieces -= Quantity_Prod;
                                        Pointer_Articles[j]->Value = Pointer_Articles[j]->Cost * Pointer_Articles[j]->Pieces;
                                        return 0;
                                    }
                                    else
                                    {
                                        Show_Error((char *) "ERROR: LA QUANITTAT D'ARTICLES ES MASSA ALTA'.",1500);
                                    }
                                }
                                else
                                {
                                    Show_Error((char *) "ERROR: ARTICLE NO TROBAT A L'INVENTARI'.",1500);
                                }
                            }
                        break;

                        case 19: return 0; break;
                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}

/********************************************************************
*                    Función: Report_Product 						*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función muestra los productos de informes.                   *
********************************************************************/
int Report_Product (void)
{
    float Total = 0;

    system("cls");
    Show_Title ();
    gotoxy(27,9);
    cout << ">> REPORT PRODUCTES <<" << endl;
    gotoxy(1,11);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,12);
    cout << "|No.|";
    cout << "      NOM     |";
    cout << "     COMPRAR     |";
    cout << "     VENDRE    |";
    cout << "  DISPONIBLES  |";
    cout << "     PREU    |";
    gotoxy(1,13);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    int j;
    int i;

    for (j = 0 ; j < Counter_Articles ; j++)
    {
        gotoxy(3,14+j);
        cout << j+1;
        gotoxy(10,14+j);
        for (i = 0 ; i<Max_Chars ; i++)
        {
            cout << Pointer_Articles[j]->Name[i];
            if (Pointer_Articles[j]->Name[i] == 0)
            {
                break;
            }
        }
        cout << setprecision(2);
        gotoxy(26,14+j);
        cout << fixed << Pointer_Articles[j]->Cost;
        gotoxy(40,14+j);
        cout << fixed << Pointer_Articles[j]->Price;
        gotoxy(55,14+j);
        cout << fixed << Pointer_Articles[j]->Pieces;
        gotoxy(70,14+j);
        cout << fixed << Pointer_Articles[j]->Value;
    }

    gotoxy(1, 15+j);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(57, 16+j);
    cout << "TOTAL : ";
    gotoxy(70, 16+j);

    for (int k = 0; k < Counter_Articles ; k++)
    {
        Total +=  Pointer_Articles[k]->Value;
    }
    cout << Total;

    gotoxy(46, 17+j);
    cout << "ULTIM REPORT : ";
    gotoxy(70, 17+j);
    cout << Total - Total_Inventary;

    gotoxy(16,9);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_ENTER:
                {
                    return 0;
                }
            }
            //gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}


/********************************************************************
*                 Función: Get_Elements_Number 						*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Número entero de elementos dentro de la array. * 				*
* Esta función devuelve el número de elementos de la estructura.    *
********************************************************************/
int Get_Elements_Number (void)
{
    int Elements_Number = 0;

    for (int i = 0; i < 100 ; i++)
    {
        if (Pointer_Articles[i]->Name[i] == 0) break;
        Elements_Number++;
    }
    return Elements_Number;
}


/********************************************************************
*                Función: Init_Structure_Elements 					*
* Argumentos de entrada: 											*
* - Elemento de número de array entera. * 							*
* Argumentos de salida: 											*
* 																	*
* Esta función inicializa la estructura base.                      	*
********************************************************************/
void Init_Structure_Elements (int Article)
{
    for (int i = 0 ; i<Max_Chars ; i++)
    {
        Pointer_Articles[Article]->Name[i] = NULL;
    }
    Pointer_Articles[Article]->Pieces = 0;
    Pointer_Articles[Article]->Cost = 0;
    Pointer_Articles[Article]->Price = 0;
    Pointer_Articles[Article]->Value = 0;
}


/********************************************************************
*                       Función: Save_File 							*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función guarda los datos de inventario en un archivo.        *
********************************************************************/
int Save_File (void)
{
    int Cursor_Pos = 13;
    float Total = 0;

    system("cls");
    Show_Title ();
    gotoxy(27,9);
    cout << ">> DESAR REPORT <<" << endl;
    gotoxy(6,13);
    cout << "Nom fitxer :   " << File_Name <<endl;
    gotoxy(7,15);
    cout << "<< DESAR >>" << endl;
    gotoxy(4,17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(20,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 17) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(18,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(18,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            //cin.getline (Name,Max_Chars,'\n');

                            cin >> File_Name;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";

                            for (int i = 0 ; i<Max_Chars ; i++)
                            {
                                File_Name[i] = toupper(File_Name[i]);
                                if (File_Name[i] == 0) break;
                            }
                        break;

                        case 15:
                            if (File_Name[0] == 0)
                            {
                                Show_Error ((char *) "ERROR: ENTRAR UN NOM PRIMER.", 1500);
                            }
                            else
                            {
                                ofstream file (File_Name);
                                if (file.is_open())
                                {
                                    file << "                            >> REPORT PRODUCTES <<                               " << endl;
                                    file << " ------------------------------------------------------------------------------ " << endl;
                                    file << "|\tNo.\t|\tNOM\t|\tCOMPRAR\t|\tVENDRE\t|\tDISPONIBLES\t|\tPREU\t|" << endl;
                                    file << " ------------------------------------------------------------------------------ " << endl;
                                    file << endl;

                                    int j;
                                    int i;

                                    for (j = 0 ; j < Counter_Articles ; j++)
                                    {
                                        file << "#\t" << j+1 << "\t\t";
                                        for (i = 0 ; i<Max_Chars ; i++)
                                        {
                                            file << Pointer_Articles[j]->Name[i];
                                            if (Pointer_Articles[j]->Name[i] == 0)
                                            {
                                                break;
                                            }
                                        }
                                        file << setprecision(2);
                                        file << "\t\t" << fixed << Pointer_Articles[j]->Cost;
                                        file << "\t\t" << fixed << Pointer_Articles[j]->Price;
                                        file << "\t\t" << fixed << Pointer_Articles[j]->Pieces;
                                        file << "\t\t" << fixed << Pointer_Articles[j]->Value << endl;
                                    }

                                    file << endl;
                                    file <<"------------------------------------------------------------------------------" << endl;
                                    file << "\t\t\t\t\t\t\t\t\t\tTOTAL € ";

                                    for (int k = 0; k < Counter_Articles ; k++)
                                    {
                                        Total +=  Pointer_Articles[k]->Value;
                                    }
                                    file << Total;

                                    file.close();
                                    gotoxy(25,25);
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
                                    cout << "FITXER CREAT CORRECTAMENT.";
                                    Sleep (1500);
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                    return 0;
                                }
                                else
                                {
                                    Show_Error ((char *) "ERROR: EL FITXER NO HA SIGUT CREAT.", 1500);
                                    return 0;
                                }
                            }
                        break;

                        case 17:
                            return 0;
                        break;
                    }
                }
            }
            gotoxy(20,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
      return 0;
}

/********************************************************************
*                       Función: Load_File 							*
* Argumentos de entrada: 											*
* 																	*
* Argumentos de salida: 											*
* - Valor entero solo para indicar que la función ha terminado. * 	*
* Esta función carga los datos de inventario de un archivo.         *
********************************************************************/
int Load_File (void)
{
    int Cursor_Pos = 13;
    char String_Row[50];

    char Name[Max_Chars];
    float Cost = 0, Price = 0;
    int Pieces;
    float Value;

    system("cls");
    Show_Title ();
    gotoxy(27,9);
    cout << ">> CARREGAR REPORT <<" << endl;
    gotoxy(6,13);
    cout << "Nom Fitxer : " << endl;
    gotoxy(7,15);
    cout << "<< CARREGAR >>" << endl;
    gotoxy(4,17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(20,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 17) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(18,Cursor_Pos);
                            cout << (char)Cursor << "                    ";
                            gotoxy(18,Cursor_Pos);
                            cout << (char)Cursor << " ";

                            cin >> File_Name;
                            cin.clear();
                            cin.ignore(10, '\n');
                            gotoxy(35,Cursor_Pos);
                            cout << "Fet";

                            for (int i = 0 ; i<Max_Chars ; i++)
                            {
                                File_Name[i] = toupper(File_Name[i]);
                                if (File_Name[i] == 0) break;
                            }
                        break;

                        case 15:
                            if (File_Name[0] == 0)
                            {
                                Show_Error ((char *) "ERROR: ENTRAR UN NOM PRIMER.", 1500);
                            }
                            else
                            {
                                ifstream file (File_Name);
                                if (file.is_open())
                                {
                                    while(!file.eof())
                                    {
                                        file >> String_Row;

                                        if (String_Row[0] == '#')
                                        {
                                            file >> String_Row;
                                            file >> Name;
                                            file >> Cost;
                                            file >> Price;
                                            file >> Pieces;
                                            file >> Value;

                                            if (Name[0] != 0)
                                            {
                                                Pointer_Articles[Counter_Articles] = new Article_Struct;
                                                Init_Structure_Elements(Counter_Articles);

                                                for (int i = 0 ; i<Max_Chars ; i++)
                                                {
                                                    Pointer_Articles[Counter_Articles]->Name[i] = Name[i];
                                                    if (Name[i] == 0)
                                                    {
                                                        break;
                                                    }
                                                }
                                                Pointer_Articles[Counter_Articles]->Cost = Cost;
                                                Pointer_Articles[Counter_Articles]->Price = Price;
                                                Pointer_Articles[Counter_Articles]->Value = Value;
                                                Pointer_Articles[Counter_Articles]->Pieces = Pieces;

                                                Counter_Articles++;
                                            }
                                        }
                                        if (String_Row[0] == '$') file >> Total_Inventary;
                                    }

                                    if (Counter_Articles == 0)
                                    {
                                        Show_Error ((char *) "EL FITXER NO CONTE INFORMACIO A CARREGAR.", 1500);
                                        file.close();
                                        return 0;
                                    }
                                    else
                                    {
                                        gotoxy(25,25);
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
                                        cout << "FITXER CARREGAT CORRECTAMENT.";
                                        Sleep (1500);
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                        file.close();
                                        return 0;
                                    }

                                }
                                else
                                {
                                    Show_Error ((char *) "ERROR: EL FITXER NO S'HA OBERT'.", 1500);
                                    return 0;
                                }
                            }
                        break;

                        case 17:
                            return 0;
                        break;
                    }
                }
            }
            gotoxy(20,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
      return 0;
}

/********************************************************************
*                     Función: Show_Error   						*
* Argumentos de entrada: 											*
* - Puntero a cadena, tiempo de retardo de Integet. * 				*
* Argumentos de salida: 											*
* 																	*
* Esta función muestra un error en Screem.                          *
********************************************************************/
void Show_Error (char *Pointer_String, int Show_Delay_us)
{
    int Strin_Leng = strlen (Pointer_String);
    gotoxy(23,25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
    for (int i = 0; i <= Strin_Leng ; i++)
    {
        cout << *(Pointer_String+i);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    Sleep(Show_Delay_us);
    gotoxy(23,25);
    for (int i = 0; i <= Strin_Leng ; i++)
    {
        cout << ' ';
    }
}
