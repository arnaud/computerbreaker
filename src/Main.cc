/*
 This file is part of the Computer Breaker project.

    Computer Breaker is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Computer Breaker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Computer Breaker; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <iostream>
#include <string>
#include <regex.h>
#include <ncurses.h>
#include "core/Breaker.hh"
#include "util/colors.h"
#include "util/Logger.hh"

bool isIPAddressValid(const char *input) {
	int match = -1;
	regex_t preg;
	const char *str_regex = "^(localhost|((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[0-1]?[0-9]?[0-9])\\.){3}(25[0-4]|2[0-4][0-9]|1[0-9]{2}|0?[1-9][0-9]|[1-9]))$";
	
	int err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
	if (err == 0) {
		match = regexec (&preg, input, 0, NULL, 0);
		regfree (&preg);
	}
	return match == 0;
}

int main (int argc, char *argv[])
{
	getLogger().debug("Main : main() - begin");
	
	// Usage
	if(argc > 2) {
		std::cout << "Usage : " << argv[0] << " [ip address]" << std::endl;
		std::cout << "(example: " << argv[0] << " 192.168.0.1)" << std::endl;
		getLogger().info("Wrong usage");
		getLogger().debug("Main : main() - end");
		exit(-1);
	}
	
	std::cout << std::endl << COL_U << "Target IP :" << COL_B << " ";
	std::string ip;
	if(argc == 2) {
		ip = (const char*)argv[1];
		std::cout << ip << std::endl;
	} else {
		std::getline(std::cin, ip);
	}
	std::cout << COL_NONE << std::endl;
	
	//Checks whether if the ip address entered is valid
	if(!isIPAddressValid((const char*)ip.c_str())) {
		std::cout << "Wrong IP address entered : " << ip.c_str() << std::endl;
		getLogger().info("Wrong IP address entered");
		getLogger().debug("Main : main() - end");
		endwin();
		exit(-1);
	}
	
	Breaker core ((const char*)ip.c_str());
	core.execute();
	
	getLogger().debug("Main : main() - end");
	endwin();
	return 0;
}
