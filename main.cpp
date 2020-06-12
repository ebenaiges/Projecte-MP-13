/********************************************************************
*                         SISTEMA INVENTARI                       	*
*                           Version 1.0                             *
*      			   	ERNEST BENAIGES I GALLEGO         				*
********************************************************************/

// ********* CARGA DE LAS LIBRERIAS NECESARIAS **************
#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <fstream>
// ***********************************************************

#define Color_Red 12		// 12 = Rojo
#define Color_Def 15		// 15 = Blanco
#define Color_Yellow 14		// 14 = Amarillo
#define Color_Green 10		// 10 = Verde
#define Delay_us 0			// Delay_us = 0
#define Cursor 16			// Cursor= 16  --- Es el símbolo que aparece en la izquierda del menu, para saber que opcion está seleccionada
#define KEY_UP 72			// 72 = Cod Ascii tecla flecha arriba
#define KEY_DOWN 80			// 80 = Cod Ascii tecla flecha abajo
#define KEY_LEFT 75			// 75 = Cod Ascii tecla flecha izquierda
#define KEY_RIGHT 77		// 77 = Cod Ascii tecla flecha derecha
#define KEY_ENTER 13		// 13 = Cod Ascii tecla ENTER
#define KEY_ESC 27			// 27 = Cod Ascii tecla ESC
#define Max_Chars 12		// Max_Chars = 12

using namespace std;		// Declaración de un espacio de nombres

COORD coord = {0,0};		// declaración de coord como un objeto de la clase COORD (coordenadas) y se le asigna el valor 0,0
char KEY_PAD;				// declaración de variable llamada KEY_PAD como tipo char

struct Article_Struct		// declaración de Article_Struct como una estructura consitituida por :
{
    char Name[Max_Chars];	// Nombre del producto (maximo 12 caracteres)
    float PVenta;			// precio de venta del producto
    float PCompra;			// precio de compra del producto
    int PiecesV;			// Numero de piezas vendidas
    int PiecesC;			// Numero de piezas compradas
    float Gastado;			// Dinero gastado
    float Ingresado;		// Dinero ingresado
};

struct Article_Struct *Pointer_Articles[100];	// declaración de un puntero llamado Pointer_Articles de 100 elementos del tipo estructura Article_Struct

//******************* Declaraciones de funciones usadas ********************************
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
//***************************************************************************************


int Counter_Articles = 0;		// Declaracion variable Counter_Articles de tipo int
char File_Name [Max_Chars];		// Declaracion variable File_Name de tipo char (12 caracteres maximos)
float Total_Inventary = 0;		// Declaracion variable Total_Inventary de tipo float y se le asigna el valor 0 al comienzo

int main()		// Función principal
{
	int devuelto;
	
    for (int i = 0; i<Max_Chars ; i++)
    {
        File_Name[i] = 0;				// File_Name[0] hasta File_Name[11] = 0
    }

    for(;;)		// Bucle infinito
    {
        switch (Wait_Option ())		// Comprobamos lo que devuelve la funcion Wait_Option
        {
            case 1:					// Si es 1 ---> ejecutamos la funcion New_Product()
                New_Product ();
            	break;

            case 2:					// Si es 2 ---> ejecutamos la funcion Delete_Product()
                Delete_Product ();
            	break;

            case 3:					// Si es 3 ---> ejecutamos la funcion Buy_Product()
                Buy_Product ();
            	break;

            case 4:					// Si es 4 ---> ejecutamos la funcion Sell_Product()
                Sell_Product ();
            	break;

            case 5:					// Si es 5 ---> ejecutamos la funcion Report_Product()
                devuelto=Report_Product ();
            	break;

            case 6:					// Si es 6 ---> ejecutamos la funcion Save_File()
                Save_File ();
            	break;

            case 7:					// Si es 7 ---> ejecutamos la funcion Load_File()
                Load_File ();
            	break;

            case 8:					// Si es 8 ---> salimos de la función main() devolviendo el valor EXIT_SUCCESS
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
    coord.X=x;		// el valor x se copia en coord.X
    coord.Y=y;		// el valor y se copia en coord.Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); // Se mueve el cursor a la posición x,y
}

/********************************************************************
*                     Función: Select_Option                        *
* Esta función solo presenta el programa al usuario.                *
********************************************************************/
void Show_Title (void)
{
    int X = 0;		// Declaracion de variable X como un entero asignandole el valor 0
    int Y = 0;		// Declaracion de variable Y como un entero asignandole el valor 0

    system("cls");	// Se bora la pantalla

	// ******* Definición de variables de tipo char que se llaman LineX[] y se le asigna un valor a cada variables *********
	char Line1[] = {"  ----------------------------------------------------------------------------   "};
    char Line2[] = {" |                         SISTEMA INVENTARI V.1                              |  "};
    char Line3[] = {" |                                                                            |  "};
    char Line4[] = {" |                         PROJECTE   DAS2   M13                              |  "};
    char Line5[] = {" |                       ERNEST BENAIGES I GALLEGO                            |  "};
    char Line6[] = {"  ----------------------------------------------------------------------------   "};
	// **********************************************************************************************************************

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Se asigna el color verde al texto
    gotoxy (X,Y+2);		// Se mueve el cursor a la posición X, Y+2 --->  como X=0  Y=0  --->  posición (0, 2)
    for (unsigned int i= 0; i < sizeof(Line1); i++)	// bucle for desde i=0 mientras i<tamaño de Line1   i++
    {
        cout << Line1[i];		// va mostrando en pantalla los caracteres de Line1 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    gotoxy (X,Y+3);		// Se mueve el cursor a la posición X, Y+3 --->  como X=0  Y=0  --->  posición (0, 3)
    for (unsigned int i= 0; i < sizeof(Line2); i++)	// bucle for desde i=0 mientras i<tamaño de Line2   i++
    {
        cout << Line2[i];		// va mostrando en pantalla los caracteres de Line2 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    gotoxy (X,Y+4);
    for (unsigned int i= 0; i < sizeof(Line3); i++)	// bucle for desde i=0 mientras i<tamaño de Line3   i++
    {
        cout << Line3[i];		// va mostrando en pantalla los caracteres de Line3 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    gotoxy (X,Y+5);
    for (unsigned int i= 0; i < sizeof(Line4); i++)	// bucle for desde i=0 mientras i<tamaño de Line4   i++
    {
        cout << Line4[i];		// va mostrando en pantalla los caracteres de Line4 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    gotoxy (X,Y+6);
    for (unsigned int i= 0; i < sizeof(Line5); i++)	// bucle for desde i=0 mientras i<tamaño de Line5   i++
    {
        cout << Line5[i];		// va mostrando en pantalla los caracteres de Line5 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    gotoxy (X,Y+7);
    for (unsigned int i= 0; i < sizeof(Line6); i++)	// bucle for desde i=0 mientras i<tamaño de Line6   i++
    {
        cout << Line6[i];		// va mostrando en pantalla los caracteres de Line6 desde 0 hasta el final con una espera configurable
        Sleep(Delay_us);		// espera en microsegundos del valor que tenga Delay_us...en este caso Delay_us=0
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def); // Se asigna el color blanco al texto
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
    int Cursor_Pos = 14;	// Declara variable Cursor_Pos como un entero y le asigna el valor 14
    int devolver=0;			// Variable para controlar el bucle do-while

    system("cls");			// Borrar la pantalla
    Show_Title ();			// Ejecuta la funcion Show_Title

    gotoxy(30,10); cout << "Selecciona una opcio.";		// Muestra el texto en la posicion x=30  y=10
    gotoxy(5,14);  cout << "(1) NOU PRODUCTE.";			// Muestra el texto en la posicion x=5  y=14
    gotoxy(5,16);  cout << "(2) ELIMINAR PRODUCTE.";	// Muestra el texto en la posicion x=5  y=16
    gotoxy(5,18);  cout << "(3) COMPRAR PRODUCTE.";		// Muestra el texto en la posicion x=5  y=18
    gotoxy(5,20);  cout << "(4) VENDRE PRODUCTE.";		// Muestra el texto en la posicion x=5  y=20
    gotoxy(5,22);  cout << "(5) MOSTRAR REPORT.";		// Muestra el texto en la posicion x=5  y=22
    gotoxy(5,24);  cout << "(6) DESAR REPORT.";			// Muestra el texto en la posicion x=5  y=24
    gotoxy(5,26);  cout << "(7) CARREGAR REPORT.";		// Muestra el texto en la posicion x=5  y=26
    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green); 	// Se asigna el color verde al texto
    gotoxy(5,28); cout << "(8) SORTIR." << endl;							// Muestra el texto en la posicion x=5  y=28
    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def); // Se asigna el color blanco al texto
    gotoxy(17,30); cout << "Utilitza el teclat per seleccionar o prem ESC per SORTIR. " << endl; // Muestra el texto en la posicion x=17  y=30

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green); // Se asigna el color verde al texto
    gotoxy(3,Cursor_Pos); cout << (char)Cursor;	// Muestra el caracter <<Cursor=16>>texto en la posicion x=3  y=Cursor_Pos (Es el simbolo que aparece a la izq. del menu
    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Se asigna el color blanco al texto
    gotoxy(75,30);	// Situa el cursor en la posición x=64 y=30

    do{					// Se repite mientras la tecla pulsada no sea ESC		
        if (kbhit())	// Si se pulsa cualquier tecla se cumple la condición
        {
            KEY_PAD = getch();	// lee la tecla que hemos pulsado

            switch (KEY_PAD)	// Comprueba KEY_PAD, para determinar la tecla que hemos pulsado
    		{
                case KEY_UP:	// Si hemos pulsado la tecla de flecha arriba, movemos la marca hacia arriba (14 como mínimo)
                    if (Cursor_Pos >= 16) Cursor_Pos = Cursor_Pos - 2;	//Decrementamos Cursor_Pos en 2 si Cursor_Pos >=16
                	break;

                case KEY_DOWN: // Si hemos pulsado la tecla de flecha abajo, movemos la marca hacia abajo (28 como maximo)
                    if (Cursor_Pos <= 26) Cursor_Pos = Cursor_Pos + 2; //Incrementamos Cursor_Pos en 2 si Cursor_Pos <=26
                	break;

                case KEY_ENTER: // Si hemos pulsado la tecla ENTER
                    switch (Cursor_Pos)  // Comprobamos que opción tenemos seleccionada es decir que valor tiene Cursor_Pos
                    {
                        case 14: devolver=1; break; // Si Cursor_Pos=14 --> Tenemos la marca en la Opcion 1, salimos de la función retornando el valor 1
                        case 16: devolver=2; break; // Si Cursor_Pos=16 --> Tenemos la marca en la Opcion 2, salimos de la función retornando el valor 2
                        case 18: devolver=3; break; // Si Cursor_Pos=18 --> Tenemos la marca en la Opcion 3, salimos de la función retornando el valor 3
                        case 20: devolver=4; break; // Si Cursor_Pos=20 --> Tenemos la marca en la Opcion 4, salimos de la función retornando el valor 4
                        case 22: devolver=5; break; // Si Cursor_Pos=22 --> Tenemos la marca en la Opcion 5, salimos de la función retornando el valor 5
                        case 24: devolver=6; break; // Si Cursor_Pos=24 --> Tenemos la marca en la Opcion 6, salimos de la función retornando el valor 6
                        case 26: devolver=7; break; // Si Cursor_Pos=26 --> Tenemos la marca en la Opcion 7, salimos de la función retornando el valor 7
                        case 28: devolver=8; break; // Si Cursor_Pos=28 --> Tenemos la marca en la Opcion 8, salimos de la función retornando el valor 8
                	}
                	break;

                case KEY_ESC: devolver=8; break; // Si hemos pulsado la tecla ESC, salimos de la función retornando el valor 8
            }

            for (int i = 0; i<16 ; i+=2)
            {
                gotoxy(3,14+i); cout << (char) 0;	// Borra el caracter de la posición donde se encuentra el cursor
            }

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Se asigna el color verde al texto
            gotoxy(3,Cursor_Pos); cout << (char)Cursor;	// Pone el símbolo del cod Ascii de <<Cursor=16>>
            
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Se asigna el color blanco al texto
            gotoxy(75,30); // Situa el cursor en la posición x=64 y=30
        }
    }while (devolver==0);	// Se repite mientras devolver=0
    return devolver; // Termina la función y devuelve el valor de la variable devolver
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
    int Cursor_Pos = 13;	// Declara la variable Cursor_Pos como un entero y le asigna el valor 13
    char Name[Max_Chars];	// Declara la variable Name del tipo char y le asigna como máximo <<Max_Chars>> caracteres
    float Cost = 0, Price = 0; // Declara 2 variables de tipo float (Cost y Price) y las asigna con 0

    system("cls");	// Borra la pantalla
    Show_Title ();	// Ejecuta la función, mostrando el Titulo
    
    gotoxy(29,9); cout << ">> NOU PRODUCTE <<" << endl;	// Muestra el texto por pantalla
    gotoxy(5,13); cout << "Nom producte : " << endl;	// Muestra el texto por pantalla
    gotoxy(5,15); cout << "Preu  compra : " << endl;	// Muestra el texto por pantalla
    gotoxy(5,17); cout << "Preu  venda  : " << endl;	// Muestra el texto por pantalla
    gotoxy(5,19); cout << "            << DESAR >> " << endl;	// Muestra el texto por pantalla
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);
    gotoxy(5,21); cout << "      << TORNA MENU PRINCIPAL" << endl;	// Muestra el texto por pantalla
    
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(18,25); cout << "Utilitza el teclat per seleccionar una opcio." << endl;	// Muestra el texto por pantalla

    gotoxy(22,Cursor_Pos);	// Posiciona el cursor en la posición x=22, y=donde indique la variable Cursor_Pos

	// Se repite mientras la tecla que pulsemos no sea ESC=cod. ascii 27
    do{
        if (kbhit())	// Comprueba que haya sido pulsada alguna tecla
        {
            KEY_PAD = getch();	// Lee el cod.Ascii de la tecla pulsada y lo gurarda en KEY_PAD

            switch (KEY_PAD)	// Comprueba la tecla que ha sido pulsada
            {
                case KEY_UP:	// Si hemos pulsado la tecla flecha arriba
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;	// Decrementa en 2 Cursor_Pos si es mayor de 13
                	break;

                case KEY_DOWN:	// Si hemos pulsado la tecla flecha abajo
                    if (Cursor_Pos < 20) Cursor_Pos = Cursor_Pos + 2; 	// Incrementa en 2 Cursor_Pos si es menor de 20
                	break;

                case KEY_ENTER:	// Si hemos pulsado la tecla ENTER
                    switch (Cursor_Pos)	// Comprobamos la variable Cursor_pos
                    {
                        case 13:	// Si Cursor_pos=13
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << "                    "; // Mostramos el cursor en la posicion y borramos los 20 caracteres siguientes
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << " "; // Borramos el caracter d ela posición donde está el cursor

                            cin >> Name;	// El usuario introduce el nombre del producto
                            cin.clear();	// Borramos el flag de cin, para evitar errores en futuras instrucciones de E/S
                            cin.ignore(10, '\n');	// Truncamos 10 caracteres o hasta el caracter de fin de linea \n

                            for (int i=0; i<Max_Chars ; i++)	// Bucle for desde i=0 minetras i<Max_Chars (12), incrementando en 1 la variable i
                            {
                                Name[i] = toupper(Name[i]);	// Pasa a Mayusculas todos los caracteres de Name
                                if (Name[i] == 0) break;	// Termina (break) cunado el caracter de Name=0
                            }
                            gotoxy(35,Cursor_Pos); cout << "Fet";	// Mostramos en pantalla el texto
                        	break;

                        case 15:
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << "                    "; // Mostramos el cursor en la posicion y borramos los 20 caracteres siguientes
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << " "; // Mostramos el cursor en la posicion y borramos el caracter siguiente
                            
							cin >> Cost;	// El usuario introduce el coste del producto
                            gotoxy(35,Cursor_Pos); cout << "Fet";	// Mostramos en pantalla el texto
                        	break;

                        case 17:
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << "                    "; // Mostramos el cursor en la posicion y borramos los 20 caracteres siguientes
                            gotoxy(20,Cursor_Pos); cout << (char)Cursor << " "; // Mostramos el cursor en la posicion y borramos el caracter siguiente
                            cin >> Price;	// El usuario introduce el precio de venta del  producto
                            gotoxy(35,Cursor_Pos); cout << "Fet";	// Mostramos en pantalla el texto
                        	break;

                        case 19:
                            if (Cost == 0 || Price == 0 || Name[0] == 0)	// Si Cost=0 o Price=0 o Nombre=0 --> Hay algun campo vacio. ERROR
                            {
                                Show_Error ((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS!'.  ", 1500);	// Mostramos una ventana con un texto de error
                            }
                            else	// Si no hubo ningun error, es decir los 3 campos estan rellenos con datos
                            {
                                Pointer_Articles[Counter_Articles] = new Article_Struct;	// Crea un nuevo objeto Article_Struct
                                Init_Structure_Elements(Counter_Articles);
                                int Local_Articles = Get_Elements_Number();

                                for (int i=0; i<Max_Chars ; i++)
                                {
                                    Pointer_Articles[Local_Articles]->Name[i] = Name[i]; // Busca un hueco que haya libre Name[i]=0
                                    if (Name[i] == 0) break;
                                }
                                Pointer_Articles[Local_Articles]->PCompra = Cost; 	// Rellena el campo Precio de compra con la variable Cost
                                Pointer_Articles[Local_Articles]->PVenta = Price; 	// Rellena el campo Precio de venta con la variable Price
                                Pointer_Articles[Local_Articles]->PiecesC = 0;	  	// Los demás campos los inicia a 0
                                Pointer_Articles[Local_Articles]->PiecesV = 0;	  	// Los demás campos los inicia a 0
                                Pointer_Articles[Local_Articles]->Gastado = 0;		// Los demás campos los inicia a 0
                                Pointer_Articles[Local_Articles]->Ingresado= 0;		// Los demás campos los inicia a 0

                                if (Counter_Articles == Local_Articles) Counter_Articles++;	// Actualiza el contador de productos

                                return 0;
                            }
                        	break;
                        case 21: return 0 ; break;
                    }
            }
            gotoxy(22,Cursor_Pos);
        }
    } while (KEY_PAD!=27);	// Si es una tecla distinto al ESC (Ascci 27) vuelve a ejecutar el bucle

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
    int Cursor_Pos = 13;
    int Delete_Register = 0;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> ELIMINAR PRODUCTE <<" << endl;
    gotoxy(1,11); cout << "----------------------------------------------------------------------------------------------------";
	gotoxy(1,12); cout << "|No.|     NOM       |   PREU DE COMPRA    |    PREU DE VENDA    |     STOCK     | CAPITAL INVERTIT |";
    gotoxy(1,13); cout << "----------------------------------------------------------------------------------------------------";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Color Texto = verde
	gotoxy(1,9);  cout << " << TORNA MENU PRINCIPAL";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Color Texto = Blanco
    gotoxy(57,9); cout << "ELIMINAR Reg.No:" ;

    for (int j = 0 ; j < Counter_Articles ; j++)	// Bucle para recorrer todos los productos
    {
        gotoxy(2,14+j); cout << j+1;									// Muestra el numero del producto
        gotoxy(8,14+j);
        for (int i = 0 ; i<Max_Chars ; i++)
        {
            cout << Pointer_Articles[j]->Name[i];						// Muestra el nombre del producto
            if (Pointer_Articles[j]->Name[i] == 0) { break; }			// Si el campo Name esta vacio, termina
        }
        cout.precision(2);	// trabajamos con 2 decimales
        gotoxy(28,14+j); cout << fixed << Pointer_Articles[j]->PCompra;		// Muestra el Precio de compra
        gotoxy(50,14+j); cout << fixed << Pointer_Articles[j]->PVenta;		// Muestra el Precio de venta
        gotoxy(72,14+j); cout << fixed << Pointer_Articles[j]->PiecesC;		// Muestra el stock
        gotoxy(89,14+j); cout << fixed << Pointer_Articles[j]->Gastado;		// Muestra el capital invertido
    }

    gotoxy(Cursor_Pos,9);

    do
	{
        if (kbhit())	// Comprobamossi hay alguna tecla pulsada
    	{
            KEY_PAD = getch();	// leemos el cod.ascii de la tecla que se ha pulsado
            switch (KEY_PAD)	// Comprobamos la tecla pulsada
            {
                case KEY_LEFT:		// Si se pulsa la tecla de la flecha izquierda
                    if (Cursor_Pos == 76) Cursor_Pos = Cursor_Pos = 13;	// Se situa el cursor en la Pos=13 (Volver al menu principal)
                	break;

                case KEY_RIGHT:		// Si se pulsa la tecla de la flecha derecha
                    if (Cursor_Pos == 13) Cursor_Pos = Cursor_Pos = 76;	// Se situa el cursor en la POs=76 ( Eliminar Reg Nº )
                	break;

                case KEY_ENTER:		// Si se pulsa la tecla ENTER
                    switch (Cursor_Pos)	// Comprobamos donde s encuetra el cursor
                    {
                        case 76:	// Si el cursor esta en la pos=76 (Eliminar Reg Nº)
                            gotoxy(Cursor_Pos-2,9); cout << (char)Cursor;	// Mostramos el simbolo del cursor
                            cin >> Delete_Register;							// El usuario introduce el numero del producto que quiere eliminar
                            if (Delete_Register>Counter_Articles)			// Comprobamos que el nº introducido no sea mayor que el nº de productos
                            {
                                Show_Error ((char *) "ERROR: EL Nº DE REGISTRE NO ES VALID.", 1500); // Muestra un error
                            }
                            else	// Si el nº introducido es correcto
                            {
                                for (int i=0; i<Max_Chars ; i++)	// Bucle para recorrer el nombre del producto
                                {
                                    Pointer_Articles[Delete_Register-1]->Name[i] = 0;	// Iniciamos cada caracter delnombre del produto
                                }
                                // Ponemos todos los demas campos a 0
                                Pointer_Articles[Delete_Register-1]->PCompra = 0;
                                Pointer_Articles[Delete_Register-1]->PVenta = 0;
                                Pointer_Articles[Delete_Register-1]->PiecesV = 0;
                                Pointer_Articles[Delete_Register-1]->PiecesC = 0;
                                Pointer_Articles[Delete_Register-1]->Ingresado = 0;
                                Pointer_Articles[Delete_Register-1]->Gastado = 0;
                                gotoxy(85,9); cout << "Fet";
                            }
                            Cursor_Pos = 13;	// Dejamos el cursor en esa posicion
                        	break;

                        case 13: return 0; break;	// Si el cursor esta en la pos=13 (Volver al menu principal), salimos y regresamos
                    }
            }
            gotoxy(Cursor_Pos,9); // Dejamos el cursor en esa posicion
        }        
    }while (KEY_PAD!=27); // Volvemos a ejecutar el buclo si la tecla pulsada es distinta a ESC

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
    gotoxy(29,9); cout << ">> COMPRAR PRODUCTE <<";
    gotoxy(4,13); cout << "      Nom producte :";
    gotoxy(4,15); cout << "Quantitat producte :";
    gotoxy(4,17); cout << "                << DESAR >> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Cambia propiedad color text a Verde
    gotoxy(4,19); cout << "           << TORNA MENU PRINCIPAL" << endl;
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Cambia propiedad color text a Blanco
    gotoxy(25,Cursor_Pos);

    do{
        if (kbhit())		// Comprueba si hay alguna tecla pulsada
        {
            KEY_PAD = getch();	// Lee el cod. ascii de la tecla pulsada

            switch (KEY_PAD)	// Comprueba la tecla que hemos pulsado
            {
                case KEY_UP:	// Si se pulsa la tecla de la flecha arriba
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;	// Decrementamos las filas en 2 si es mayor de 13
                	break;

                case KEY_DOWN:	// Si se pulsa la tecla de la flecha abajo
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;	// Incrementamos las filas en 2 si es menor de 19
                	break;

                case KEY_ENTER:	// Si se pulsa ENTER

                    switch (Cursor_Pos)	// Comprueba la posicion del cursor 
                    {
                        case 13:	// Si la fila donde se encuentra el cursor es la 13 ( Nombre del producto )
                            gotoxy(25,Cursor_Pos); cout << (char)Cursor << "                    ";
                            gotoxy(25,Cursor_Pos); cout << (char)Cursor << " ";
                            cin >> Name; cin.clear(); cin.ignore(10, '\n');		// El usuario introduce el nombre del producto
                            gotoxy(45,Cursor_Pos); cout << "Fet";	// Muestra mensaje en pantalla
                        	break;

                        case 15:	// Si la fila donde se encuentra el cursor es la 15  ( Canidad de producto )
                            gotoxy(25,Cursor_Pos); cout << (char)Cursor << "                    ";
                            gotoxy(25,Cursor_Pos); cout << (char)Cursor << " ";
                            cin >> Quantity_Prod; cin.clear(); cin.ignore(10, '\n');	// El usuario introduce la cantidad de producto comprado
                            gotoxy(45,Cursor_Pos); cout << "Fet";	// Muestra mensaje en pantalla
                        	break;

                        case 17:	// Si la fila donde se encuentra el cursor es la 15  ( Guardar )
                            if (Quantity_Prod == 0 || Name[0] == 0) { Show_Error((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS'.", 1500); }
                            // Si hay algun campo vacio, muestra un mensaje de error
                            else
                            {
                                int j; int i;
                                for (j = 0 ; j < Counter_Articles ; j++)	// Bucle parabuscar el producto
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)	// Bucle para recorrer los caracteres del nombre
                                    {
                                        if (Pointer_Articles[j]->Name[i] != toupper(Name[i]) || Pointer_Articles[j]->Name[i] == 0) { break; }
                                        // Si el nombre no coincide o está en minusculas o no hay nada, salimos del bucle
                                    }

                                    if (i == strlen(Name)) { Found_Article = true; break; } // Si la longitu coincide, hemos encontrado el producto y salimos
                                }

                                if (Found_Article)	// Si encuentra el producto
                                {
                                    Pointer_Articles[j]->PiecesC += Quantity_Prod;	// Actualiza la cantidad de produtos comprados
                                    Pointer_Articles[j]->Gastado = Pointer_Articles[j]->PCompra * Pointer_Articles[j]->PiecesC; // Actualiza el capital invertido o gastado
									return 0;
                                }
                                else
                                {
                                    Show_Error((char *) "ERROR: ARTICLE NO TROBAT A L'INVENTARI'", 1500);
                                    // Si no encuentra el producto, muestra un mensaje de error
                                }
                            }
                        	break;

                        case 19: return 0; break; // Si la fila donde se encuentra el cursor es la 19  ( Volver Menu Principal ), terminamos y volvemos
                    }
            }
            gotoxy(25,Cursor_Pos);	// Dejamos el cursor en esa posicion
        }
      }while (KEY_PAD!=27);	// Si la teclapulsada es distinta a ESC volvemos a repetir el bucle, sino salimos
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
    gotoxy(29,9); cout << ">> VENDRE PRODUCTE <<" << endl;
    gotoxy(5,13); cout << "      Nom Producte : " << endl;
    gotoxy(5,15); cout << "Quantitat producte : " << endl;
    gotoxy(5,17); cout << "                  << DESAR >> ";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Ponemos el texto en Verde
    gotoxy(5,19); cout << "             << TORNA MENU PRINCIPAL" << endl;
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Ponemos el texto en blanco
    gotoxy(28,Cursor_Pos);

    do{
        if (kbhit())		// Comprueba si hay alguna tecla pulsada
        {
            KEY_PAD = getch();	// Lee el cod. ascii de la tecla pulsada
            switch (KEY_PAD)	// Comprueba la tecla pulsada
            {
                case KEY_UP:	// Si ha sido pulsada la tecla de la flecha arriba
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;	// Decrementamos las filas en 2 si es mayor de 13
                	break;

                case KEY_DOWN:	// Si ha sido pulsada la tecla de la flecha abajo
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;	// Incrementamos las filas en 2 si es menor de 19
                	break;

                case KEY_ENTER:	// Si ha sido pulsada la tecla ENTER
                    switch (Cursor_Pos)		// Comprueba la posicion del cursor
                    {
                        case 13:	// Si el cursor se encuentra en la fila 13 ( Nombre del producto)
                            gotoxy(26,Cursor_Pos); cout << (char)Cursor << "                    ";
                            gotoxy(26,Cursor_Pos); cout << (char)Cursor << " ";
                            cin >> Name; cin.clear(); cin.ignore(10, '\n');
                            gotoxy(45,Cursor_Pos); cout << "Fet";
                        	break;

                        case 15:	// Si el cursor se encuentra en la fila 15 ( Cantidad de producto a vender)
                            gotoxy(26,Cursor_Pos); cout << (char)Cursor << "                    ";
                            gotoxy(26,Cursor_Pos); cout << (char)Cursor << " ";
                            cin >> Quantity_Prod; cin.clear(); cin.ignore(10, '\n');
                            gotoxy(45,Cursor_Pos); cout << "Fet";
                        	break;

                        case 17:	// Si el cursor se encuentra en la fila 17 (Grabar)
                            if (Quantity_Prod == 0 || Name[0] == 0) { Show_Error((char *) "ERROR: HAS D'ENTRAR TOTS ELS VALORS'.",1500); }
                            // Si la cantidad a vender=0 o no se ha introducido nombre, muestra un error
                            else
                            {
                                int j; int i;
                                for (j = 0 ; j < Counter_Articles ; j++)	// Bucle para recorrer todos los productos
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)	// Bucle para recorrer todos los caracteres del producto
                                    {
                                    	//  Si el caracter del nombre esta en minuscula o si es un caracter=0
                                        if (Pointer_Articles[j]->Name[i] != toupper(Name[i]) || Pointer_Articles[j]->Name[i] == 0) { break; }
                                    }
                                    if (i == strlen(Name)) { Found_Article = true; break; } // Si lo encuentra pone Foun_Article=true
                                }

                                if (Found_Article)	// Si ha encontrado el producto
                                {
                                    if (Quantity_Prod <= Pointer_Articles[j]->PiecesC)	// Si la cantidad indicada es menor que la que hay en stock
                                    {
                                        Pointer_Articles[j]->PiecesV += Quantity_Prod;	// Actualiza las cantidades vendidas
                                        Pointer_Articles[j]->Ingresado = Pointer_Articles[j]->PVenta * Pointer_Articles[j]->PiecesV; // Actualiza el importe vendido
                                        return 0;
                                    }
                                    else	// Si hemos introducido una cantidad mayor que la que hay en stock
                                    {
                                        Show_Error((char *) "ERROR: LA QUANITTAT D'ARTICLES ES MASSA ALTA'.",1500); // Muestra un error
                                    }
                                }
                                else	// Si no se ha encontrado el producto
                                {
                                    Show_Error((char *) "ERROR: ARTICLE NO TROBAT A L'INVENTARI'.",1500); // Muestra un mensaje de error
                                }
                            }
                        	break;

                        case 19: return 0; break;	// Si el cursor esta en la fila 19 (Volver almenu principal)
                    }
            }
            gotoxy(28,Cursor_Pos);
        }
      }while (KEY_PAD!=27);		// Si la tecla pulsada es distinta a ESC volvemos a ejecutar el bucle
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
    float TInvertido = 0; float TIngresado=0; float TGanancias=0;	// Variables nenecasrias para calcular las ganancias

    system("cls");
    Show_Title ();
    gotoxy(27,9); cout << ">> REPORT PRODUCTES <<" << endl;
    gotoxy(1,11); cout << "                     -----------------------------------------";
    gotoxy(1,12); cout << "                     |      COMPRA       |       VENDA       |";
    gotoxy(1,13); cout << "------------------------------------------------------------------------------------------------------";
    gotoxy(1,14); cout << "|No.|  NOM PRODUCTE  | QUANT. |   PREU   | QUANT. |   PREU   | STOCK | INVERT. | INGRES. |  GUANYS   |";
    gotoxy(1,15); cout << "------------------------------------------------------------------------------------------------------";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Pone texto de color verde
	gotoxy(1,9);  cout << " << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Pone el texto de colorblanco

    int j; int i;

    for (j = 0 ; j < Counter_Articles ; j++)
    {
        gotoxy(2,16+j);	cout << j+1; // Muestra el numero del Producto
        gotoxy(8,16+j);				// Coordenadas del nombre del Producto
        for (i = 0 ; i<Max_Chars ; i++)	// Bucle para recorrer el nombre
        {
            cout << Pointer_Articles[j]->Name[i];	// Muestra el nombre del Producto
            if (Pointer_Articles[j]->Name[i] == 0) { break; }
        }
        cout << setprecision(2); // Usamos 2 decimales
        
        gotoxy(25,16+j); cout << fixed << Pointer_Articles[j]->PiecesC; 	// Muestra la cantidad de productos comprados
        gotoxy(34,16+j); cout << fixed << Pointer_Articles[j]->PCompra; 	// Muestra el precio de compra
        gotoxy(45,16+j); cout << fixed << Pointer_Articles[j]->PiecesV; 	// Muestra la cantidad de productos vendidos
        gotoxy(54,16+j); cout << fixed << Pointer_Articles[j]->PVenta; 	// Muestra el precio de compra
        gotoxy(65,16+j); cout << fixed << Pointer_Articles[j]->PiecesC - Pointer_Articles[j]->PiecesV;	// Muestra las piezas en stock
        gotoxy(72,16+j); cout << fixed << Pointer_Articles[j]->Gastado;	    // Muestra el importe gastado
        gotoxy(82,16+j); cout << fixed << Pointer_Articles[j]->Ingresado;   // Muestra el importe ingresado
        gotoxy(94,16+j); cout << fixed << Pointer_Articles[j]->Ingresado - Pointer_Articles[j]->Gastado;   // Muestra los beneficios
    }

    gotoxy(1, 16+j); cout <<"------------------------------------------------------------------------------------------------------";
    gotoxy(55, 17+j); cout << "TOTALS : ";
    
    for (int k = 0; k < Counter_Articles ; k++)		// Bucle para recorrer todos los productos
    {
        TInvertido +=  Pointer_Articles[k]->Gastado;		// Calculo del total invertido
        TIngresado +=  Pointer_Articles[k]->Ingresado;		// Calculo del total ingresado
        TGanancias=TIngresado-TInvertido;					// Calgulo de las ganancias
    }
    gotoxy(72, 17+j); cout << fixed << TInvertido;	// Muestra el Total invertido
    gotoxy(82, 17+j); cout << fixed << TIngresado;	// Muestra el Total ingresado
    gotoxy(94, 17+j); cout << fixed << TGanancias;	// Muestra las ganancias


    gotoxy(13,9);
    do{
        if (kbhit())	// Comprueba que haya alguna tecla pulsada
        {
            KEY_PAD = getch();	// Lee el cod. ascii de la tecla pulsada
            switch (KEY_PAD)
            {
                case KEY_ENTER:	// Si se ha pulsado ENTER retorna 0 y termina la funcion
                    return 0;
            }
        }
      }while (KEY_PAD!=27);	// Repite el bucle si no se pulsa la tecla ESC
    return 0;
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

    for (int i = 0; i < 100 ; i++)	// Bucle para contar los productos
    {
        if (Pointer_Articles[i]->Name[i] == 0) break;
        Elements_Number++;	// incrementa la cantidad de productos
    }
    return Elements_Number;	// Devuelve la cantidad de productos
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
    for (int i = 0 ; i<Max_Chars ; i++)	// Bucle para inciar el nombre del producto
    {
        Pointer_Articles[Article]->Name[i] = 0;
    }
    // Inicia todos los campos con 0
    Pointer_Articles[Article]->PiecesC = 0;
    Pointer_Articles[Article]->PiecesV = 0;
    Pointer_Articles[Article]->PCompra = 0;
    Pointer_Articles[Article]->PVenta = 0;
    Pointer_Articles[Article]->Gastado = 0;
    Pointer_Articles[Article]->Ingresado = 0;
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
    float TInvertido = 0; float TIngresado=0; float Ingresado=0; float Invertido=0;

    system("cls");
    Show_Title ();
    gotoxy(29,9); cout << ">> DESAR REPORT <<" << endl;
    gotoxy(5,13); cout << "Nom fitxer : " <<endl;
    gotoxy(5,15); cout << "           << DESAR >>" << endl;
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Pone el texto en color verde
	gotoxy(5,17); cout << "     << TORNA MENU PRINCIPAL" << endl;
	
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Pone el texto en color blanco
    gotoxy(20,Cursor_Pos);	// Pone el cursor en la pos=20

    do{
        if (kbhit())		// Comprueba si alguna tecla esta pulsada
        {
            KEY_PAD = getch();	// Lee el co. ascii de la tecla pulsada
            switch (KEY_PAD)	// Comprueba la tecla que ha sidopulsada
            {
                case KEY_UP:	// Si se ha pulsado la tecla de la flecha arriba
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                	break;

                case KEY_DOWN:	// Si se ha pulsado la tecla de la flecha abajo
                    if (Cursor_Pos < 17) Cursor_Pos = Cursor_Pos + 2;
                	break;

                case KEY_ENTER:	// Si se ha pulsado la tecla ENTER
                    switch (Cursor_Pos)	// Comprueba la fila donde se encuentra el cursor
                    {
                        case 13:	// Caso que la fila=13 (Nombre del fichero)
                            gotoxy(18,Cursor_Pos); cout << (char)Cursor << "                    ";
                            gotoxy(18,Cursor_Pos); cout << (char)Cursor << " ";
                            cin >> File_Name; cin.clear(); cin.ignore(10, '\n');	// El usuario introduce el nombre del fichero
                            gotoxy(35,Cursor_Pos); cout << "Fet";

                            for (int i = 0 ; i<Max_Chars ; i++)	// Bucle para recorrer todos los caracteres del nombre del fichero
                            {
                                File_Name[i] = toupper(File_Name[i]);	// Convertimos el nombre a mayusculas
                                if (File_Name[i] == 0) break;
                            }
                        	break;

                        case 15:	// Caso que la fila=15 (Grabar)
                            if (File_Name[0] == 0)	// Si no hemos introducido ningun nombre
                            {
                                Show_Error ((char *) "ERROR: ENTRAR UN NOM PRIMER.", 1500);	// Muestra mensaje de error
                            }
                            else	// Si el nombre del fichero es correcto
                            {
                                ofstream file (File_Name);	// Abrimos el fichero para escribir
                                if (file.is_open())	// Comprobamos si ha podido abrirse
                                {
                                	//************* GRABAMOS EL CONTENIDO DEL FICHERO **************************
                                    file << "                                                 >> REPORT PRODUCTES <<                               " << endl;
                                    file << "-------------------------------------------------------------------------------------------------------------" << endl;
                                    //file << "|\tNo.\t|\t\tNOM\t\t|\t PREU VENDA \t|\t PREU COMPRA \t|\tQ. VENUDES\t|\tQ.COMPRADES\t|\tINVERTITS\t|\tINGRESSAT\t|" << endl;
                                    file << "|  No.  |      NOM      | PREU  VENDA | PREU COMPRA | Q.  VENUDES | Q.COMPRADES |  INVERTITS  |  INGRESSAT  |" << endl;
                                    file << "-------------------------------------------------------------------------------------------------------------" << endl;
                                    file << endl;

                                    int j; int i;

                                    for (j = 0 ; j < Counter_Articles ; j++)	// Bucle para recorrer todos los productos
                                    {
                                        file << "#  " << j+1 << "\t\t";	// Graba el numero del producto
                                        for (i = 0 ; i<Max_Chars ; i++)	// Bucle para grabar el nombre del producto
                                        {
                                            file << Pointer_Articles[j]->Name[i];
                                            if (Pointer_Articles[j]->Name[i] == 0) { break; }
                                        }
                                        file << setprecision(2);
                                        file << "\t\t" << fixed << Pointer_Articles[j]->PVenta;					// Graba el precio de venta
                                        file << "\t\t" << fixed << Pointer_Articles[j]->PCompra;				// Graba el precio de compra
                                        file << "\t\t\t" << fixed << Pointer_Articles[j]->PiecesV;				// Graba la cantidad de productos vendidos
                                        file << "\t\t\t\t" << fixed << Pointer_Articles[j]->PiecesC;				// Graba la cantidad de productos comprados
                                        Invertido=Pointer_Articles[j]->PCompra * Pointer_Articles[j]->PiecesC;	// Calcula el capital invertido
                                        Ingresado=Pointer_Articles[j]->PVenta * Pointer_Articles[j]->PiecesV;	// Calcula el capital ingresado
                                        file << "\t\t\t" << fixed << Invertido;									// Graba el capital invertido (compras)
                                        file << "\t\t\t" << fixed << Ingresado << endl;							// Graba el capital ingresado (ventas)
                                    }
									// ******** PARTE DE ABAJO DE LA GRABACION ******************
                                    file << endl;
                                    file <<"-------------------------------------------------------------------------------------------------------------" << endl;
                                    file << "\t\t\t\t\t\t\t\t\t\t\t\t\tTOTALES  €  :";

                                    for (int k = 0; k < Counter_Articles ; k++)	// Bucle para calcular los totales
                                    {
                                    	Invertido=Pointer_Articles[k]->PCompra * Pointer_Articles[k]->PiecesC;	// Calcula invertido
                                    	Ingresado=Pointer_Articles[k]->PVenta * Pointer_Articles[k]->PiecesV;	// Calcula ingresado
                                        TInvertido +=  Invertido;	// Calcula total invertido
                                        TIngresado +=  Ingresado;	// Calcula total inresado
                                    }
                                    file << "\t\t\t\t\t" << fixed << TInvertido;	// Graba el total invertido
                                    file << "\t\t\t" << fixed << TIngresado;		// Graba el total ingresado
                                    file.close();	// Cierra el fichero
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green);	// Pone texto en verde
                                    gotoxy(25,25); cout << "FITXER CREAT CORRECTAMENT.";
                                    Sleep (1500);	// espera 1500 ms
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Pone texto en blanco
                                    return 0;
                                }
                                else	// Si el fichero no se ha poddio abrir
                                {
                                    Show_Error ((char *) "ERROR: EL FITXER NO HA SIGUT CREAT.", 1500); return 0; // Muestra un mensaje de error
                                }
                            }
                        	break;

                        case 17:	// Si el cursor esta en la fila 17 (Volver menu principal), sale retornando un 0
                            return 0; break;
                    }
            }
            gotoxy(20,Cursor_Pos);	// Coloca el cursor en esa posicion
        }
      }while (KEY_PAD!=27);		// Se vuelve a ejecutar el bucle si la tecla pulsada es distinta a ESC
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
    char String_Row[500];

    char Name[Max_Chars];
    float PCompra = 0, PVenta = 0;
    int PiecesC; int PiecesV;
    float Gastado; float Ingresado;

    system("cls");
    Show_Title ();
    gotoxy(27,9); cout << ">> CARREGAR REPORT <<" << endl;
    gotoxy(5,13); cout << " Nom Fitxer : " << endl;
    gotoxy(5,15); cout << "         << CARREGAR >>" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green); 	// Texto en color verde
    gotoxy(4,17); cout << "      << TORNA MENU PRINCIPAL" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);	// Texto en color blanco
    gotoxy(20,Cursor_Pos);

    do{
        if (kbhit())		// Si alguna tecla ha sido pulsada
        {
            KEY_PAD = getch(); // Guarda el cod Ascii de la tecla pulsada en KEY_PAD

            switch (KEY_PAD)	// Comprueba la tecla pulsada
            {
                case KEY_UP:	// Si se ha pulsado la tecla de la flecha arriba
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;		//Decrementa las filas en 2 si es mayor de 13
                	break;

                case KEY_DOWN:	// Si se ha pulsado la tecla de la flecha abajo
                    if (Cursor_Pos < 17) Cursor_Pos = Cursor_Pos + 2;		//Incrementa las filas en 2 si es menor de 17
                	break;

                case KEY_ENTER: // Si se ha pulsado la tecla ENTER
                    switch (Cursor_Pos)		// Comprueba la posicion del cursor
                    {
                        case 13:		// Si el cursor esta en la Pos=13    (Nombre del fichero)
                            gotoxy(18,Cursor_Pos); cout << (char)Cursor << "                    ";	// Borramos el campo del nombre
                            gotoxy(18,Cursor_Pos); cout << (char)Cursor << " ";		// Borramos el simbolo del cursor
                            cin >> File_Name; cin.clear(); cin.ignore(10, '\n');	// El usuario introduce el nombre del fichero
                            gotoxy(35,Cursor_Pos); cout << "Fet";

                            for (int i = 0 ; i<Max_Chars ; i++)		// Bucle para recorrer todo el nombre del fichero
                            {
                                File_Name[i] = toupper(File_Name[i]);	// Pone el nombre en mayusculas
                                if (File_Name[i] == 0) break;
                            }
                        	break;

                        case 15:		// Si el cursor esta en la Pos=15    ( Guardar )
                            if (File_Name[0] == 0) { Show_Error ((char *) "ERROR: ENTRAR UN NOM PRIMER.", 1500); } // Muestra mensaje de error
                            else
                            {
                                ifstream file (File_Name);	// Abrimos el fichero para lectura
                                if (file.is_open())		// Comprobamos si el fichero se ha abierto correctamente
                                {
                                    while(!file.eof())		// Bucle que recorre el fichero completo hasta llegar al final
                                    {
                                        file >> String_Row;

                                        if (String_Row[0] == '#')	// Buscamos el simbolo # donde comienzan los datos a cargar
                                        {
                                        	// ****** Lee los datos delfichero********
                                            file >> String_Row;
                                            file >> Name;
                                            file >> PVenta;
                                            file >> PCompra;
                                            file >> PiecesV;
                                            file >> PiecesC;
                                            file >> Gastado;
                                            file >> Ingresado;
                                            //****************************************

                                            if (Name[0] != 0)
                                            {
                                            	// Inicializamos la structure para almacenar los datos del fichero abierto
                                                Pointer_Articles[Counter_Articles] = new Article_Struct;
                                                Init_Structure_Elements(Counter_Articles);

                                                for (int i = 0 ; i<Max_Chars ; i++)	// Bucle para recorrer todo el nombre
                                                {
                                                    Pointer_Articles[Counter_Articles]->Name[i] = Name[i];	// Se actualiza el campo Name de ls structure
                                                    if (Name[i] == 0) { break; }
                                                }
                                                // Actualiza la structure con las variables leidas
                                                Pointer_Articles[Counter_Articles]->PCompra = PCompra;
                                                Pointer_Articles[Counter_Articles]->PVenta = PVenta;
                                                Pointer_Articles[Counter_Articles]->Gastado = Gastado;
                                                Pointer_Articles[Counter_Articles]->Ingresado = Ingresado;
                                                Pointer_Articles[Counter_Articles]->PiecesC = PiecesC;
                                                Pointer_Articles[Counter_Articles]->PiecesV = PiecesV;
                                                //*********************************************************
                                                Counter_Articles++;		// Incrementamos el contador de productos
                                            }
                                        }
                                        if (String_Row[0] == '$') file >> Total_Inventary;
                                    }

                                    if (Counter_Articles == 0)	// Si no ha encontrado ningun producto (Fichero vacio)
                                    {
                                        Show_Error ((char *) "EL FITXER NO CONTE INFORMACIO A CARREGAR.", 1500); // Muestra mensaje de error indicado
                                        file.close(); // Cierra el fichero
                                        return 0;
                                    }
                                    else	// Si ha encontrado algun producto
                                    {
                                    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Green); // Color texto = Verde
                                        gotoxy(25,25); cout << "FITXER CARREGAT CORRECTAMENT."; // Muestra mensaje de error indicado
                                        Sleep (1500); // Espera 1500 ms
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def); // Color texto = blanco
                                        file.close(); // Cierra el fichero
                                        return 0;
                                    }

                                }
                                else // Si el fichero no se ha abierto de forma correcta
                                {
                                    Show_Error ((char *) "ERROR: EL FITXER NO S'HA OBERT'.", 1500); return 0; // Muestra mensaje de error indicado
                                }
                            }
                        	break;

                        case 17:	// Caso que estemos en la fila 17 (Volver menu principal)
                            return 0;
                        	break;
                    }
            }
            gotoxy(20,Cursor_Pos);	// Dejamos el cursor en esa posicion
        }
      }while (KEY_PAD!=27);	// Si la tecla pulsada no es ESC (Ascii 27) vuelve al bucle
      return 0;
}

/********************************************************************
*                     Función: Show_Error   						*
* Argumentos de entrada: 											*
* - Puntero a cadena, tiempo de retardo de Integet. * 				*
* Argumentos de salida: 											*
* 																	*
* Esta función muestra un error en la pantalla.                     *
********************************************************************/
void Show_Error (char *Pointer_String, int Show_Delay_us)
{
    int Strin_Leng = strlen (Pointer_String);
    gotoxy(23,25); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red); // Color texto = rojo
    for (int i = 0; i <= Strin_Leng ; i++) { cout << *(Pointer_String+i); }	// Muestra el error
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);				// Color texto = blanco
    Sleep(Show_Delay_us);	// Esperar los us indicados
    gotoxy(23,25);
    for (int i = 0; i <= Strin_Leng ; i++) { cout << ' '; }
}
