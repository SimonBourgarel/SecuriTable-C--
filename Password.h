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

#ifndef PASSWORD_H_INCLUDED
#define PASSWORD_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Password
{
    private :
        int type;
        int abscissa1;
        int ordinate1;
        int abscissa2;
        int ordinate2;
        int abscissa3;
        int ordinate3;
        int abscissa4;
        int ordinate4;

    public :
        void setType(int number){type = number;};
        void setAbscissa1(int number){abscissa1 = number;};
        void setOrdinate1(int number){ordinate1 = number;};
        void setAbscissa2(int number){abscissa2 = number;};
        void setOrdinate2(int number){ordinate2 = number;};
        void setAbscissa3(int number){abscissa3 = number;};
        void setOrdinate3(int number){ordinate3 = number;};
        void setAbscissa4(int number){abscissa4 = number;};
        void setOrdinate4(int number){ordinate4 = number;};

        int getType(){return type;};
        int getAbscissa1(){return abscissa1;};
        int getOrdinate1(){return ordinate1;};
        int getAbscissa2(){return abscissa2;};
        int getOrdinate2(){return ordinate2;};
        int getAbscissa3(){return abscissa3;};
        int getOrdinate3(){return ordinate3;};
        int getAbscissa4(){return abscissa4;};
        int getOrdinate4(){return ordinate4;};
};


#endif // PASSWORD_H_INCLUDED
