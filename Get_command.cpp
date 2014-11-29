/*
 * Get_command.cpp
 *
 *  Created on: 29 lis 2014
 *      Author: edek437
 */

#include "Get_command.h"

std::string get_command(std::string& input){ //get command and erase it from input string
	int i=0;
	std::string output;
	while(!(input[i]==' '||input.begin()+i==input.end())){
		output.push_back(input[i]);
		i++;
	}
	input.erase(0,i+1); //erasing command part form string
	return output;
}
