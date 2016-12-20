CFLAGS=-Wall -Werror -O3 -pedantic -Iproduct -Itest

PRODUCT_LIBS=-lrt -lpthread -pthread
PRODUCT_SOURCES=$(wildcard product/*.cpp)
PRODUCT_OBJECTS=$(PRODUCT_SOURCES:.cpp=.o)

TEST_LIBS=$(PRODUCT_LIBS) -lgtest -lgtest_main
TEST_SOURCES=$(filter-out product/main.cpp, $(wildcard product/*.cpp test/*.cpp))
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

CC=g++

.phony: all clean product test simulator

product.bin: $(PRODUCT_OBJECTS) Makefile
	@$(CC) $(PRODUCT_OBJECTS) -o $@ $(PRODUCT_LIBS)

test.bin: $(TEST_OBJECTS) Makefile
	@$(CC) $(TEST_OBJECTS) -o $@ $(TEST_LIBS)
	
test:
	@valgrind ./test.bin

product:
	@./product.bin

simulator:
	@./SluiceSim64

all: product.bin test.bin

.cpp.o: Makefile
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf product/*.o test/*.o product.bin test.bin 
