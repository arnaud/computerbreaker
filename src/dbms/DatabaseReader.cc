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

#include "DatabaseReader.hh"
#include <iostream>
#include "../util/Logger.hh"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_USE

const char *DatabaseReader::dbVulnerabilities = "db/vuln.xml";
const char *DatabaseReader::dbExploits = "db/expl.xml";
const char *DatabaseReader::dbExploitsImpl = "db/expl/";

/**
 * Constructor : creates a DatabaseReader with a databaseFileName chosen between:
 * - dbVulnerabilities
 * - dbExploits
 * - cbExploitsImpl + ...
 */
DatabaseReader::DatabaseReader(const char *database_file_name){
	setDatabaseFileName(database_file_name);
}

/**
 * Deconstructor
 */
DatabaseReader::~DatabaseReader(){
	delete _parser;
}

/**
 * Sets the databaseFileName and parses it, validates it and catches any exception that could occur
 */
void DatabaseReader::setDatabaseFileName(const char *database_file_name){
	_database_file_name = database_file_name;
	
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		getLogger().error("%s : %s - %s : databaseFileName='%s'", "DatabaseReader", "setDatabaseFileName()", message, _database_file_name);
        XMLString::release(&message);
    }
	
    _parser = new XercesDOMParser();
    _parser->setValidationScheme(XercesDOMParser::Val_Always);  // optional
    _parser->setDoNamespaces(true);  // optional
    
    _errHandler = (ErrorHandler*) new HandlerBase();
    _parser->setErrorHandler(_errHandler);
    
    try {
        _parser->parse(_database_file_name);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		getLogger().error("%s : %s - %s : databaseFileName='%s'", "DatabaseReader", "setDatabaseFileName()", message, _database_file_name);
        XMLString::release(&message);
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
		getLogger().error("%s : %s - %s : databaseFileName='%s'", "DatabaseReader", "setDatabaseFileName()", message, _database_file_name);
        XMLString::release(&message);
    }
    catch (...) {
		getLogger().error("%s : %s - %s : databaseFileName='%s'", "DatabaseReader", "setDatabaseFileName()", "Unexpected Exception", _database_file_name);
    }

	getLogger().debug("%s : %s - %s", "DatabaseReader", "setDatabaseFileName()", "Parsing success");
    
    delete _errHandler;
}

/**
 * Gets the databaseFileName
 */
const char* DatabaseReader::getDatabaseFileName(){
	return _database_file_name;
}

/**
 * Gets the Root Node of the current database file
 */
DOMElement *DatabaseReader::getRootElement(){
	return _parser->getDocument()->getDocumentElement();
}
