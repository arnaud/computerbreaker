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

#include "Platform.hh"

Platform::Platform() {
	_name = "";
	_distributions = new TCollection<std::string>();
}

Platform::Platform(std::string name, TCollection<std::string> *distributions) {
	_name = name;
	_distributions = distributions;
}

Platform::~Platform() {
	delete _distributions;
}

std::string Platform::getName() {
	return _name;
}

TCollection<std::string> *Platform::getDistributions() {
	return _distributions;
}

void Platform::setName(std::string name) {
	_name = name;
}

void Platform::setDistributions(TCollection<std::string> *distributions) {
	_distributions = distributions;
}

std::string Platform::toString() {
	std::string result = "Platform(";
	result.append("name=\"");
	result.append(_name);
	result.append("name=\"");
	result.append(_name);
	result.append("\", ");
	result.append("#distributions=\"");
	result.append(_distributions->toString());
	result.append("\")");
	return result;
}
