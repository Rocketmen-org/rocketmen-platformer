# Compiler
CXX = g++

# Compiler and linker flags. It's not the end of the world if you don't know which
# is which, but you may need to modify the compile statements as a result.
#   Note: If you're up to the challenge, I left my compiler flags here. It adds way
#   more warning flags, and uses the -Werror flag, meaning the program won't compile
#   if it finds a warning...
CXXFLAGS = `sdl2-config --cflags` -std=c++17 -ggdb3 -Wall  #Add more flags as you see fit!
# CXXFLAGS = -`sdl2-config --cflags` std=c++17 -ggdb3 -Wall -W -Werror -Weffc++ -Wextra -pedantic
LDFLAGS = `sdl2-config --libs` -lm -lSDL2_image -lSDL2_mixer

# For the include statements, the compiler needs to know where the .h files are
# located at! For many files, it knows by default, but for SDL, since this is not
# standard C++, we have to tell the compiler. This is what the sdl2-config part is
# about. We can also tell the compiler where our .h files are so the .cpp files
# don't have to look for them! If you make ./include directory and put all your .h
# files in there, then you can always include them in any source file, regardless
# of where it is located in the directory structure!
INCLUDES = -I ./include -I `sdl2-config --prefix`/include/

# Executable name.
# NOTE: If you change the name to include a filepath, it will put the executable
#       at that location. Use that to get the executable in the right position
#       for finding any other files like images!
EXEC = game.out

# Function for finding source code since ** doesn't work in GNU Make. Touch at your own risk!
# Credit to larskholte at https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
glob = $(foreach d, $(wildcard $(1:=/*)), $(call glob, $d, $2) $(filter $(subst *, %, $2), $d))

# Automatically constructed file lists

# This list automatically searches all the way into the src directory for .cpp files to compile.
# If you would rather check all directories, uncomment the two lines below instead. You can also
# manually make one instead, if you would rather.
SRCS := $(call glob, src, *.cpp)
#SRCS := $(wildcard *.cpp) 
#SRCS += $(call glob, *, *.cpp)

# As the list above searched for .cpp files in src, so this searches in include for .h files.
HDRS := $(call glob, include, *.h)
#HDRS := $(wildcard *.h ) 
#HDRS += $(call glob, *, *.h )

OBJS := $(patsubst %.cpp, bin/%.o, $(SRCS))


# Build targets
bin/%.o: %.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(INCLUDES) $(LDFLAGS)

# Execution commands
build: $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf bin
	rm $(EXEC)

# Print the file lists
print_srcs: 
	@echo $(SRCS) | tr " " "\n"
print_hdrs: 
	@echo $(HDRS) | tr " " "\n"
print_objs:
	@echo $(OBJS) | tr " " "\n"
