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

#ifndef PLATFORM_HH_
#define PLATFORM_HH_

#include <string>
#include "../util/TCollection.hh"

/** 
* @class Platform
*
* @brief Platform model class
*
* Detailed description starts here.
*  
* @author CBTeam
* 
*/
class Platform {
  private:
	// -----------------------------------------------------------------------
    //  Private Attributes
    // -----------------------------------------------------------------------
	std::string _name;
	TCollection<std::string> *_distributions;
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    /**
      * Construct a Platform with Empty attribute
      */
	Platform();
	/** Construct a Platform with Predefine element
      *
      * Constructor with name and type of distribution of the Platform
      * 
      *
      * @param name The name of the Platform
      *
      * @param distributions The type of distribution of the Platform
      */
	Platform(std::string name, TCollection<std::string> *distributions);
	/** Construct a Platform with a Platform in parameters
      *
      * 
      * @param Platform The Platform
      */
	Platform(const Platform&);
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~Platform();
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    
    /** Get the name of the platform
      *
      * This method returns the name of the platform.
      *
      *
      * @return The name.
      */
	std::string getName();
	/** Get the type of distribution of the platform
      *
      * This method returns the type of distribution of the platform.
      *
      *
      * @return The type of distribution.
      */
	TCollection<std::string> *getDistributions();
	//@}
	
	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    /** @name Setter methods */
    //@{
    
    /** Set the name of the Platform
      *
      * This method allows users to set the name of the Platform.
      *      
      * @param name The value specifying whether name rules should
      *                 be the name of the Platform.
      *
      */
	void setName(std::string name);
	/** Set the type of distribution of the Platform
      *
      * This method allows users to set the type of distribution of the Platform.
      *      
      * @param distributions The value specifying whether type of distribution rules should
      *                 be the type of distribution of the Platform.
      *
      */
	void setDistributions(TCollection<std::string> *distributions);
	//@}
	
	/* public methods */
	std::string toString();
};

#endif /*PLATFORM_HH_*/
