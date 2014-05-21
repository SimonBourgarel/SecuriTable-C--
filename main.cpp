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
#include "View.h"
#include "Password.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    string fileName = "SecuriTable_Password.txt";

    ifstream file(fileName.c_str());

    View view;
    Manager manager;

    if (!file){ /// If the file does not exist, launching of settings.
        view.sChoice();
    } else{ /// If the file exists, unlock process.
        manager.lock();
    }

    return 0;
}
