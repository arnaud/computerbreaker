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

#ifndef REMOTEHOST_HH_
#define REMOTEHOST_HH_

#include <string>
#include "Platform.hh"

/** 
* @class RemoteHost
*
* @brief RemoteHost model class
*
* Detailed description starts here.
*  
* @author CBTeam
* 
*/
class RemoteHost {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	std::string _ip_address;
	Platform *_platform;
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    /**
      * Construct a RemoteHost with Empty attribute
      */
	RemoteHost();
	/** Construct a RemoteHost with Predefine element
      *
      * Constructor with the ip address of the RemoteHost
      * 
      *
      * @param ip_address The ip address of the RemoteHost
      */
	RemoteHost(std::string ip_address);
	/** Construct a RemoteHost with Predefine element
      *
      * Constructor with the ip address and the type of platforms of the RemoteHost
      * 
      *
      * @param ip_address The ip address of the RemoteHost
      * 
      * @param platform The type of platforms of the RemoteHost
      */
	RemoteHost(std::string ip_address, Platform *platform);
	//@}
	
	/** @name Destructor */
    //@{
    /**
      * Destructor
      */
	~RemoteHost();
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    /** Get the ip Address of the RemoteHost
      *
      * This method returns the ip address of the RemoteHost.
      *
      *
      * @return The ip address.
      */
	std::string getIpAddress();
    /** Get the type of Platform of the RemoteHost
      *
      * This method returns the type Platform of the RemoteHost.
      *
      *
      * @return The type Platform.
      */
	Platform *getPlatform();
	//@}
	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    /** @name Setter methods */
    //@{
    /** Set the Ip Adress
      *
      * This method allows users to set the Ip Adress of the vulnerability.
      *      
      * @param ip_address The value specifying whether the Ip Adress rules should
      *                 be the Ip Adress of the vulnerability.
      *
      */
	void setIpAddress(std::string ip_address);
	/** Set the Platform
      *
      * This method allows users to set the Platform.
      *      
      * @param platform The value specifying whether platform rules should
      *                 be the Platform.
      *
      */
	void setPlatform(Platform *platform);
	//@}
	
	/* public methods */
	std::string toString();
};

#endif /*REMOTEHOST_HH_*/
