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

#include "TargetInformationsHandler.hh"
#include "../dom/XalanTransform.hh"
#include "../dom/XPathQueryManager.hh"
#include <boost/regex.hpp>
#include <string>


#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/XObject.hpp>
#include <xalanc/PlatformSupport/XSLException.hpp>
#include <xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp>

#include <xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
//#include <xalanc/XalanSourceTree/XalanSourceTreeInit.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeParserLiaison.hpp>

#include <iostream>
#include <vector>

//#include <cassert>



#include "../util/Logger.hh"

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XPathEvaluator)


TargetInformationsHandler::TargetInformationsHandler() {
	
	_xml_file_path = "results.xml";
	
	/* définition des requetes xpath */
	_platform_name_query = "result/system/data/text()";
	_distribution_name_query = "result/host/@ip";
	
	_services_nodeset_query = "result/host/ports/port";
	
}

TargetInformationsHandler::~TargetInformationsHandler() {

}


bool TargetInformationsHandler::transformNessusResults() {
	XalanTransform transformer;
	int result = transformer.transform("nessus_output", "bdd/transform.xsl", "results.xml");
	return result == 0;
}



bool TargetInformationsHandler::checkInformationsValidity() {
	getLogger().debug("TargetInformationsHandler : checkInformationsValidity() - begin");
	bool result;
	result = (getTargetNbOpenPorts()) > 0;
	getLogger().debug("TargetInformationsHandler : checkInformationsValidity() - end");
	return result;
}

/**
 * Trim a String by removing all the ' ', '\n' and `9` characters from both beginning and ending
 */
/*void trim(std::string& str, const char rem)
{
  std::string::size_type pos = str.find_last_not_of(rem);
  if(pos != std::string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(rem);
    if(pos != std::string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}*/

/*bool startsWith(std::string str1, const char *search)
{
        if (!std::strncmp(str1.c_str(), search, std::strlen(search) )) // if (strncmp() == 0)
                return true;
        else
                return false;
}*/

/**
 * récupere les données necessaires a la description de la platforme
 * - nom
 * - distributions associés
 *  
 **/
Platform *TargetInformationsHandler::getTargetPlatform() {
	getLogger().debug("TargetInformationsHandler : getTargetPlatform() - begin");
	
	// Get the system platform informations
	
	XPathQueryManager *queryManager = new XPathQueryManager(_xml_file_path);
	std::string system = queryManager->getXpathResultString("text()", "/result/system");
	
	// Formating the result
	
	std::string name;
	std::string distribution;
	
	//1-remove the weird characters
	boost::regex pattern("[^A-Za-z0-9[:blank:]\\-\\'\\.\\:]");
	system = boost::regex_replace(system, pattern, " ");
	//2-format the blanks
	pattern = "[[:blank:]]{2,}";
	system = boost::regex_replace(system, pattern, "|");
	//3-split the result parts and gets the informations (if multiple operating systems)
	char *substr = strtok ((char *)system.c_str(),"|");
	bool multipleDistributions = false;
	while (substr != NULL) { // iterate the tokens of the splitted string
		std::string theString = substr;
		if(strcmp(theString.c_str(), "The remote host is running one of these operating systems :") == 0) {
			// do nothing
		} else if(strcmp(theString.c_str(), "The remote host is running ") == 0) {
			// do nothing
		} else if(theString.length()>0) {
			if(theString.find("Microsoft ")==0) { // removes the 'Microsoft' string if present
				theString = theString.substr(10, system.length() - 10);
			}
			if(name.length()==0) { // get the name
				name = theString.substr(0, theString.find(' '));
			}
			if(distribution.length()==0) { // get the first distribution
				distribution = theString.substr(theString.find(' ')+1, theString.length() - theString.find(' '));
			} else { // get the other distributions
				multipleDistributions = true;
				distribution.append(", ");
				distribution.append(theString.substr(theString.find(' ')+1, theString.length() - theString.find(' ')));
			}
		}
		getLogger().debug("TargetInformationsHandler : getTargetPlatform() - substring : %s", theString.c_str());
		substr = strtok (NULL, "|");
	}
	if(multipleDistributions && distribution.length()>0) { //format the distributions
		distribution = "[" + distribution + "]";
	}
	//4-get the operating system informations if unique
	system = system.substr(28, system.length() - 29);
	if(system.find("Microsoft ")==0) { // removes the 'Microsoft' string if present
		system = system.substr(10, system.length() - 10);
	}
	name = system.substr(0, system.find(' '));
	distribution = system.substr(system.find(' ')+1, system.length() - system.find(' '));
	
	Platform *platform = new Platform();
	
	platform->setName(name);
	getLogger().info("TargetInformationsHandler : getTargetPlatform() - %s", name.c_str());
	
	platform->getDistributions()->add(distribution);
	getLogger().info("TargetInformationsHandler : getTargetPlatform() - %s", distribution.c_str());
	
	getLogger().debug("TargetInformationsHandler : getTargetPlatform() - end");
	return platform;
}

/**
 * récupere les services actifs sur la machine distante.
 * 
 * */
TCollection<Service*> *TargetInformationsHandler::getTargetServices() {
	getLogger().debug("TargetInformationsHandler : getTargetServices() - begin");
	TCollection<Service*> *services = new TCollection<Service*>();
	 
	XALAN_USING_XALAN(NodeRefListBase)
	XALAN_USING_XALAN(XalanNode)
	
	XPathQueryManager *queryManager = new XPathQueryManager(_xml_file_path);
	services = queryManager->getXpathResultServices("result/ports/port");

	getLogger().debug("TargetInformationsHandler : getTargetServices() - end");
	return services;
}


int TargetInformationsHandler::getTargetNbIdentifiedServices() {
	getLogger().debug("TargetInformationsHandler : getTargetNbIdentifiedServices() - begin");
	XPathQueryManager queryManager(_xml_file_path);
	int result = (int)queryManager.getXpathResultDouble("count(port/service[@name!='unknown'])", "/result/ports");
	getLogger().info("TargetInformationsHandler : getTargetNbIdentifiedServices() - %d", result);
	getLogger().debug("TargetInformationsHandler : getTargetNbIdentifiedServices() - end");
	return result;
}


int TargetInformationsHandler::getTargetNbOpenPorts() {
	getLogger().debug("TargetInformationsHandler : getTargetNbOpenPorts() - begin");
	XPathQueryManager queryManager(_xml_file_path);
	int result = (int)queryManager.getXpathResultDouble("count(port)", "/result/ports");
	getLogger().info("TargetInformationsHandler : getTargetNbOpenPorts() - %d", result);
	getLogger().debug("TargetInformationsHandler : getTargetNbOpenPorts() - end");
	return result;
}
