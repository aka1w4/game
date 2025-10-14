CXX = g++
CXXFLAGS = -Werror -std=c++20 -I./src -I./include/ 
SRC = src/main.cpp src/player/player.cpp src/entity/entity.cpp src/ui/button.cpp src/ui/textinput.cpp src/ui/background.cpp src/world/world.cpp src/world/map.cpp src/db/db.cpp src/game.cpp
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11 -lleveldb
OUTPUT_DIR = build
FILE = main
TARGET = $(OUTPUT_DIR)/$(FILE)

ifeq ($(OS),Windows_NT)
		CXXFLAGS += -L./lib/windows/
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lleveldb
    FILE = main.exe
    TARGET = $(OUTPUT_DIR)/$(FILE)
else
		CXXFLAGS += -L./lib/linux/
endif

.PHONY: all clean release

all: CXXFLAGS += -g --save-temps
all: $(TARGET)

release: CXXFLAGS += -O3 -s -fno-ident -no-pie -fno-pie\
	-Wl,--gc-sections \
	-ffunction-sections -fdata-sections 
release: $(OBJ) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET) $(LIBS)

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
