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
${SRC}/models/Service.cc \
${SRC}/models/Vulnerability.cc \
${SRC}/models/Platform.cc \
${SRC}/models/Exploit.cc \
${SRC}/models/Attack.cc \
${SRC}/models/RemoteHost.cc

OBJS += \
${OUT}/models/Service.o \
${OUT}/models/Vulnerability.o \
${OUT}/models/Platform.o \
${OUT}/models/Exploit.o \
${OUT}/models/Attack.o \
${OUT}/models/RemoteHost.o

CC_DEPS += \
${OUT}/models/Service.d \
${OUT}/models/Vulnerability.d \
${OUT}/models/Platform.d \
${OUT}/models/Exploit.d \
${OUT}/models/Attack.d \
${OUT}/models/RemoteHost.d
