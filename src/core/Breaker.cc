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

#include "Breaker.hh"
#include <iostream>
#include "../dbms/DatabaseReader.hh"
#include "../dbms/ExploitsSearcher.hh"
#include "../dbms/VulnerabilitiesSearcher.hh"
#include "../util/colors.h"
#include "../util/Logger.hh"

/**
 * Constructor - defines the IP Address of the remote computer
 */
Breaker::Breaker(const char *ip_address) {
	_remote_host = new RemoteHost(ip_address);
	_target_infos_handler = new TargetInformationsHandler();
	_services = new TCollection<Service*>();
	_vulnerabilities = new TCollection<Vulnerability*>();
	_exploits = new TCollection<Exploit*>();
}

/**
 * Destructor
 */
Breaker::~Breaker() {
	delete _remote_host;
}

/**
 * Executes attacking the remote computer
 */
void Breaker::execute() {
	getLogger().debug("Breaker : execute() - begin");
	bool state;
	
	// 1 - Searching for target informations
	showCategory(1, "Searching for target informations...");
	std::cout << COL_B << " * " << COL_NONE << "Probing target with Nessus...      " << std::flush;
	state = searchInformations();
	showResult(state);
	if(state) { // Converting Nessus results
		std::cout << COL_B << " * " << COL_NONE << "Converting Nessus results...       " << std::flush;
		state = convertNessusResults();
		showResult(state);
	}
	if(state) { // Loading target informations
		std::cout << COL_B << " * " << COL_NONE << "Loading target informations...     " << std::flush;
		state = loadTargetInformations();
		showResult(state);
	}
	if(state) { // Displaying remote host informations
		std::cout << COL_B << " * " << COL_NONE << "Remote host informations :         " << std::flush;
		showResult(state);
		
		std::cout << "    - IP address          : " << COL_B << _remote_host->getIpAddress() 
			<< COL_NONE << std::endl;
		std::cout << "    - Platform            : " << COL_B;
		if(strlen(_remote_host->getPlatform()->getName().c_str()) > 0) {
			std::cout << _remote_host->getPlatform()->getName();
			std::cout << " " << _remote_host->getPlatform()->getDistributions()->operator [](0);
		} else {
			std::cout << "unknown";
		}
		std::cout << COL_NONE << std::endl;
		std::cout << "    - Identified services : " << COL_B << _target_infos_handler->getTargetNbIdentifiedServices()
			<< COL_NONE << std::endl;
		std::cout << getServicesList() << std::endl;
	}
	testSuccess(state);
	
	// 2 - Searching for entries in database
	if(state) {
		showCategory(2, "Searching for entries in database...");
		std::cout << COL_B << " * " << COL_NONE << "Database total vulnerabilities : " << std::flush;
		VulnerabilitiesSearcher *db = new VulnerabilitiesSearcher();
		std::cout << COL_B << db->getNbTotalVulnerabilities() << COL_NONE << std::endl;
		free(db);
		
		std::cout << COL_B << " * " << COL_NONE << "Corresponding vulnerabilities  : " << std::flush;
		state = searchVulnerabilitiesDatabase();
		std::cout << COL_B << _vulnerabilities->count() << COL_NONE << std::endl;
		
		if(state) { // Searching for exploits entries
			std::cout << COL_B << " * " << COL_NONE << "Database total exploits        : " << std::flush;
			ExploitsSearcher *db = new ExploitsSearcher();
			std::cout << COL_B << (int)db->getNbTotalExploits() << COL_NONE << std::endl;
			free(db);
			
			std::cout << COL_B << " * " << COL_NONE << "Corresponding exploits         : " << std::flush;
			state = searchExploitsDatabase();
			std::cout << COL_B << _exploits->count() << COL_NONE << std::endl;
		}
		testSuccess(state);
	}
	
	// 3 - Using exploits to attack the target
	if(state) {
		showCategory(3, "Using exploits to attack the target...");
		state = tryAttacks();
		testSuccess(state);
	}
	
	// 4 - Displaying result of the attacks
	if(state) {
		showCategory(4, "Attack results :");
		showVictory();
	}
	
	getLogger().debug("Breaker : execute() - end");
}

/**
 * Outputs a category message with colors
 */
void Breaker::showCategory(int num, const char *msg) {
	std::cout << COL_BRED << "[" << num << "]" << COL_B << " - " << msg << COL_NONE << std::endl;
}

/**
 * Tests if an action was successful or not and weither the program has to
 * quit on unsuccessful action
 */
void Breaker::testSuccess(bool success) {
	if(success) {
		std::cout << COL_BGREEN << " ** SUCCESSFUL **" << COL_NONE << std::endl << std::endl;
	} else {
		std::cout << COL_BRED << " ** UNSUCCESSFUL **" << COL_NONE << std::endl << std::endl;
	}
}

/**
 * Outputs whether a step succeeded or not
 */
void Breaker::showResult(bool success) {
	if(success) {
		std::cout << COL_BGREEN << "[OK]" << COL_NONE << std::endl;
	} else {
		std::cout << COL_BRED   << "[KO]" << COL_NONE << std::endl;
	}
}

/**
 * Searches for informations about the remote computer
 */
bool Breaker::searchInformations() {
	getLogger().debug("Breaker : searchInformations() - begin");
	char script[80];
	strcpy (script, "src/modules/scanner/nessus ");
	strcat (script, _remote_host->getIpAddress().c_str());
	int result = 0;//system(script);
	
	getLogger().debug("Breaker : searchInformations() - end");
	return result == 0;
}

/**
 * Converts the output file of the Nessus tests
 */
bool Breaker::convertNessusResults() {
	getLogger().debug("Breaker : convertNessusResults() - begin");
	
	bool result = true;//_target_infos_handler->transformNessusResults();
	
	getLogger().debug("Breaker : convertNessusResults() - end");
	return result;
}

/**
 * Loads the target informations such as the remote platform used
 */
bool Breaker::loadTargetInformations() {
	getLogger().debug("Breaker : loadTargetInformations() - begin");
	
	bool result = _target_infos_handler->checkInformationsValidity();
	_remote_host->setPlatform(_target_infos_handler->getTargetPlatform());
	_services = _target_infos_handler->getTargetServices();
	
	getLogger().debug("Breaker : loadTargetInformations() - end");
	return result;
}

/**
 * Searches the presence of the corresponding vulnerabilities in database
 */
bool Breaker::searchVulnerabilitiesDatabase() {
	getLogger().debug("Breaker : searchVulnerabilitiesDatabase() - begin");
	
	bool result;
	VulnerabilitiesSearcher *searcher = new VulnerabilitiesSearcher();
	_vulnerabilities = searcher->search(_services);
	result = _vulnerabilities->count() > 0;
	free(searcher);
	
	getLogger().debug("Breaker : searchVulnerabilitiesDatabase() - end");
	return result;
}

/**
 * Searches the presence of the corresponding exploits in database
 */
bool Breaker::searchExploitsDatabase() {
	getLogger().debug("Breaker : searchExploitsDatabase() - begin");
	
	bool result;
	ExploitsSearcher *searcher = new ExploitsSearcher();
	_exploits = searcher->search(_vulnerabilities);
	result = _exploits->count() > 0;
	free(searcher);
	
	getLogger().debug("Breaker : searchExploitsDatabase() - end");
	return result;
}

/**
 * Tries attacking the remote computer with exploiting attacks
 */
bool Breaker::tryAttacks() {
	getLogger().debug("Breaker : tryAttacks() - begin");
	bool result = true;
	
	// xxx
	/*
	TCollection<Attack*> *colAttacks = new TCollection<Attack*>();
	Attack *att1 = new Attack(1, NULL, "success", "", "1st testing attack", "c", "", "int main(void) { printf(\"success\"); } ");
	Attack *att2 = new Attack(2, NULL, "", "Atta.*!", "2nd testing attack", "c", "{EXPLOIT} {IP}", "int main(int argc, char *argv[]) { printf(\"Attaque de [%s] !\", argv[1]); return 0; } ");
	colAttacks->add(att1);
	colAttacks->add(att2);
	_exploits->clear();
	_exploits->add(new Exploit("1", "bob", "description", colAttacks));
	*/
	// xxx
	
	// loops on all the exploits
	for(int e=0; e<_exploits->count() && result; e++) {
		Exploit *exploit = _exploits->operator [](e);
		std::cout << COL_B << " * " << COL_NONE << "Trying exploit " << e+1 << "/" << _exploits->count() << " : " << COL_NONE << std::endl;
		TCollection<Attack *> *attacks = exploit->getAttacks();
		bool result_tmp = true;
		getLogger().debug("    %s", exploit->toString().c_str());
		// loops on all the attacks
		for(int a=0; a<attacks->count() && result_tmp; a++) {
			Attack *attack = attacks->operator [](a);
			std::cout << COL_B << "  " << attack->getNum() << " - " << COL_NONE << attack->getType() << " : " << std::flush;
			result_tmp = attack->run(_remote_host->getIpAddress()/*, __port__*/);
			showResult(result_tmp);
		}
		result = result_tmp;
	}
	getLogger().debug("Breaker : tryAttacks() - end");
	return result;
}

void Breaker::showVictory() {
	getLogger().debug("Breaker : showVictory() - begin");
	
	std::cout << COL_BLUE << "***************************************************" << std::endl;
	std::cout << COL_BLUE << "*" << COL_NONE << " The distant host has been successfully attacked " << COL_BLUE << "*" << std::endl;
	std::cout << COL_BLUE << "*" << COL_NONE << "               You are " << COL_B << "victorious!" << COL_NONE << "               " << COL_BLUE << "*" << std::endl;
	std::cout << COL_BLUE << "***************************************************" << COL_NONE << std::endl << std::endl;
	
	getLogger().debug("Breaker : showVictory() - end");
}

/*
std::string Breaker::getServicesPortsList() {
	std::ostringstream oss;
	for(int i=0; i<_services->count(); i++) {
		if(i>0) oss << ", ";
		oss << _services->operator [](i)->getPort();
	}
	return oss.str();
}

std::string Breaker::getServicesNamesList() {
	std::ostringstream oss;
	for(int i=0; i<_services->count(); i++) {
		if(i>0) oss << ", ";
		oss << _services->operator [](i)->getName();
	}
	return oss.str();
}
*/
std::string Breaker::getServicesList() {
	std::ostringstream oss;
	for(int i=0; i<_services->count(); i++) {
		Service *s = _services->operator [](i);
		if(i>0) oss << ", ";
		oss << s->getProtocol() << "/" << s->getName() << ":" << s->getPort();
	}
	return oss.str();
}
