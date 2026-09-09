
#==========================================================
#  2D Navier Stokes Equation Solver | Makefile
#  Created      | Sylvain Laizet    | 2014 | Fortran
#  Translated   | Nathanael Jenkins | 2021 | C++
#  Parallelised | Nathanael Jenkins | 2021 | SYCL
#==========================================================
#  Version 4.3
#  Last updated 17.10.2021

#  Source filename
SOURCES = Final.cpp
#  Domain width (square)
DOMAIN = 129
#  Number of timesteps
TIMESTEPS = 10000
#  File saving frequency
IMODULO = 2500
#  SYCL device type
DEVICE = default
#  Parallel by default (when using parallel compilers)
SERIAL = 0
DPC = 1
#  Optimise by default
OPT = 1
#  Run by default
RUN = 1
#  Show averages by default
AVG = 1
#  Use second-order differencing schemes by default
ORDER=2
#  Use Adams-Bashforth temporal scheme by default
TEMPORAL=AB

#  GNU C++ compiler
CC = g++
CCFLAGS = -std=c++17 -o
CC_OPTFLAGS = -O3
CC_EXE_NAME = 2DSolver_serial

#  oneAPI DPC++ SYCL compiler
DPCPP_CC = dpcpp
DPCPP_CCFLAGS = -std=c++17 -o
DPCPP_OPTFLAGS = #  DPC++ on Devcloud fails to compile using -fast
DPCPP_EXE_NAME = 2DSolver_dpc

#  hipSYCL SYCL compiler
SYCL_CC = syclcc
SYCL_CCFLAGS = -std=c++17 -o
SYCL_OPTFLAGS = -O3
SYCL_EXE_NAME = 2DSolver_hip

#  gnuPlot
PLOTFILE = C_Plot
	
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
	@echo "              plot   Generate visualisations using gnuPlot file"
	@echo "             clean   Clean existing executables"
	@echo " "
	@echo "           Options   Description"
	@echo "------------------------------------------------------------------------------------------"
	@echo "           SOURCES   Specify source filename, default: USM.cpp"
	@echo "            DOMAIN   Specify domain width, default=129"
	@echo "         TIMESTEPS   Specify number of timesteps, default=100"
	@echo "           IMODULO   File writing frequency, default=2500"
	@echo "             ORDER   Order of differencing scheme (2=> 2nd, 4=> 4th), default: 2"
	@echo "          TEMPORAL   Temporal scheme (AB=> Adams-Bashforth, RK=> Runge-Kutta), default: AB"
	@echo "            DEVICE   SYCL device type, default: default"
	@echo "            SERIAL   (BOOL) Force compiler to use serial code. Does not apply if using GNU."
	@echo "               AVG   (BOOL) Live field averages for monitoring, enabled by default"
	@echo "           ADFLAGS   Specify additional compiler flags here"
	@echo "               RUN   (BOOL) Run after compilation, enabled by default"
	@echo "               OPT   (BOOL) Compile with optimisation flags, enabled by default"
	@echo "          PLOTFILE   gnuPlot file name, default: C_Plot"
	@echo " "
	@echo "Remember to define appropriate SYCL or DPC++ environment variables if necessary."
	@echo " "
	
#==========================================================
#  Define additional options
vars:
#  Additional flags
ifdef ADFLAGS
	$(eval COMP_VARS += $(ADFLAGS))
endif
ifeq ($(AVG), 1)
	$(eval COMP_VARS += -DAVG=1)
endif
ifeq ($(ORDER), 4)
	@tput setaf 5; echo "Using fourth-order differencing schemes"
	$(eval COMP_VARS += -DFOURORDER=1)
else
	@tput setaf 5; echo "Using second-order differencing schemes"
	$(eval COMP_VARS += -DFOURORDER=0)
endif
ifeq ($(TEMPORAL), RK)
	@tput setaf 5; echo "Using Runge-Kutta temporal scheme"
	$(eval COMP_VARS += -DITEMP=1)
else
	@tput setaf 5; echo "Using Adams-Bashforth temporal scheme"
	$(eval COMP_VARS += -DITEMP=0)
endif

#==========================================================
#  GNU compiler
gnu: vars
ifeq ($(shell which g++), )
	@tput bel
	@tput setaf 1; echo "g++ compiler not found."
else
ifeq ($(OPT), 1)
	$(eval COMP_VARS += $(CC_OPTFLAGS))
	@tput setaf 5; echo "Compiling with optimisations"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "g++ compiler found"; tput sgr0
	@$(CC) $(COMP_VARS) -Dimod=$(IMODULO) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=1 $(CCFLAGS) $(CC_EXE_NAME) $(SOURCES)
endif
ifeq ($(RUN), 1)
	@tput setaf 2; echo "Running program..."; tput sgr0
	@./$(CC_EXE_NAME)
endif

#==========================================================
#  DPCPP compiler
dpc: vars
ifeq ($(shell which dpcpp), )
	@tput bel
	@tput setaf 1; echo "DPCPP compiler not found."
else
ifeq ($(OPT), 1)
	$(eval COMP_VARS += $(DPCPP_OPTFLAGS))
	@tput setaf 1; echo "Optimisations disabled for DPC++"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "DPCPP compiler found"; tput sgr0
ifeq ($(SERIAL), 1)
	$(eval DPC = 0)
endif
	@$(DPCPP_CC) $(COMP_VARS) -DDPC=$(DPC) -Dimod=$(IMODULO) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=$(SERIAL) -DdeviceSelection=cl::sycl::$(DEVICE)_selector{} $(DPCPP_CCFLAGS) $(DPCPP_EXE_NAME) $(SOURCES)
endif
ifeq ($(RUN), 1)
	@tput setaf 2; echo "Running program..."; tput sgr0
	@./$(DPCPP_EXE_NAME)
endif

#==========================================================
#  hipSYCL compiler
hip: vars
ifeq ($(shell which syclcc), )
	@tput bel
	@tput setaf 1; echo "hipSYCL compiler not found."
else
ifeq ($(OPT), 1)
	$(eval COMP_VARS += $(SYCL_OPTFLAGS))
	@tput setaf 5; echo "Compiling with optimisations"
else
	@tput setaf 5; echo "Compiling without optimisations"
endif
	@tput setaf 2; echo "hipSYCL compiler found"; tput sgr0
	@$(SYCL_CC) $(COMP_VARS) -Dimod=$(IMODULO) -Ddomain=$(DOMAIN) -Dtimesteps=$(TIMESTEPS) -DSERIAL=$(SERIAL) -DdeviceSelection=cl::sycl::$(DEVICE)_selector{} $(SYCL_CCFLAGS) $(SYCL_EXE_NAME) $(SOURCES)
endif
ifeq ($(RUN), 1)
	@tput setaf 2; echo "Running program..."; tput sgr0
	@./$(SYCL_EXE_NAME)
endif

#==========================================================
#  gnuPlot visualisation
plot:
	@gnuplot $(PLOTFILE)

#==========================================================
#  Cleaning
clean:
	@rm -rf $(CC_EXE_NAME) $(DPCPP_EXE_NAME) $(SYCL_EXE_NAME)
	@tput setaf 2; echo "Cleaning complete!"; tput sgr0
