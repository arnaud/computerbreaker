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

RM := rm -rf
SRC := src
OUT := out
BIN := bin
CB_VERSION := 0.2
KMA_VERSION := 0.1
BUF1_VERSION := 0.1
BUF2_VERSION := 0.1
HEAP_VERSION := 0.1
FMTD_VERSION := 0.1

# All of the sources participating in the build are defined here
SUBDIRS := src
-include src/subdir.mk
-include src/core/subdir.mk
-include src/dbms/subdir.mk
-include src/dom/subdir.mk
-include src/models/subdir.mk
-include src/util/subdir.mk

# Libraries
LIBS := -lxerces-c -lxalan-c -llog4cpp -lncurses -lboost_regex

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: computerbreaker kma buf1 buf2 heap

# Each subdirectory must supply rules for building sources it contributes
${OUT}/%.o: ${SRC}/%.cc
	@echo 'Building file: $<'
	@g++ -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
${OUT}/%.o: ${SRC}/%.c
	@echo 'Building file: $<'
	@gcc -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Tool invocations
computerbreaker: CreateOutputDirectories $(OBJS)
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/breaker_${CB_VERSION}'
	@g++  -o"${BIN}/breaker_${CB_VERSION}" $(OBJS) $(LIBS)
	@echo 'Finished building target'
	@echo '--------------------------------'

kma: CreateOutputDirectories ${OUT}/services/kmac.o ${OUT}/services/kmas.o
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/kmac_${KMA_VERSION}'
	@gcc  -o"${BIN}/kmac_${KMA_VERSION}" ${OUT}/services/kmac.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/kmas_${KMA_VERSION}'
	@gcc  -o"${BIN}/kmas_${KMA_VERSION}" ${OUT}/services/kmas.o
	@echo 'Finished building target'
	@echo '--------------------------------'

buf1: CreateOutputDirectories ${OUT}/services/buf1_expl.o ${OUT}/services/buf1_vuln.o
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/buf1_expl_${BUF1_VERSION}'
	@gcc  -o"${BIN}/buf1_expl_${BUF1_VERSION}" ${OUT}/services/buf1_expl.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/buf1_vuln_${BUF1_VERSION}'
	@gcc  -o"${BIN}/buf1_vuln_${BUF1_VERSION}" ${OUT}/services/buf1_vuln.o
	@echo 'Finished building target'
	@echo '--------------------------------'

buf2: CreateOutputDirectories ${OUT}/services/buf2_expl.o ${OUT}/services/buf2_vuln.o
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/buf2_expl_${BUF2_VERSION}'
	@gcc  -o"${BIN}/buf2_expl_${BUF2_VERSION}" ${OUT}/services/buf2_expl.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/buf2_vuln_${BUF2_VERSION}'
	@gcc  -o"${BIN}/buf2_vuln_${BUF2_VERSION}" ${OUT}/services/buf2_vuln.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	
heap: CreateOutputDirectories ${OUT}/services/heap_expl.o ${OUT}/services/heap_vuln.o
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/heap_expl_${HEAP_VERSION}'
	@gcc  -o"${BIN}/heap_expl_${HEAP_VERSION}" ${OUT}/services/heap_expl.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/heap_vuln_${HEAP_VERSION}'
	@gcc  -o"${BIN}/heap_vuln_${HEAP_VERSION}" ${OUT}/services/heap_vuln.o
	@echo 'Finished building target'
	@echo '--------------------------------'

fmtd: CreateOutputDirectories ${OUT}/services/fmtd.o ${OUT}/services/expl-fmtd.o
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/fmtd_${FMTD_VERSION}'
	@gcc  -o"${BIN}/fmtd_${FMTD_VERSION}" ${OUT}/services/fmtd.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	@echo 'Building target: ${BIN}/expl-fmtd_${FMTD_VERSION}'
	@gcc  -o"${BIN}/expl-fmtd_${FMTD_VERSION}" ${OUT}/services/expl-fmtd.o
	@echo 'Finished building target'
	@echo '--------------------------------'
	
# Other Targets
clean:
	@echo 'Cleaning...'
	@${RM} ${OUT}
	@echo 'Finished cleaning'

CreateOutputDirectories:
	@echo 'Creating output directories : ${OUT}'
	@mkdir -p ${OUT}/core
	@mkdir -p ${OUT}/dbms
	@mkdir -p ${OUT}/dom
	@mkdir -p ${OUT}/models
	@mkdir -p ${OUT}/modules
	@mkdir -p ${OUT}/services
	@mkdir -p ${OUT}/util
	@echo 'Finished creating output directories'
	@echo ' '

.PHONY: all clean dependents
.SECONDARY:
