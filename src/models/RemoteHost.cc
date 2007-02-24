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

#include "RemoteHost.hh"
#include <iostream>

RemoteHost::RemoteHost() {
	_ip_address = "localhost";
	_platform = new Platform();
}

RemoteHost::RemoteHost(std::string ip_address) {
	_ip_address = ip_address;
	_platform = new Platform();
}

RemoteHost::RemoteHost(std::string ip_address, Platform *platform) {
	_ip_address = ip_address;
	_platform = platform;
}

RemoteHost::~RemoteHost() {
	delete _platform;
}

std::string RemoteHost::getIpAddress() {
	return _ip_address;
}

Platform *RemoteHost::getPlatform() {
	return _platform;
}

void RemoteHost::setIpAddress(std::string ip_address) {
	_ip_address = ip_address;
}

void RemoteHost::setPlatform(Platform *platform) {
	_platform = platform;
}

std::string RemoteHost::toString() {
	std::string result = "RemoteHost(";
	result.append("ip=\"");
	result.append(_ip_address);
	result.append("\", ");
	result.append("#platforms=\"");
	result.append(_platform->getName());
	result.append("\")");
	return result;
}
