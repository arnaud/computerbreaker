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

#include "VulnerabilitiesSearcher.hh"
#include "../dom/XPathQueryManager.hh"
#include "../util/Logger.hh"


TCollection<Vulnerability*> *VulnerabilitiesSearcher::search(Service *service) {
	getLogger().debug("VulnerabilitiesSearcher : search(Service) - begin");
	
	TCollection<Vulnerability*> *returnedList = new TCollection<Vulnerability*>();
	
	// 1 - Retrieve all the matching vulnerabilities, with the port value
	
	XPathQueryManager *queryM = new XPathQueryManager(DatabaseReader::dbVulnerabilities);
	std::string xpath = "service[port/text()='";
	std::ostringstream oss;
	oss << service->getPort();
	xpath += oss.str();
	xpath += "']";
	getLogger().info("xpath = %s", xpath.c_str());
	TCollection<Vulnerability*> *vulnList = queryM->getXpathResultVulnerabilities(xpath, "/vulnerabilities");
	getLogger().info("vulnList->count() = %d", vulnList->count());
	
	// 2 - Remove from the list those that don't match exactly the identified service
	
	for(int db=0; db<vulnList->count(); db++) { // Iterate the database port-matched vulnerabilities
		std::string db_bug_track = vulnList->operator [](db)->getBugtrackId();
		std::string db_cve_id = vulnList->operator [](db)->getCveId();
		TCollection<Platform *> *db_platforms = vulnList->operator [](db)->getPlatforms();
		TCollection<Vulnerability *> *vulnerabilities = service->getVulnerabilities();
		bool isOk = false;
		// Iterate the identified service vulnerabilities
		for(int rm=0; rm<vulnerabilities->count(); rm++) {
			std::string rm_bug_track = vulnerabilities->operator [](rm)->getBugtrackId();
			std::string rm_cve_id = vulnerabilities->operator [](rm)->getCveId();
			if(db_bug_track.compare(rm_bug_track) == 0 || db_cve_id.compare(rm_cve_id) == 0) {
				isOk = true;
				break;
			}
			// Iterate the platforms
			TCollection<Platform *> *plats = vulnerabilities->operator [](rm)->getPlatforms();
			if(plats->count() > 0) {
				Platform *rm_platform = plats->operator [](0);
				for(int p=0; p<db_platforms->count(); p++) {
					if(rm_platform->getName().compare( db_platforms->operator [](p)->getName() ) == 0) {
						isOk = true;
						break;
					}
				}
			}
			// If the database vulnerability don't know about the platform
			if(db_platforms->count()==0) {
				isOk = true;
			}
			// The Vulnerability matches perfectly! Add it to the returned list
			if(isOk) {
				returnedList->add(vulnList->operator [](db));
			}
		}
	}
	
	getLogger().debug("VulnerabilitiesSearcher : search(Service) - end");
	return returnedList;
}

VulnerabilitiesSearcher::VulnerabilitiesSearcher() {
	_database = DatabaseReader::dbVulnerabilities;
	DatabaseReader dbReader(_database);
	_root = dbReader.getRootElement();
	getLogger().debug("VulnerabilitiesSearcher initialized");
}

VulnerabilitiesSearcher::~VulnerabilitiesSearcher() {
	delete _root;
	getLogger().debug("VulnerabilitiesSearcher deleted");
}

TCollection<Vulnerability*> *VulnerabilitiesSearcher::search(TCollection<Service*> *services) {
	getLogger().debug("VulnerabilitiesSearcher : search(TCollection<Service*>) - begin");
	TCollection<Vulnerability*> *vulnerabilities = new TCollection<Vulnerability*>();
	// loops on all the services
	for(int i=0; i<services->count(); i++) {
		TCollection<Vulnerability*> *vul = search(services->operator [](i));
		// adds the new vulnerabilities of "vul" (if they exist) in the "vulnerabilities" collection
		for(int j=0; j<vul->count(); j++) {
			vulnerabilities->add(vul->operator [](j));
		}
	}
	getLogger().info("vulnerabilities->count() = %d", vulnerabilities->count());
	getLogger().debug("VulnerabilitiesSearcher : search(TCollection<Service*>) - end");
	return vulnerabilities;
}

int VulnerabilitiesSearcher::getNbTotalVulnerabilities() {
	getLogger().debug("VulnerabilitiesSearcher : getNbTotalVulnerabilities() - begin");
	XPathQueryManager queryManager(_database);
	int result = (int)queryManager.getXpathResultDouble("text()", "/vulnerabilities/informations/total-vulnerabilities");
	getLogger().debug("VulnerabilitiesSearcher : getNbTotalVulnerabilities() - end");
	return result;
}
