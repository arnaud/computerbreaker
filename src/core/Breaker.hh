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

#ifndef BREAKER_HH_
#define BREAKER_HH_

#include "TargetInformationsHandler.hh"
#include "../models/Exploit.hh"
#include "../models/RemoteHost.hh"
#include "../models/Service.hh"
#include "../models/Vulnerability.hh"
#include "../util/TCollection.hh"

/**
 * Computer Breaker Core class
 */
class Breaker {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	RemoteHost *_remote_host;
	TargetInformationsHandler *_target_infos_handler;
	TCollection<Service*> *_services;
	TCollection<Vulnerability*> *_vulnerabilities;
	TCollection<Exploit*> *_exploits;
	
	
	// -----------------------------------------------------------------------
    //  Private Methods
    // -----------------------------------------------------------------------
    /**
 	* Outputs a category message with colors
 	*/
	void showCategory(int num, const char *msg);
	
	/**
 	* Tests if an action was successful or not and weither the program has to
 	* quit on unsuccessful action
 	*/
	void testSuccess(bool success);
	
	/**
 	* Outputs whether a step succeeded or not
 	*/
	void showResult(bool success);
	
	/**
 	* Searches for informations about the remote computer
 	* 
 	* Execute the script of use of Nessus
 	*/
	bool searchInformations();
	
	/**
 	* Converts the output file of the Nessus tests
 	* 
 	* Use the TargetInformationHandler to transform 
 	* the XML schema (appr 5Mo) into a new reduce XML schema
 	* @see TargetInformationsHandler#transformNessusResults
 	*/
	bool convertNessusResults();
	
	/**
 	* Loads the target informations such as the remote platform used
 	* 
 	* Perform an operation to initialize the information about the remote host:
 	* 
 	* Control the information obtain with Nessus
 	* 
 	* Initialize the RemoteHost
 	* 
 	* Initialize the Service
 	* 
 	* @see TargetInformationsHandler#checkInformationsValidity
 	* @see RemoteHost#setPlatform
 	*/
	bool loadTargetInformations();
	
	/**
 	* Searches the presence of the corresponding vulnerabilities in database
 	*/
	bool searchVulnerabilitiesDatabase();
	
	/**
 	* Searches the presence of the corresponding exploits in database
 	*/
	bool searchExploitsDatabase();
	
	/**
 	* Tries attacking the remote computer with exploiting attacks
 	*/
	bool tryAttacks();
	
	/**
	 * Show the result of the exploiting attacks when success
	 */
	void showVictory();
	
  public:
    // -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct the Breaker 
      * - defines the IP Address of the remote computer
      */
	Breaker(const char* ip_address = "127.0.0.1");
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~Breaker();
	//@}
	
	// -----------------------------------------------------------------------
    //  Public methods
    // -----------------------------------------------------------------------

    /** @name Public methods */
    //@{
    /**
 	* Executes attacking the remote computer
 	* 
 	* This public methods progress with successive stage:
 	* 
 	* - Searching for target informations
 	* 		@see #searchInformations -- Launching Nessus  
 	* 		@see #convertNessusResults -- Converting Nessus results 
 	* 		@see #loadTargetInformations -- Loading target informations 
 	* 		@see RemoteHost#getIpAddress Platform#getDistributions TargetInformationsHandler#getTargetNbOpenPorts TargetInformationsHandler#getTargetNbIdentifiedServices -- Displaying remote host informations (ip address, type of platform, nb of open ports,  nb of indentified services) 
 	* 
 	* - Searching for entries in database
 	* 		@see VulnerabilitiesSearcher#VulnerabilitiesSearcher -- Loading all Vulnerabilities which are in db
 	* 		@see ExploitsSearcher#ExploitsSearcher -- Loading all Exploits which are in db
 	*  
 	* - Using exploits to attack the target
 	* 		@see #tryAttacks -- Tries attacking the remote computer with exploiting attacks
 	*  
 	* - Displaying result of the attacks 
 	* 		@see #showCategory -- 
 	* 		@see #showVictory --
 	*/
	void execute();
	//@}
	std::string getServicesPortsList();
	std::string getServicesNamesList();
	std::string getServicesList();
};

#endif /*BREAKER_HH_*/
