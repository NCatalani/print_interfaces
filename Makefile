CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g
LDFLAGS =  -lpcap

SRC = print_interfaces.c
OBJ = $(SRC:.c=.o)
EXEC = print_interfaces

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)