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

#include <fstream>
#include <string>
#include <boost/regex.hpp>
#include "../util/Logger.hh"
#include "Attack.hh"

void Attack::compile() {
	getLogger().debug("Attack : compile() - begin");
	// creates the code file
	std::ofstream f_code;
	f_code.open(getCodeFileName());
	if (f_code.is_open()) {
		f_code << _code << std::endl;
		f_code.close();
	}
	// compiles it
	if(strcmp(_language.c_str(), "c")==0) {
		std::string cmd = "gcc -o runExploit ";
		cmd += getCodeFileName();
		cmd += " 2> compile.log";
		system(cmd.c_str());
	} else if(strcmp(_language.c_str(), "cpp")==0) {
		std::string cmd = "g++ -o runExploit ";
		cmd += getCodeFileName();
		cmd += " 2> compile.log";
		system(cmd.c_str());
	} else {
		getLogger().error("Attack : compile() - Unknown Language '%s'", _language.c_str());
	}
	getLogger().debug("Attack : compile() - end");
}

const char *Attack::getCodeFileName() {
	std::string filename = "codeExploit";
	filename += ".";
	filename += _language;
	return filename.c_str();
}

std::string Attack::execute() {
	getLogger().debug("Attack : execute() - begin");
	// runs the exploit with redirection of the stdout
	std::string cmd = getCommand();
	
	// Execution
	
	if(cmd.length()==0) {
		cmd = "./runExploit";
	} else {
		boost::regex pattern;
		pattern = "\\{EXPLOIT\\}";
		cmd = boost::regex_replace(cmd, pattern, "./runExploit ");
		pattern = "\\{IP\\}";
		cmd = boost::regex_replace(cmd, pattern, _ip_address);
		/*pattern = "\\{PORT\\}";
		std::string port = "" + _port;
		cmd = boost::regex_replace(cmd, pattern, port);*/
	}
	cmd += " 1> stdout.";
	cmd += _num;
	cmd += " 2> stderr.";
	cmd += _num;
	getLogger().debug("Attack : Execution of => %s", cmd.c_str());
	system(cmd.c_str());
	
	// Get the standard outputs
	
	std::ifstream f_std;
	std::string out = "stdout." + _num;
	f_std.open(out.c_str());
	std::string content;
	if (f_std.is_open()) {
		while (!f_std.eof()) {
			std::string line;
			std::getline (f_std, line);
			content += line;
		}
		f_std.close();
	}
	getLogger().debug("Attack : execute() - end");
	return content.c_str();
}

void Attack::clean() {
	getLogger().debug("Attack : clean()");
	remove(getCodeFileName());
	remove("runExploit");
}

bool Attack::isAttackSuccess(std::string execResult) {
	getLogger().debug("Attack : isAttackSuccess() - begin");
	bool result = false;
	
	result = result || (execResult != "" && execResult.compare(getSuccessfulReturnValue()) == 0);
	
	if(getSuccessfulRegExReturnValue().length()>0) {
		boost::cmatch what;
		const char *e = getSuccessfulRegExReturnValue().c_str();
		boost::regex expression(e);
		result = result || regex_match(execResult.c_str(), what, expression);
	}
	
	getLogger().debug("Attack : isAttackSuccess() - begin");
	return result;
}

Attack::Attack() {
	_num = -1;
	_dependancies = new TCollection<Attack*>();
	_successful_return_value = "";
	_successful_regex_return_value = "";
	_type = "";
	_language = "";
	_command = "";
	_code = "";
}

Attack::Attack(int num, TCollection<Attack*> *dependancies, std::string successful_return_value,
	std::string successful_regex_return_value, std::string type, std::string language,
	std::string command, std::string code) {
	_num = num;
	_dependancies = dependancies;
	_successful_return_value = successful_return_value;
	_successful_regex_return_value = successful_regex_return_value;
	_type = type;
	_language = language;
	_command = command;
	_code = code;
}

Attack::Attack(const Attack&) {
}

Attack::~Attack() {
	delete _dependancies;
}

int Attack::getNum() {
	return _num;
}

TCollection<Attack*> *Attack::getDependancies() {
	return _dependancies;
}

std::string Attack::getSuccessfulReturnValue() {
	return _successful_return_value;
}

std::string Attack::getSuccessfulRegExReturnValue() {
	return _successful_regex_return_value;
}

std::string Attack::getType() {
	return _type;
}

std::string Attack::getLanguage() {
	return _language;
}

std::string Attack::getCommand() {
	return _command;
}

std::string Attack::getCode() {
	return _code;
}

void Attack::setNum(int num) {
	_num = num;
}

void Attack::setDependancies(TCollection<Attack*> *dependancies) {
	_dependancies = dependancies;
}

void Attack::setSuccessfulReturnValue(std::string successful_return_value) {
	_successful_return_value = successful_return_value;
}

void Attack::setSuccessfulRegExReturnValue(std::string successful_regex_return_value) {
	_successful_regex_return_value = successful_regex_return_value;
}

void Attack::setType(std::string type) {
	_type = type;
}

void Attack::setLanguage(std::string language) {
	_language = language;
}

void Attack::setCommand(std::string command) {
	_command = command;
}

void Attack::setCode(std::string code) {
	_code = code;
}

bool Attack::run(std::string ip_address/*, int port*/) {
	getLogger().debug("Attack : run() - begin");
	_ip_address = std::string(ip_address);
	//_port = port;
	compile();
	std::string execResult;
	execResult = execute();
	clean();
	bool result = isAttackSuccess(execResult);
	getLogger().debug("Attack : run() - end");
	return result;
}

std::string Attack::toString() {
	std::string result = "Attack(";
	result.append("num=\"");
	result.append(""+_num);
	result.append("\", ");
	result.append("#dependancies=\"");
	result.append(_dependancies->toString());
	result.append("\", ");
	result.append("returnValue=\"");
	result.append(_successful_return_value);
	result.append("\", ");
	result.append("regexReturnValue=\"");
	result.append(_successful_regex_return_value);
	result.append("\", ");
	result.append("type=\"");
	result.append(_type);
	result.append("\", ");
	result.append("command=\"");
	result.append(_command);
	result.append("\", ");
	result.append("ip=\"");
	result.append(_ip_address);
	result.append("\", ");
	result.append("code=\"");
	result.append(_code.substr(0,20));
	result.append("\")");
	return result;
}
