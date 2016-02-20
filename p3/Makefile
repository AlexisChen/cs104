CXX = g++
CPPFLAGS = -g -Wall 
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: llisttest 

llisttest: llistint.o llisttest.cpp 
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

llistint.o: llistint.h llistint.cpp 
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o llistint.o

.PHONY: clean
clean:
	rm -rf 
.PHONY: tests

tests: $(BIN_DIR)/arrayTest
	-@$(BIN_DIR)/arrayTest
	-@echo "--- All Tested!---"


problem5: stackint.h stackint.cpp llistint.h llistint.cpp hw3p5.cpp
	$(CXX) -g stackint.h stackint.cpp llistint.h llistint.cpp hw3p5.cpp -o problem5


	


