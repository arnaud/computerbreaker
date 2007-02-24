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

#ifndef SERVICE_HH_
#define SERVICE_HH_

#include <string>
#include "Vulnerability.hh"
#include "../util/TCollection.hh"

/** 
* @class Service
*
* @brief Service model class
*
* Detailed description starts here.
*  
* @author CBTeam
* 
*/
class Service {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	int _id;
	std::string _name;
	int _port;
	std::string _protocol;
	TCollection<Vulnerability*> *_vulnerabilities;
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct a Service with Empty attribute
      */
	Service();
	/** Construct a Service with Predefine element
      *
      * Constructor with the id, the name, the port and the vulnerabilities of the Service
      * 
      *
      * @param id The ID of the Service
      * 
      * @param name The name of the Service
      *
      * @param port The port of the Service   
      *
      * @param vulnerabilities The collection of vulnerabilities associate with this Service
      */
	Service(int id, std::string name, int port, std::string _protocol,
		TCollection<Vulnerability*> *vulnerabilities);
	/** Construct a Service with a Service in parameters
      *
      * 
      * @param Service The Service
      */
	Service(const Service&);
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~Service();
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    
    /** Get the Id of the service
      *
      * This method returns the id of the service.
      *
      *
      * @return The id.
      */
	int getId();
	/** Get the name of the service
      *
      * This method returns the name of the service.
      *
      *
      * @return The name.
      */
	std::string getName();
	/** Get the port of the service
      *
      * This method returns the port of the service.
      *
      *
      * @return The port.
      */
	int getPort();
	/** Get the protocol of the service
      *
      * This method returns the protocol of the service.
      *
      *
      * @return The protocol.
      */
	std::string getProtocol();
	/** Get a collection of vulnerabilities associate with this service
      *
      * This method returns a collection of vulnerabilities associate with this service.
      *
      *
      * @return The collection of vulnerabilities associate with this service.
      */
	TCollection<Vulnerability*> *getVulnerabilities();
	//@}
	
	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    /** @name Setter methods */
    //@{
    
    /** Set the Id of the service
      *
      * This method allows users to set the Id of the service.
      *      
      * @param id The value specifying the Id of the service.
      *
      */
	void setId(int id);
	/** Set the name of the service
      *
      * This method allows users to set the name of the service.
      *      
      * @param name The value specifying the name of the service.
      *
      */
	void setName(std::string name);
	/** Set the port of the service
      *
      * This method allows users to set the port of the service.
      *      
      * @param port The value specifying the port of the service.
      *
      */
	void setPort(int port);
	/** Set the protocol of the service
      *
      * This method allows users to set the protocol of the service.
      *      
      * @param protocol The value specifying the protocol of the service.
      *
      */
	void setProtocol(std::string protocol);
	/** Set a collection of vulnerabilities associate with this service
      *
      * This method allows users to set a collection of vulnerabilities associate with this service.
      *      
      * @param vulnerabilities The value specifying whether vulnerabilities rules should
      *                 be a collection of vulnerabilities associate with this service.
      *
      */
	void setVulnerabilities(TCollection<Vulnerability*> *vulnerabilities);
	//@}
	
	/* public methods */
	std::string toString();
};

#endif /*SERVICE_HH_*/
