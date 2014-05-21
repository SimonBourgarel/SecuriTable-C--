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

#ifndef VIEW_H
#define VIEW_H

#include "Password.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

class View{
public :
    void sChoice(); /// Method that asks the user to determine the type of the password.
    Password sLinear(); /// Method for configuring a linear password.
    Password s3NCCells(); /// Method for configuring a password of 3 non consecutive cells.
    Password s4NCCells(); /// Method for configuring a password of 4 non consecutive cells.
    void printTable(int** tab, int taille); /// Method for printing the table on the screen.
    string enterPassword(); /// Method that asks the user to enter his password.
};

#endif
