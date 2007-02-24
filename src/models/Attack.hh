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


#ifndef ATTACK_HH_
#define ATTACK_HH_

#include <string>
#include "../util/TCollection.hh"

/** 
* @class Attack
*
* @brief Attack model class
*
* Detailed description starts here.
*  
* @author CBTeam
* 
*/
class Attack {
  private:
	std::string _ip_address;
	//int _port;
	
	int _num;
	TCollection<Attack*> *_dependancies;
	std::string _successful_return_value;
	std::string _successful_regex_return_value;
	std::string _type;
	std::string _language;
	std::string _command;
	std::string _code;
	
	// -----------------------------------------------------------------------
    //  Private Methods
    // -----------------------------------------------------------------------
	/**
      * Compilateur du scenario d'attaque
      * 
      * Cette méthode permet de charger le scenario d'attaque de la base et de le compiler
      */
	void compile();
	/**
      * Execute l'attaque
      * 
      * Cette méthode permet de lancer l'exploit avec une redirection dans stdout
      * 
      */
	std::string execute();
	void clean();
	bool isAttackSuccess(std::string execResult);
	const char *getCodeFileName();
	
  public:
	// -----------------------------------------------------------------------
    //  Constructors and Detructor
    // -----------------------------------------------------------------------
	/** @name Constructors */
    //@{
    
    /**
      * Construct an Attack with Empty attribute
      */
	Attack();
	/** Construct an Attack with Predefine element
      *
      * Constructor with the 
      * 
      *
      * @param num 
      *
      * @param dependancies   
      *
      * @param successful_return_value
      * 
      * @param successful_regex_return_value
      * 
      * @param type
      * 
      * @param language
      * 
      * @param command
      * 
      * @param code
      */
	Attack(int num, TCollection<Attack*> *dependancies, std::string successful_return_value,
		std::string successful_regex_return_value, std::string type, std::string language,
		std::string command, std::string code);
	/** Construct an Attack with an Attack in parameters
      *
      * 
      * @param Attack The Attack
      */	
	Attack(const Attack&);
	
	//@}
	
	/** @name Destructor */
    //@{
    
    /**
      * Destructor
      */
	~Attack();
	//@}
	
	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{
    
    /** Get the num of the Attack
      *
      * This method returns the num of the Attack.
      *
      *
      * @return The num.
      */
	int getNum();
	TCollection<Attack*> *getDependancies();
	std::string getSuccessfulReturnValue();
	std::string getSuccessfulRegExReturnValue();
	std::string getType();
	std::string getLanguage();
	std::string getCommand();
	std::string getCode();
	//@}
	
	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    /** @name Setter methods */
    //@{
    
    /** Set the num of the Attack
      *
      * This method allows users to set the num of the Attack.
      *      
      * @param num The value specifying whether num rules should
      *                 be the num of the Attack.
      *
      */
	void setNum(int num);
	void setDependancies(TCollection<Attack*> *dependancies);
	void setSuccessfulReturnValue(std::string successful_return_value);
	void setSuccessfulRegExReturnValue(std::string successful_regex_return_value);
	void setType(std::string type);
	void setLanguage(std::string language);
	void setCommand(std::string command);
	void setCode(std::string code);
	//@}
	
	/* public methods */
	bool run(std::string ip_address/*, int port*/);
	std::string toString();
};

#endif /*ATTACK_HH_*/
