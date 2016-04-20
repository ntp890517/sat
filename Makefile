CXX = g++
EXEC = sat
TEST_EXEC = clauseTest
CXX_FLAGS = -g -Wall -std=c++11
LD_FLAGS = -g -std=c++11

MAIN = src/main/main.cpp
TEST = src/main/clauseTest.cpp
MODULES = db sol test
MOD_DIRS = $(addprefix src/,$(MODULES))
REG_DIR = regression
REG_CASES = $(wildcard $(REG_DIR)/*.cnf)
CPP_FILES = $(foreach mod_dir,$(MOD_DIRS),$(wildcard $(mod_dir)/*.cpp))
OBJS = $(CPP_FILES:.cpp=.o)

$(EXEC): $(MAIN:.cpp=.o) $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(EXEC) 

$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(OBJS): %.o:%.cpp %.h
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(TEST_EXEC): $(TEST:.cpp=.o) $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $(TEST_EXEC)

$(TEST:.cpp=.o): $(TEST) $(OBJS)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

.PHONY: all clean regression test

all: $(OBJS) $(EXEC) $(TEST_EXEC)

clean:
	-rm -f $(OBJS)
	-rm -f $(EXEC)
	-rm -f $(TEST_EXEC)

regression:
	@$(foreach case,$(REG_CASES),\
	    echo "\n[Run] $(case)";\
	    ./$(EXEC) $(case);)

test: $(TEST_EXEC)
	@echo "\n[Run] clauseTest"
	@./$(TEST_EXEC)
