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

#ifndef DATABASEREADER_HH_
#define DATABASEREADER_HH_

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

/**
 * DatabaseReader class
 */
class DatabaseReader {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	const char *_database_file_name;
	XERCES_CPP_NAMESPACE::XercesDOMParser *_parser;
	XERCES_CPP_NAMESPACE::ErrorHandler *_errHandler;
	
  public:
  	// -----------------------------------------------------------------------
    //  Static Attributes
    // -----------------------------------------------------------------------
	static const char *dbVulnerabilities;
	static const char *dbExploits;
	static const char *dbExploitsImpl;
	
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct 
      */
	DatabaseReader(const char *database_file_name = DatabaseReader::dbVulnerabilities);
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~DatabaseReader();
	//@}
	
	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    /** @name Setter methods */
    //@{
    /**
     *
     */
	void setDatabaseFileName(const char *database_file_name);
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    /**
     *
     */
	const char *getDatabaseFileName();
	XERCES_CPP_NAMESPACE::DOMElement *getRootElement();
	//@}
};

#endif /*DATABASEREADER_HH_*/
