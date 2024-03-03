# Setting variables
RM = rm
DELOUT = $(APPNAME)
INCDIR = "/usr/include/boost"
CXXFLAGS = -I$(INCDIR)

# Compiler settings - Can be customized.
CC = g++ -std=c++11 -Wall -Werror

# Makefile settings - Can be customized.
APPNAME = calendar
EXT = .cpp

SRC = $(wildcard *$(EXT))
OBJ = $(SRC:%$(EXT)=%.o)
DEP = $(OBJ:%.o=%.d)


########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

# Creates the dependecy rules
%.d: %$(EXT)
	@$(CPP) $< -MM -MT $(@:%.d=%.o) >$@ $(CXXFLAGS)

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
%.o: %$(EXT)
	$(CC) -o $@ -c $< $(CXXFLAGS)


# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(DELOUT)

# Cleans only all files with the extension .d and .o
.PHONY: cleanod
cleanod:
	$(RM) $(DEP) $(OBJ)