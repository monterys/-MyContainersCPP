CC = g++
CFLAGS = -Wall -Werror -Wextra -fno-elide-constructors
LDFLAGS = -lgtest
GCOVFLAGS = -ftest-coverage -fprofile-arcs
LCOVFLAGS = --no-external -c -d .

PROJECTNAME = my_containers
SRC_DIR = .
SRC_TEST_DIR = ./tests
OBJ_DIR = .
OBJ_TEST_DIR = $(addprefix $(OBJ_DIR)/, test)
GCOV_HTML_DIR = report

SRC = $(addsuffix .h, $(PROJECTNAME))
SRC_TEST = $(wildcard $(SRC_TEST_DIR)/test_*.cc)

EXECUTABLE = $(addprefix test_, $(PROJECTNAME))
COVERAGE_INFO = $(addsuffix .info, $(PROJECTNAME))
COVERAGE_NAME = $(addprefix $(OBJ_DIR)/, $(addsuffix .gcda, $(EXECUTABLE)))

OS := $(shell uname)

ifeq ($(OS),Darwin)
	GCOVFLAGS += --ignore-errors mismatch
endif

all: test

clean:
	@echo "Cleaning up..."
	rm -rf *.o $(EXECUTABLE) $(LIB) $(GCOV_HTML_DIR) *.gc*

test: clean ${EXECUTABLE}
	@echo "Running tests..."
	./${EXECUTABLE}

$(EXECUTABLE): $(SRC_TEST)
	@echo "Building..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(GCOVFLAGS)

gcov_report: test
	@echo "Generating HTML coverage report..."
	@mkdir -p $(GCOV_HTML_DIR)

	lcov -t $(EXECUTABLE) -o $(GCOV_HTML_DIR)/$(COVERAGE_INFO) $(LCOVFLAGS)
	genhtml $(GCOV_HTML_DIR)/$(COVERAGE_INFO) -o $(GCOV_HTML_DIR)
	open $(GCOV_HTML_DIR)/index.html

test_memory: $(EXECUTABLE)
	@echo "Checking leaks..."
ifeq ($(OS),Linux)
	valgrind ./$(EXECUTABLE) --check-full
endif
ifeq ($(OS),Darwin) 
	CK_FORK=no leaks -quiet --atExit -- ./$(EXECUTABLE)
endif

test_format:
	@echo "Checking styles..."
	clang-format -n -style=Google $(SRC_TEST_DIR)/*.cc *.h

format:
	@echo "Formatting..."
	clang-format -i -style=Google $(SRC_TEST_DIR)/*.cc *.h

.PHONY: all clean test gcov_report test_memory test_format
