
#==========================================================
#  2D Navier Stokes Equation Solver | Makefile
#  Created      | Sylvain Laizet    | 2014 | Fortran
#  Translated   | Nathanael Jenkins | 2021 | C++
#  Parallelised | Nathanael Jenkins | 2021 | SYCL
#==========================================================
#  Version 3.2
#  Last updated 12.08.2021

#  Source filename
SOURCES = Final.cpp
#  Domain width (square)
DOMAIN = 100
#  Number of timesteps
TIMESTEPS = 100
#  SYCL device type
DEVICE = default
#  Parallel by default (when using parallel compilers)
SERIAL = 0
DPC = 1

#  GNU C++ compiler
CC = g++
CCFLAGS = -std=c++17 -o
CC_OPTFLAGS = -O3
CC_EXE_NAME = 2DSolver_serial

#  oneAPI DPC++ SYCL compiler
DPCPP_CC = dpcpp
DPCPP_CCFLAGS = -std=c++17 -o
DPCPP_OPTFLAGS = -fast
DPCPP_EXE_NAME = 2DSolver_dpc

#  hipSYCL SYCL compiler
SYCL_CC = syclcc
SYCL_CCFLAGS = -std=c++17 -o
SYCL_OPTFLAGS = -O3
SYCL_EXE_NAME = 2DSolver_hip
	
#==========================================================
#  Print make options
.PHONY: help
help:
	@tput setaf 2; tput bold; echo "\nCompiling a 2D Navier-Stokes Solver.\n"; tput sgr0
	@echo "       Make target   Description"
	@echo "------------------------------------------------------------------------------------------"
	@echo "              help   Print this help message"
	@echo "               gnu   Generate executable using g++ compiler (serial only)"
	@echo "               dpc   Generate executable using oneAPI DPC++"
	@echo "               hip   Generate executable using hipSYCL"
	@echo "             clean   Clean existing executables"
	@echo " "
	@echo "           Options   Description"
	@echo "------------------------------------------------------------------------------------------"
	@echo "            DOMAIN   Specify domain width (default: 100)"
	@echo "         TIMESTEPS   Specify number of timesteps (default: 100)"
	@echo "            DEVICE   SYCL device type (default by default)"
	@echo "            SERIAL   (BOOL) Force compiler to use serial code. Does not apply if using GNU."
	@echo "           ADFLAGS   Specify additional compiler flags here"
	@echo "           SOURCES   Specify source code file (default: Final.cpp)"
	@echo "       temporal=AB   Use Adams-Bashforth temporal scheme (Runge-Kutta [RK] by default)"
	@echo "       fourOrder=Y   Compile with fourth-order derivative schemes (disabled by default)"
	@echo "             opt=Y   Compile with optimisation flags (disabled by default)"
	@echo " "
	@echo "Remember to define appropriate SYCL or DPC++ environment variables if necessary."
	@echo " "
	
#==========================================================
#  Define additional options
vars:
#  Temporal scheme
ifeq ($(temporal), RK)
	$(eval COMP_VARS += -DITEMP=0)
	@tput setaf 5; echo "Using Runge-Kutta temporal scheme"
else
	$(eval COMP_VARS += -DITEMP=1)
	@tput setaf 5; echo "Using Adams-Bashforth temporal scheme (default)"
endif
#  Differencing method
ifeq ($(fourOrder), Y)
	$(eval COMP_VARS += -DfourOrder=1)
	@tput setaf 5; echo "Using fourth order differencing"
else
	$(eval COMP_VARS += -DfourOrder=0)
	@tput setaf 5; echo "Using second order differencing (default)"
endif
#  Additional flags
ifdef ADFLAGS
	$(eval COMP_VARS += $(ADFLAGS))
endif

#==========================================================
#  GNU compiler
gnu: vars
ifeq ($(shell which g++), )
	@tput bel
	@tput setaf 1; echo "g++ compiler not found."
else
ifeq ($(opt), Y)
	$(eval COMP_VARS += $(CC_OPTFLAGS))
	@tput setaf 5; echo "Compiling with optimisations"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "g++ compiler found"; tput sgr0
	@$(CC) $(COMP_VARS) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=1 $(CCFLAGS) $(CC_EXE_NAME) $(SOURCES)
endif

dpc: vars
ifeq ($(shell which dpcpp), )
	@tput bel
	@tput setaf 1; echo "DPCPP compiler not found."
else
ifeq ($(opt), Y)
	$(eval COMP_VARS += $(DPCPP_OPTFLAGS))
	@tput setaf 5; echo "Compiling with optimisations"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "DPCPP compiler found"; tput sgr0
ifeq ($(SERIAL), 1)
	$(eval DPC = 0)
endif
	@$(DPCPP_CC) $(COMP_VARS) -DDPC=$(DPC) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=$(SERIAL) -DdeviceSelection=cl::sycl::$(DEVICE)_selector{} $(DPCPP_CCFLAGS) $(DPCPP_EXE_NAME) $(SOURCES)
endif

hip: vars
ifeq ($(shell which syclcc), )
	@tput bel
	@tput setaf 1; echo "hipSYCL compiler not found."
else
ifeq ($(opt), Y)
	$(eval COMP_VARS += $(SYCL_OPTFLAGS))
	@tput setaf 5; echo "Compiling with optimisations"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "hipSYCL compiler found"; tput sgr0
	@$(SYCL_CC) $(COMP_VARS) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=$(SERIAL) -DdeviceSelection=cl::sycl::$(DEVICE)_selector{} $(SYCL_CCFLAGS) $(SYCL_EXE_NAME) $(SOURCES)
endif

clean:
	@rm -rf $(CC_EXE_NAME) $(DPCPP_EXE_NAME) $(SYCL_EXE_NAME)
	@tput setaf 2; echo "Cleaning complete!"; tput sgr0
