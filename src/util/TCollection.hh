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

#ifndef TCOLLECTION_H_
#define TCOLLECTION_H_

#include <vector>
#include <string>

template <class TBase>
class TCollection {
  protected:
	//The Vector container that will hold the collection of items
	std::vector<TBase> m_items;
	
  public:
	/**
	 * Adds a new base item to the container and returns its position
	 */
	int add() {
		TBase baseItem;
		m_items.push_back(baseItem);
		return (m_items.size()-1);
	}
	
	/**
	 * Adds an item in the collection
	 */
	void add(TBase item) {
		m_items[add()] = item;
	}
	
	/**
	 * Return the memory address of a specific item
	 */
	TBase* getAddress(int itemKey) {
		return &(m_items[itemKey]);
	}
	
	/**
	 * Removes a specific item from the collection
	 */
	void remove(int itemKey) {
		m_items.erase(getAddress(itemKey));
	}
	
	/**
	 * Clears the collection
	 */
	void clear() {
		m_items.clear();
	}
	
	/**
	 * Returns the number of items in the collection
	 */
	int count() {
		return m_items.size();
	}
	
	//Operator Returning a reference to TBase
	TBase& operator [](int itemKey) {
		return m_items[itemKey];
	}
	
	std::string toString() {
		//TODO
		return "";
	}
};

#endif /*TCOLLECTION_H_*/
