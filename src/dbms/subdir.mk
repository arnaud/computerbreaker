# This file is part of the Computer Breaker project.
#
#    Computer Breaker is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    Computer Breaker is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Computer Breaker; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

CC_SRCS += \
${SRC}/dbms/DatabaseReader.cc \
${SRC}/dbms/VulnerabilitiesSearcher.cc \
${SRC}/dbms/ExploitsSearcher.cc

OBJS += \
${OUT}/dbms/DatabaseReader.o \
${OUT}/dbms/VulnerabilitiesSearcher.o \
${OUT}/dbms/ExploitsSearcher.o

CC_DEPS += \
${OUT}/dbms/DatabaseReader.d \
${OUT}/dbms/VulnerabilitiesSearcher.d \
${OUT}/dbms/ExploitsSearcher.d
