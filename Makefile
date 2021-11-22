# Makefile

# Name of the project
PROJ_NAME=main
 
# .cpp files
C_SOURCE=$(wildcard *.cpp)
 
# .hpp files
H_SOURCE=$(wildcard *.hpp)
 
# Object files
OBJ=$(C_SOURCE:.cpp=.o)
 
# Compiler
CC=g++
 
# Flags for compiler
CC_FLAGS= -c -O3 -std=c++2a -m64
DEBUG_FLAGS= -W -Wall -Wextra -Werror -ggdb -g3 
OTHER_FLAGS= -pthread -fopenmp

# Compilation and linking
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(OTHER_FLAGS) $(DEBUG_FLAGS)
 
%.o: %.cpp %.hpp
	$(CC) -o $@ $< $(CC_FLAGS) $(OTHER_FLAGS) $(DEBUG_FLAGS)
 
main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS) $(OTHER_FLAGS) $(DEBUG_FLAGS)
 
clean:
	 rm -f *.o *~

