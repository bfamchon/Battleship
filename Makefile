PACKAGES = sfml-all
CXXFLAGS = -std=c++14 -Wall -Wextra -g 
LDFLAGS = 
LIBS = 

CXXFLAGS += `pkg-config --cflags $(PACKAGES)`
LDFLAGS +=`pkg-config --libs-only-L --libs-only-other $(PACKAGES)`
LIBS +=`pkg-config --libs-only-l $(PACKAGES)`

PROGFILE = BattleShip.cpp
SRVFILE  = BattleShipSrv.cpp
TESTFILE = MainTest.cpp
BINDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src

PROGSRC = $(SRCDIR)/$(PROGFILE) 
PROGBIN = $(BINDIR)/$(PROGFILE:.cpp=.out) 
PROGOBJ = $(OBJDIR)/$(PROGFILE:.cpp=.o)

SRVSRC = $(SRCDIR)/$(SRVFILE) 
SRVBIN = $(BINDIR)/$(SRVFILE:.cpp=.out) 
SRVOBJ = $(OBJDIR)/$(SRVFILE:.cpp=.o)

TESTSRC = $(SRCDIR)/$(TESTFILE) 
TESTBIN = $(BINDIR)/$(TESTFILE:.cpp=.out) 
TESTOBJ = $(OBJDIR)/$(TESTFILE:.cpp=.o)

SRC = $(filter-out $(PROGSRC) $(SRVSRC) $(TESTSRC), $(shell find $(SRCDIR) -name "*.cpp"))
OBJ = $(subst $(SRCDIR)/, $(OBJDIR)/, $(SRC:.cpp=.o))
TESTHPP = $(shell find $(SRCDIR) -name "*_test.hpp")
SRVHPP = $(shell find $(SRCDIR) -name "*Srv.hpp")

.PHONY : all clean cppcheck
.SECONDARY:

all: $(PROGBIN) $(SRVBIN) $(TESTBIN)
$(PROGBIN): $(PROGOBJ) $(OBJ) 
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(OBJ) $(LIBS)
$(SRVBIN): $(SRVOBJ) $(OBJ) $(SRVHPP)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(OBJ) $(LIBS)
$(TESTBIN): $(TESTOBJ) $(OBJ) $(TESTHPP)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(OBJ) $(LIBS)
$(PROGOBJ): $(PROGSRC)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(SRVOBJ): $(SRVSRC) $(SRVHPP)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(TESTOBJ): $(TESTSRC) $(TESTHPP)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp 
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
cppcheck:
	cppcheck --enable=all --inconclusive $(SRC) $(PROGSRC) $(SRVSRC) $(TESTSRC)
clean:
	find $(OBJDIR) -name "*.o" | xargs rm $(PROGBIN) $(SRVBIN) $(TESTBIN)

