/**
 *    Copyright 2014 Simon Bourgarel

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   *
   **/

#include "View.h"
#include "Controler.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>

#include <iomanip>

using namespace std;

/// Asks the user to choose the type of password.
void View::sChoice(){
    bool ok = false;
    string userInput;
    Password password;
    Manager manager;
    int** tab = NULL;
    tab =  new int*[9];
    for (int i = 0 ; i < 9 ; i++)
    {
        tab[i] = new int[9];
    }

    do{
        userInput.clear();
        manager.tableGeneration(tab, 9);
        system("cls");
        cout << "Select the password's type :\n";
        cout << "2/ Linear password composed of 3 or 4 cases\n";
        cout << "3/ Password composed of 3 non consecutive cells\n";
        cout << "4/ Password composed of 4 non consecutive cells\n";

        getline(cin, userInput);

        if((userInput.size() != 1) || ((userInput[0] != '2')  && (userInput[0] != '3')  && (userInput[0] != '4'))){
            cout << "Bad choice..." << endl;
        }
        else
        {
            ok = true;
        }
    }while(!ok);

    int var = userInput[0] - 48;
    switch (var){
    case 2: /// Linear password.
        password = sLinear();
        break;
    case 3: /// Password with 3 non consecutive cells
        password = s3NCCells();
        break;
    default:    /// Password with 4 non consecutive cells
        password = s4NCCells();
        break;
    }

    manager.save(password);
}

/// Selection of cells for a linear password
Password View::sLinear(){
    bool ok = false;
    string coord;
    Password password;

    int abs1;	// First cell's abscissa
    int ord1;	// First cell's ordinate
    int abs2;	// Last cell's abscissa
    int ord2;	// Last cell's ordinate

    do{
            coord.clear();

            do{
                cout << "Enter the coordinates of the first cell : ";

                getline(cin, coord);

                if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
                {
                    cout << "Bad syntax..." << endl;
                }
                else
                {
                    ok = true;
                }
            }while(!ok);

            abs1 = coord[0] - 64;   // Transformation from char to int (ascii)
            ord1 = coord[1] - 48;

            ok = false;
            coord.clear();

            do{
                cout << "Enter the coordinates of the last cell : ";

                getline(cin, coord);

                if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1') || (coord[1] > '9')))
                {
                    cout << "Bad syntax..." << endl;
                }
                else
                {
                    ok = true;
                }
            }while(!ok);

            abs2 = coord[0] - 64;   // Transformation from char to int (ascii)
            ord2 = coord[1] - 48;


        ok = false;
        if(((abs1 == abs2) && ((ord1 == (ord2 - 3))))   // vertical
            || ((abs1 == abs2) && ((ord1 == (ord2 + 3))))
            || ((abs1 == abs2) && ((ord1 == (ord2 - 2))))
            || ((abs1 == abs2) && ((ord1 == (ord2 + 2))))
            || ((abs1 == (abs2 - 3)) && (ord1 == ord2)) // horizontal
            || ((abs1 == (abs2 + 3)) && (ord1 == ord2))
            || ((abs1 == (abs2 - 2)) && (ord1 == ord2))
            || ((abs1 == (abs2 + 2)) && (ord1 == ord2))
            || (((abs1 - abs2) == (ord1 - ord2)) && (((abs1 - abs2) == 2)
            || ((abs1 - abs2) == 3) || ((abs1 - abs2) == -2) || ((abs1 - abs2) == -3)))
            || (((abs1 - abs2) == -(ord1 - ord2)) && (((abs1 - abs2) == 2)
            || ((abs1 - abs2) == 3) || ((abs1 - abs2) == -2) || ((abs1 - abs2) == -3)))){
            ok = true;
        }
        else
        {
            cout << "Bad coordinates" << endl;
            ok = false;
        }
    }while(!ok);

    password.setType(1);
    password.setAbscissa1(abs1);
    password.setOrdinate1(ord1);
    password.setAbscissa2(abs2);
    password.setOrdinate2(ord2);

    password.setAbscissa3(0);
    password.setOrdinate3(0);
    password.setAbscissa4(0);
    password.setOrdinate4(0);

    return password;
}

/// Selection of cells for a password composed of 3 non consecutives cells.
Password View::s3NCCells(){
    bool ok = false;
    string coord;
    Password password;

    int abs1;	// First cell
    int ord1;
    int abs2;	// Second cell
    int ord2;
    int abs3;	// Last cell ( = Third)
    int ord3;

    do{
        coord.clear();
        system("cls");
        ok = false;
        do{
            cout << "Enter the coordinates of the first cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs1 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord1 = coord[1] - 48;

        ok = false;
        coord.clear();
        do{
            cout << "Enter the coordinates of the second cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs2 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord2 = coord[1] - 48;

        ok = false;
        coord.clear();
        do{
            cout << "Enter the coordinates of the last cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1') || (coord[1] > '9')))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs3 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord3 = coord[1] - 48;

        ok = false;
        if (!(((abs1 == abs2) && (ord1 == ord2)) || ((abs1 == abs3) && (ord1 == ord3)) || ((abs2 == abs3) && (ord2 == ord3)))) {
            /// Good coordinates
            password.setType(2);
            password.setAbscissa1(abs1);
            password.setOrdinate1(ord1);
            password.setAbscissa2(abs2);
            password.setOrdinate2(ord2);
            password.setAbscissa3(abs3);
            password.setOrdinate3(ord3);
            password.setAbscissa4(0);
            password.setOrdinate4(0);

            ok = true;
        }
        else{
            cout << "Bad coordinates" << endl;
        }
    }while(!ok);

    return password;
}

/// Selection of cells for a password composed of 4 non consecutives cells.
Password View::s4NCCells(){
    bool ok = false;
    string coord;
    Password password;

    int abs1;	// First cell
    int ord1;
    int abs2;	// Second cell
    int ord2;
    int abs3;	// Third cell
    int ord3;
    int abs4;	// Last cell ( = Fourth)
    int ord4;

    do{
        coord.clear();
        system("cls");
        ok = false;
        do{
            cout << "Enter the coordinates of the first cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs1 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord1 = coord[1] - 48;

        ok = false;
        coord.clear();
        do{
            cout << "Enter the coordinates of the second cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs2 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord2 = coord[1] - 48;


        ok = false;
        coord.clear();
        do{
            cout << "Enter the coordinates of the third cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1' || (coord[1] > '9'))))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs3 = coord[0] - 64;   // Transformation from char to int (ascii)
        ord3= coord[1] - 48;

        ok = false;
        coord.clear();
        do{
            cout << "Enter the coordinates of the last cell : ";

            getline(cin, coord);

            if(((coord.size() != 2) || (coord[0] < 'A') || (coord[0] > 'I')) || ((coord[1] < '1') || (coord[1] > '9')))
            {
                cout << "Bad syntax..." << endl;
            }
            else
            {
                ok = true;
            }
        }while(!ok);

        abs4 = coord[0] - 64;
        ord4 = coord[1] - 48;

        ok = false;
        if (!(((abs1 == abs2) && (ord1 == ord2))
                || ((abs1 == abs3) && (ord1 == ord3))
                || ((abs1 == abs4) && (ord1 == ord4))
                || ((abs2 == abs3) && (ord2 == ord3))
                || ((abs2 == abs4) && (ord2 == ord4))
                || ((abs3 == abs4) && (ord3 == ord4)))) {
            /// Good coordinates
            password.setType(3);
            password.setAbscissa1(abs1);
            password.setOrdinate1(ord1);
            password.setAbscissa2(abs2);
            password.setOrdinate2(ord2);
            password.setAbscissa3(abs3);
            password.setOrdinate3(ord3);
            password.setAbscissa4(abs4);
            password.setOrdinate4(ord4);
            ok = true;
        }
        else{
            cout << "Bad coordinates" << endl;
        }
    }while(!ok);

    return password;
}

/// Method that asks the user to enter the password, and loops until the syntax is not good.
string View::enterPassword(){
    string code = "";
    bool ok = false;

    do{
        code = "";
        cout << "Password:  ";

        getline(cin, code);

        if(((code.size() == 4) && ((code[0] >= '0') && (code[0] <= '9')) && ((code[1] >= '0') && (code[1] <= '9')) && ((code[2] >= '0') && (code[2] <= '9')) && ((code[3] >= '0') && (code[3] <= '9'))) || ((code.size() == 3 && ((code[0] >= '0') && (code[0] <= '9')) && ((code[1] >= '0') && (code[1] <= '9')) && ((code[2] >= '0') && (code[2] <= '9')))))
        {
            ok = true;
        }
        else
        {
            cout << "Bad Syntax..." << endl;
        }
    }while(!ok);

    return code;
}

/// Method that prints the table.
void View::printTable(int** tab, int taille){
    /// Top table printing
    cout << char(201) << setfill(char(205)) << setw(4) << setfill(char(205)) << setw(4) << char(203) << setfill(char(205)) << setw(4) << char(203) << setfill(char(205)) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205)) << char(203) << setw(4) << setfill(char(205));
    cout << char(203) << setw(4) << setfill(char(205)) << char(187) << endl;
    cout << char(186) << setfill(' ') << setw(4) << char(186) << " A " << char(186) << " B " << char(186) << " C " << char(186) << " D " << char(186) << " E " << char(186) << " F " << char(186) << " G " << char(186) << " H " << char(186) << " I " << char(186)<< endl;
    cout << char(204) << setfill(char(205)) << setw(4) << setfill(char(205)) << setw(4) << char(206) << setfill(char(205)) << setw(4) << char(206) << setfill(char(205)) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205)) << char(206) << setw(4) << setfill(char(205));
    cout << char(206) << setw(4) << setfill(char(205)) << char(185) << endl;

    /// Table printing
    for(int i = 0 ; i < 9 ; i++)
    {
        cout << char(186) << " " << i + 1 << " " << char(186);
        for (int j = 0 ; j < 9 ; j++)
        {
            cout << " " << tab[i][j] << " " << char(186);
        }
        cout << endl;
    }

    /// Bottom table printing
    cout << char(200) << setfill(char(205)) << setw(4) << setfill(char(205)) << setw(4) << char(202) << setfill(char(205)) << setw(4) << char(202) << setfill(char(205)) << setw(4) << setfill(char(205)) << char(202) << setw(4) << setfill(char(205)) << char(202) << setw(4) << setfill(char(205)) << char(202) << setw(4) << setfill(char(205)) << char(202) << setw(4) << setfill(char(205));
    cout << char(202) << setw(4) << setfill(char(205)) <<  char(202) << setw(4) << setfill(char(205)) <<  char(202) << setw(4) << setfill(char(205)) << char(188) << endl;

    return;
}


