CXX = g++
EXEC = sat
TEST_EXEC = clauseTest
CXX_FLAGS = -g -Wall -std=c++11
LD_FLAGS = -g -std=c++11

MAIN = src/main/main.cpp
TEST = src/main/clauseTest.cpp
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

$(TEST_EXEC): $(TEST:.cpp=.o) $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(TEST_EXEC)

.PHONY: all clean regression test

all: $(OBJS) $(EXEC) $(TEST_EXEC)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)
	-rm -f $(TEST_EXEC)

regression:
	@echo "\n[Run] sat.1.cnf"
	@./$(EXEC) cases/tiny/sat.1.cnf
	@echo "\n[Run] unsat.cnf"
	@./$(EXEC) cases/tiny/unsat.cnf
	@echo "\n[Run] unsat.2.cnf"
	@./$(EXEC) cases/tiny/unsat.2.cnf

test: $(TEST_EXEC)
	@echo "\n[Run] clauseTest"
	@./$(TEST_EXEC)
