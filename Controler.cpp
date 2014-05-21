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

#include "Controler.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;


/// Class that manages the unlock process.
void Manager::lock(){
    View view;
    Manager manager;
    int** tab = NULL; // Creation of the table
    tab =  new int*[9];
    for (int i = 0 ; i < 9 ; i++)
    {
        tab[i] = new int[9];
    }

    bool ok = false;

    manager.tableGeneration(tab, 9);  // Generation of the table
    Password password = manager.recover();
    string passwordGenerated = manager.generatePassword(tab, 9, password);
    string passwordEntered;

    system("cls");
    view.printTable(tab, 9);
    passwordEntered = view.enterPassword();

    while(!ok){
        if(passwordEntered == passwordGenerated){   /// password entered and generated are the same => OK
            ok = true;
            system("cls");
            view.printTable(tab, 9);
            cout << "Password:  " << passwordEntered << endl;
            cout << endl << endl << endl << "System unlocked" << endl << endl << endl;
        }
        else{   /// password entered and generated are not the same => NOT OK ==> Loop
            system("cls");
            view.printTable(tab, 9);
            cout << "Wrong password" << endl;
            passwordEntered = view.enterPassword();
        }
    }
}

/// Method that saves the data into a specific file, SecuriTable_Password.txt.
void Manager::save(Password password){

    srand(time(NULL));

    ofstream fichier ("SecuriTable_Password.txt", ios::out | ios::trunc);

    fichier << password.getAbscissa1() - 1<< endl;
    fichier << password.getOrdinate1()  - 1<< endl;
    fichier << password.getAbscissa2()  - 1<< endl;
    fichier << password.getOrdinate2()  - 1<< endl;
    fichier << password.getAbscissa3()  - 1<< endl;
    fichier << password.getOrdinate3()  - 1<< endl;
    fichier << password.getAbscissa4()  - 1<< endl;
    fichier << password.getOrdinate4()  - 1<< endl;
    fichier << password.getType() << endl;

    fichier.close();
}

/// Method that generates the table with random values.
void Manager::tableGeneration(int** tab, int taille){

    srand(time(NULL));
    bool ok = false;

    for(int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            do {
                tab[i][j]  = rand() % (9 + 1);
                /// Algorithm that forbids having two consecutive numbers AND ALSO forbids having generation like 101 or 636
                if (((i - 1 >= 0) && (tab[i - 1][j] == tab[i][j]))
                    || ((j - 1 >= 0) && (tab[i][j - 1] == tab[i][j]))/** Comment this lines to allow generation like 101 but still deny generation like 11 or 00. **/
                    || ((i - 2 >= 0) && (tab[i - 2][j] == tab[i][j]))
                    || ((j - 2 >= 0) && (tab[i][j - 2] == tab[i][j]))/** End comment **/
                    ) {
                    ok = false;
                } else {
                    ok = true;
                }
            } while (!ok);
            ok = false;
        }
    }
}

/// Method that generates the password from the coordinates and the table.
string Manager::generatePassword(int** tab, int taille, Password password){
    string chaine;

    int abs1 = password.getAbscissa1();
    int ord1 = password.getOrdinate1();
    int abs2 = password.getAbscissa2();
    int ord2 = password.getOrdinate2();
    int abs3 = password.getAbscissa3();
    int ord3 = password.getOrdinate3();
    int abs4 = password.getAbscissa4();
    int ord4 = password.getOrdinate4();

    if(password.getType() == 1){	// Linear

        /// If the password is vertical:
        if(abs1 == abs2){
            chaine = "";
            /// Up -> Down
            if(ord1 < ord2){
                for(int i = ord1 ; i < ord2 + 1 ; i++){
                    chaine += tab[i][abs1] + 48;
                }
            }
            /// Down -> Up
            else{
                for(int i = ord1 ; i > ord2 - 1; i--){
                    chaine += tab[i][abs1] + 48;
                }
            }
        }
        /// If the password is horizontal:
        else if(ord1 == ord2){
            chaine = "";
            /// Left -> Right
            if(abs1 < abs2){
                for(int i = abs1 ; i < abs2 + 1 ; i++){
                    chaine += tab[ord1][i] + 48;
                }
            }
            /// Right -> Left
            else{
                for(int i = abs1 ; i > abs2 - 1; i--){
                    chaine += tab[ord1][i] + 48;
                }
            }
        }
        /// If the password is in diagonal NW-SE or SE-NW
        else if((abs1 - abs2) == (ord1 - ord2)){
            chaine = "";
            if ((abs1 - abs2) < 0){   /// NW -> SE
                int i = abs1 - 1;
                int j = ord1 - 1;
                while((i != abs2) && (j != ord2)){
                    i++;
                    j++;
                    chaine += tab[j][i] + 48;
                }
            }
            else{   /// SE -> NW
                int i = abs1 + 1;
                int j = ord1 + 1;
                while((i != abs2) && (j != ord2)){
                    i--;
                    j--;
                    chaine += tab[j][i] + 48;
                }
            }
        }
        /// Else, the password is in diagonal NE-SW or SW-NE
        else{
            chaine = "";
            if ((abs1 - abs2) < 0){   /// SW -> NE
                int i = abs1 - 1;
                int j = ord1 + 1;
                while((i != abs2) && (j != ord2)){
                    i++;
                    j--;
                    chaine += tab[j][i] + 48;
                }
            }
            else{   /// NE -> SW
                int i = abs1 + 1;
                int j = ord1 - 1;
                while((i != abs2) && (j != ord2)){
                    i--;
                    j++;
                    chaine += tab[j][i] + 48;
                }
            }
        }
    }
    else if(password.getType() == 2){	// NCC3
        chaine = "";
        chaine += tab[ord1][abs1] + 48;
        chaine += tab[ord2][abs2] + 48;
        chaine += tab[ord3][abs3] + 48;
    }
    else{	// NCC4
        chaine = "";
        chaine += tab[ord1][abs1] + 48;
        chaine += tab[ord2][abs2] + 48;
        chaine += tab[ord3][abs3] + 48;
        chaine += tab[ord4][abs4] + 48;
    }
    return chaine;
}

/// Method that recovers the coordinates of the password from the file.
Password Manager::recover(){
    string ligne;
    string adresse = "SecuriTable_Password.txt";
    Password password;

    ifstream fichier(adresse.c_str());

    getline(fichier, ligne);
    password.setAbscissa1(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setOrdinate1(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setAbscissa2(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setOrdinate2(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setAbscissa3(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setOrdinate3(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setAbscissa4(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setOrdinate4(ligne[0] - 48);
    ligne.clear();
    getline(fichier, ligne);
    password.setType(ligne[0] - 48);

    return password;
}
