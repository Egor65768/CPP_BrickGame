NAMEAPP = BrickGame
CC = gcc 
CXX = g++
FLAGS = -Wextra -Werror -Wall -std=c++17
TEST_LIB = ./tests/*.cc
LIBRARIES = -lncurses
LINK_FLAGS = -lgtest -lgtest_main -pthread 
SNAKE = brick_game/controller/s21_controller.cc brick_game/snake/s21_snake.cc brick_game/snake/additinal_func/s21_additinal_func.cc
BACKEND := brick_game/snake/s21_snake.cc \
    			brick_game/controller/s21_controller.cc \
				brick_game/controller/s21_tetris_controller.c \
    			brick_game/tetris/s21_tetris.c \
				brick_game/snake/additinal_func/s21_additinal_func.cc 

FRONTEND:=gui/cli/frontend.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) 
	LINK_FLAGS += -lm -lsubunit
endif

clean: 
	rm -fr *.o *.a *.gch *.gcno *.gcda *.info gcov_test s21_test.info ./report test .record.txt ../build ../dist

style:
	clang-format -style=google -n  brick_game/controller/* brick_game/snake/*.cc \
	brick_game/snake/*.cc gui/desktop/view/*.cc gui/desktop/view/*.h brick_game/tetris/* \
	gui/cli/* tests/* brick_game/parametr/* brick_game/snake/additinal_func/*

format:
	clang-format -style=google -i  brick_game/controller/* brick_game/snake/*.cc \
	brick_game/snake/*.cc gui/desktop/view/*.cc gui/desktop/view/*.h brick_game/tetris/* \
	gui/cli/* tests/* brick_game/parametr/* brick_game/snake/additinal_func/*
	

install_desktop:
	echo "Start installation"
	mkdir -p ../build
	cd gui/desktop/view && qmake && make && make clean && rm Makefile && mv view ../../../../build/$(NAMEAPP).app
	echo "The installation has been completed successfully"

install_cli: ${BACKEND} ${FRONTEND}
	$(CXX) $(FLAGS) $(LIBRARIES) $^ -o brickgame_cli.out -lncurses
	mv brickgame_cli.out ../build

install: install_desktop install_cli

uninstall:
	rm -rf ../build 
	echo "The uninstallation has been completed successfully"

rebuild: uninstall install 

test: clean
	$(CXX) $(FLAGS) $(SNAKE) ${TEST_LIB} ${LINK_FLAGS} -o test
	./test

gcov_flag:
	$(eval FLAGS += -fprofile-arcs -ftest-coverage -g)

gcov_report: gcov_flag test
	lcov -t "stest" -o s21_test.info -c -d . --rc lcov_branch_coverage=1 --ignore-errors mismatch
	genhtml -o report s21_test.info
	open report/index.html	

valgrind: test
ifeq ($(UNAME_S), Linux) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
endif

dist:
	mkdir -p ../dist
	cp -R ../build/$(NAMEAPP).app ../dist
	cp ../README.md ../dist
	cd ../dist && tar cvzf $(NAMEAPP)_v1.0.tgz *
	cd ../dist && rm -rf $(NAMEAPP).app README.md
	echo "The build was successfully archived"

dvi:
	open ../README.md

all: rebuild dist
