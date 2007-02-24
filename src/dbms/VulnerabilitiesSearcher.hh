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

#ifndef VULNERABILITIESSEARCHER_HH_
#define VULNERABILITIESSEARCHER_HH_

#include "DatabaseReader.hh"
#include "../models/Service.hh"
#include "../models/Vulnerability.hh"
#include "../util/TCollection.hh"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

/**
 * VulnerabilitiesSearcher class
 */
class VulnerabilitiesSearcher {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	const char *_database;
	XERCES_CPP_NAMESPACE::DOMElement *_root;
	
	// -----------------------------------------------------------------------
    //  Private methods
    // -----------------------------------------------------------------------

    /** @name Private methods */
    //@{
    /**
     *
     */
	TCollection<Vulnerability*> *search(Service *service);
	//@}
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct 
      */
	VulnerabilitiesSearcher();
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~VulnerabilitiesSearcher();
	//@}
	
	// -----------------------------------------------------------------------
    //  Public methods
    // -----------------------------------------------------------------------

    /** @name Public methods */
    //@{
    /**
     *
     */
	TCollection<Vulnerability*> *search(TCollection<Service*> *services);
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    /**
     *
     */
	int getNbTotalVulnerabilities();
	//@}
};

#endif /*VULNERABILITIESSEARCHER_HH_*/
