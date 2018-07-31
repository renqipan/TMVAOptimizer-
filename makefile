#MakeFile for TMVAOptimizer

#----------------------- here you can input your files and libraries ----------
#
# we compile all *.C and *.cpp defined in SRCDIR
#

SRCDIR = ./src
INCDIR = ./include
BINDIR = ./bin
DEPDIR = $(BINDIR)
VPATH = $(SRCDIR):$(OBJDIR):$(DEPDIR)
SOURCES = $(wildcard $(SRCDIR)/*.C)
SOURCES := $(notdir $(SOURCES))

TMVAOptimizer = bin/TMVAOptimizer

# with additional libs and includes
# e.g. MORELIBS = -L/path -lblub
MORELIBS = -L/usr/lib64 -lz -lCore
# e.g. -I/path
MOREINCS = -I/usr/include -I${ROOTSYS}/include 

OBJS = $(notdir $(SOURCES))
OBJS := $(OBJS:.C=.o)
OBJS := $(OBJS:.cpp=.o)

#------------------------------------------------------------------------------

ifndef ROOTSYS
$(error ROOTSYS is not defined!)
endif

ROOTLIBS = `root-config --libs` -lGenVector -lMathCore -lMinuit2 -lTreePlayer -lTMVA -lTMVAGui -lMLP
CXX = g++ -g3 -O1
CXXFLAGS = `root-config --cflags`
LD = g++
LDFLAGS = `root-config --ldflags`

.SUFFIXES: .cpp .C .o .so

#------------------------------------------------------------------------------

all: ${TMVAOptimizer}

bin/TMVAOptimizer: TMVAOptimizer.C ${OBJS}
	@echo $(SOURCES)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $(MOREINCS) $(ROOTLIBS) $(MORELIBS) -o $@ $< $(addprefix $(BINDIR)/,$(OBJS))
	@echo "$@ done"

install: bindir

bindir:
	mkdir -p $(BINDIR)

uninstall: clean
	rm -rf bin

clean:
	@echo "Cleaning all compiled files, dependencies, etc."
	@rm -rf $(BINDIR)/*
	@rm -rf test/*.exe

#This is the rule for creating the dependency files
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $(MOREINCS) -MM -MF $(DEPDIR)/$@ $<
%.d: %.C
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $(MOREINCS) -MM -MF $(DEPDIR)/$@ $<

%.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $(MOREINCS) -c $< -o $(BINDIR)/$@
%.o: %.C %.d
	$(CXX) $(CXXFLAGS) -I $(INCDIR) $(MOREINCS) -c $< -o $(BINDIR)/$@

-include $(addprefix $(DEPDIR)/,$(SOURCES:%.C=%.d))