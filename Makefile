CXX = g++
CXXFLAGS = -Werror -std=c++17 -I./src
SRC = main.cpp
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
OUTPUT_DIR = build
FILE = main
TARGET = $(OUTPUT_DIR)/$(FILE)

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
