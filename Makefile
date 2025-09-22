CXX = g++
CXXFLAGS = -Werror -std=c++17 -I./src -I./inlcude/ #-fsanitize=address,undefined -fno-omit-frame-pointer -g
SRC = src/main.cpp src/player/player.cpp src/ui/button.cpp src/ui/textinput.cpp src/world/world.cpp src/world/map.cpp src/db/db.cpp src/game.cpp
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
OUTPUT_DIR = build
FILE = main
TARGET = $(OUTPUT_DIR)/$(FILE)

ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    FILE = main.exe
    TARGET = $(OUTPUT_DIR)/$(FILE)
endif

all: $(TARGET)

$(TARGET): $(OBJ) | $(OUTPUT_DIR) 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

build/%.o: src/%.cpp | $(OUTPUT_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTPUT_DIR)
	rm -f $(OBJ)
