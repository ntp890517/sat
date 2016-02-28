CXX = g++
EXEC = sat
CXX_FLAGS = -g -Wall
LD_FLAGS = -g

MAIN = src/main/main.cpp
MODULES = db solver 
MOD_DIRS = $(addprefix src/,$(MODULES))
CPP_FILES = $(foreach mod_dir,$(MOD_DIRS),$(wildcard $(mod_dir)/*.cpp))
OBJS = $(CPP_FILES:.cpp=.o)


$(EXEC): $(MAIN:.cpp=.o) $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(EXEC) 

$(MAIN:.cpp=.o): $(MAIN)
	$(CSS) $(CSS_FLAGS) -c -o $@ $<

$(OBJS): %.o:%.cpp %.h
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: all clean

all: $(OBJS) $(EXEC)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)
