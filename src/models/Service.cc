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

#include "Service.hh"

Service::Service() {
	_id = -1;
	_name = "";
	_port = -1;
	_protocol = "";
	_vulnerabilities = new TCollection<Vulnerability*>();
	//_vulnerabilities->add(new Vulnerability());
}

Service::Service(int id, std::string name, int port, std::string protocol,
	TCollection<Vulnerability*> *vulnerabilities) {
	_id = id;
	_name = name;
	_port = port;
	_protocol = protocol;
	_vulnerabilities = vulnerabilities;
}

Service::Service(const Service&) {
}

Service::~Service() {
	delete _vulnerabilities;
}

int Service::getId() {
	return _id;
}

std::string Service::getName() {
	return _name;
}

int Service::getPort() {
	return _port;
}

std::string Service::getProtocol() {
	return _protocol;
}

TCollection<Vulnerability*> *Service::getVulnerabilities() {
	return _vulnerabilities;
}

void Service::setId(int id) {
	_id = id;
}

void Service::setName(std::string name) {
	_name = name;
}

void Service::setPort(int port) {
	_port = port;
}

void Service::setProtocol(std::string protocol) {
	_protocol = protocol;
}

void Service::setVulnerabilities(TCollection<Vulnerability*> *vulnerabilities) {
	_vulnerabilities = vulnerabilities;
}

std::string Service::toString() {
	std::string result = "Service(";
	result.append("id=\"");
	result.append(""+_id);
	result.append("\", ");
	result.append("name=\"");
	result.append(_name);
	result.append("\", ");
	result.append("port=\"");
	result.append(""+_port);
	result.append("\", ");
	result.append("protocol=\"");
	result.append(_protocol);
	result.append("\", ");
	result.append("#vulnerabilities=\"");
	result.append(_vulnerabilities->toString());
	result.append("\")");
	return result;
}
