CC = gcc
CXX = g++

INCLUDES = -Iincludes
LIBRARIES = -Llib

CFLAGS = -g $(INCLUDES)
CXXFLAGS = -g $(INCLUDES)
LDFLAGS = $(LIBRARIES) -l:libglfw3.a -lglfw3 -lopengl32 -lglu32 -lgdi32

src_files = src/*.cpp src/*.c
output_dir = .

main.exe:
	$(CXX) $(src_files) -o $(output_dir)/$@ $(CXXFLAGS) $(LDFLAGS)
	
clean:
	rm -r $(output_dir)
# TARGET = main
# cpp_files = main.cpp

# all: $(TARGET)

# $(TARGET): $(objects) 
#         $(CXX) -o $@ $^ $(LDFLAGS)