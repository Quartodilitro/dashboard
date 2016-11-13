/**
 * Copyright 2016 Quartodilitro Team Unipd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef STD_UTILS
#define STD_UTILS


#include <sstream>


std::string toString(double number){
    //2 decimal precision
    std::ostringstream result;

    result << floor(number);
    result << ".";

    int decimals = 100 * (number - (floor(number)));

    result << decimals;

    return result.str();
}

std::string toString(int number){
    std::ostringstream result;

    result << number;

    return result.str();
}

double doubleRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

#endif // STD_UTILS
