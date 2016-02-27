CXX = g++
EXEC = sat
CXX_FLAGS = -g -Wall
LD_FLAGS = -g

MODULES = db solver main
MOD_DIRS = $(addprefix src/,$(MODULES))
CPP_FILES = $(foreach mod_dir,$(MOD_DIRS),$(wildcard $(mod_dir)/*.cpp))
OBJS = $(CPP_FILES:.cpp=.o)


$(EXEC): $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(EXEC) 

$(OBJS): %.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: all clean

all: $(OBJS) $(EXEC)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)
