/*
 * mainGame.cpp
 *
 *  Created on: Feb 25, 2021
 *      Author: 13027
 */

#include "Board.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;


int main() {
	srand(time(NULL));
	Board board('m',"fido", true);
	return 0;
}


