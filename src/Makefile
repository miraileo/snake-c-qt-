TEST_DIR = tests
CPPFLAGS=-lstdc++ -std=c++17
LINUXFLAGS=-lgtest -lrt -lpthread -lm -lsubunit
CFLAGS=-Wall -Werror -Wextra
CC=gcc
MAKECLANG=clang-format -i
CHECKCLANG=clang-format -n
VALGRINDFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes
SNAKEDESKTOP_DIR=gui/desktop/snakeView
SNAKECONTROLLER_DIR=brick_game/snake/snakeController
SNAKEMODEL_DIR=brick_game/snake/snakeModel
TETRISDESKTOP_DIR=gui/desktop/tetrisView
SNAKECLI_DIR=gui/cli/snakeView
SRC_DIRS = brick_game gui
SOURCES = $(shell find $(SRC_DIRS) -name '*.cpp' -o -name '*.h')
BUILD_DIR = build
SNAKE_EXECUTABLE = snake

all: snakeDesktop

dvi:
	doxygen
	open doxygen/html/index.html

install:
	@echo "Creating build directory..."
	mkdir -p $(BUILD_DIR)  # Create the build directory if it doesn't exist
	cd $(SNAKEDESKTOP_DIR) && qmake snake.pro && make
	mv $(SNAKEDESKTOP_DIR)/$(SNAKE_EXECUTABLE) $(BUILD_DIR)/

uninstall:
	@echo "Removing the executable..."
	rm -rf $(BUILD_DIR)

test:
	$(CC) tests/test.cpp $(LINUXFLAGS) -o test $(CPPFLAGS)
	./test

snakeCli:
	$(CC) $(SNAKEMODEL_DIR)/snakemodel.cpp $(SNAKECLI_DIR)/*.cpp $(SNAKECONTROLLER_DIR)/snakecontroller.cpp $(CPPFLAGS) -o snake $(LINUXFLAGS) -lncurses $(CFLAGS)
	./snake

snakeDesktop:
	cd $(SNAKEDESKTOP_DIR) && qmake snake.pro && make && ./snake 

tetrisDesktop:
	cd $(TETRISDESKTOP_DIR) && qmake tetris.pro && make && ./tetris

cleanSnakeDesktop:
	rm -rf $(SNAKEDESKTOP_DIR)/*.o $(SNAKEDESKTOP_DIR)/snake $(SNAKEDESKTOP_DIR)/.qmake.stash $(SNAKEDESKTOP_DIR)/Makefile
	rm -rf $(SNAKEDESKTOP_DIR)/moc_mainwindow.cpp $(SNAKEDESKTOP_DIR)/moc_predefs.h $(SNAKEDESKTOP_DIR)/moc_snakeview.cpp

cleanTetrisDesktop:
	rm -rf $(TETRISDESKTOP_DIR)/*.o $(TETRISDESKTOP_DIR)/tetris $(TETRISDESKTOP_DIR)/.qmake.stash $(TETRISDESKTOP_DIR)/Makefile
	rm -rf $(TETRISDESKTOP_DIR)/moc_mainwindow.cpp $(TETRISDESKTOP_DIR)/moc_predefs.h $(TETRISDESKTOP_DIR)/moc_tetrisview.cpp

cleanSnakeCli:
	rm -rf snake

clean: cleanSnakeDesktop cleanTetrisDesktop cleanSnakeCli
	rm -rf test
	rm -rf doxygen

dist: clean uninstall
	mkdir ../dist
	cp -r ../src ../dist
	cp ../README.md ../dist
	cd ../dist && tar -czvf dist.tar.gz ./src
	rm -rf ../dist/src

style:
	clang-format -n $(SOURCES)
	clang-format -i $(SOURCES)