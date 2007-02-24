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

#include <log4cpp/BasicLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#include "Logger.hh"

static bool logInit = false;

/**
 * Returns the logger and initializes it if needed
 */
log4cpp::Category& getLogger() {
	
	if (logInit)
		return log4cpp::Category::getInstance("CB");
	
	// 1. instantiate an appender object.
	log4cpp::Appender* app = new log4cpp::FileAppender("FileAppender", "computer-breaker.log");
	
	// 2. Instantiate a layout object, which tells how to
	// format the log.
	log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
	layout->setConversionPattern("%d %p : %m%n");
	
	// 3. attach the layout object to the appender object
	app->setLayout(layout);
	
	// 4.
	log4cpp::Category::getInstance("CB").setAdditivity(false);
	log4cpp::Category::getInstance("CB").setAppender(app);
	
	// 5. Set up the priority for the category
	log4cpp::Category::getInstance("CB").setPriority(log4cpp::Priority::DEBUG);
	
	logInit = true;
	return log4cpp::Category::getInstance("CB");
}
