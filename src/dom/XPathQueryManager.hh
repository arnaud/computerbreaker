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

#ifndef XPATHQUERYMANAGER_HH_
#define XPATHQUERYMANAGER_HH_

#include <string>
//#include <xalanc/XPath/NodeRefListBase.hpp>
#include <xalanc/XalanDOM/XalanDOMString.hpp>
#include <xalanc/XalanDOM/XalanNode.hpp>
#include "../models/Exploit.hh"
#include "../models/Service.hh"
#include "../models/Vulnerability.hh"
#include "../models/Platform.hh"


/**
 * The XPathQueryManager class is used in order to execute XPath
 * queries in a particular file.
 */
class XPathQueryManager {
  private:
  	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	std::string _file_name;
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct 
      */
	XPathQueryManager(std::string file_name);
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    /**
     *
     */
	const std::string getXpathResultString(const std::string xPathQuery, const std::string contextNode = "/");
	
	/**
     *
     */
	const std::string getXpathResultStringMultiple(const std::string xPathQuery, const std::string contextNode = "/");
  	
  	/**
     *
     */
  	double getXpathResultDouble(const std::string xPathQuery, const std::string contextNode = "/");
  	
  	/**
     *
     */
  	TCollection<Service*> *getXpathResultServices(const std::string xPathQuery, const std::string contextNode = "/");
  	
  	/**
     *
     */
  	TCollection<Vulnerability*> *getXpathResultVulnerabilities(const std::string xPathQuery, const std::string contextNode = "/");
  	
  	/**
     *
     */
  	TCollection<Exploit*> *getXpathResultExploits(const std::string xPathQuery, const std::string contextNode = "/");
  	
  	/**
     *
     */
  	XALAN_CPP_NAMESPACE::XalanNode *getNodeChild(const XALAN_CPP_NAMESPACE::XalanNode *parentNode, const std::string name);
  	
  	/**
     *
     */
  	std::string getAttributeByName(const XALAN_CPP_NAMESPACE::XalanNode *node, const std::string attributeName);
  	//@}
	
	// -----------------------------------------------------------------------
    //  Public methods
    // -----------------------------------------------------------------------

    /** @name Public methods */
    //@{
    /**
     *
     */
  	static std::string convertToString(const XALAN_CPP_NAMESPACE::XalanDOMString xalanString);
  	//@}

};

#endif /*XPATHQUERYMANAGER_HH_*/
