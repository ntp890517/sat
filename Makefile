CXX = g++
EXEC = sat
CXX_FLAGS = -g -Wall
LD_FLAGS = -g

MAIN = src/main/main.cpp
MODULES = db sol 
MOD_DIRS = $(addprefix src/,$(MODULES))
CPP_FILES = $(foreach mod_dir,$(MOD_DIRS),$(wildcard $(mod_dir)/*.cpp))
OBJS = $(CPP_FILES:.cpp=.o)


$(EXEC): $(MAIN:.cpp=.o) $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(EXEC) 

$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(CSS_FLAGS) -c -o $@ $<

$(OBJS): %.o:%.cpp %.h
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: all clean regression

all: $(OBJS) $(EXEC)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)

regression:
	@echo "\n[Run] sat.1.cnf"
	@./$(EXEC) cases/tiny/sat.1.cnf
	@echo "\n[Run] unsat.cnf"
	@./$(EXEC) cases/tiny/unsat.cnf
	@echo "\n[Run] unsat.2.cnf"
	@./$(EXEC) cases/tiny/unsat.2.cnf
