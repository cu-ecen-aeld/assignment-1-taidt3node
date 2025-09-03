CC = gcc
CFLAGS = -Iinc
SRC = src/bstrutils.c
OBJ = bstrutils.o
STATIC_LIB = libstrutils.a
SHARED_LIB = libstrutils.so

all: main_static main_shared
# Build static lib
$(STATIC_LIB): $(OBJ)
	ar rcs $(STATIC_LIB) $(OBJ)
# Build shared lib
$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $(SHARED_LIB) $(OBJ)
# Object file for both static and shared
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -fPIC -c $(SRC) -o $(OBJ)
# Build static binary
main_static: main.c $(STATIC_LIB)
	$(CC) $(CFLAGS) main.c ./$(STATIC_LIB) -o main_static
# Build shared binary
main_shared: main.c $(SHARED_LIB)
	$(CC) $(CFLAGS) main.c -L. -lstrutils -o main_shared
clean:
	rm -f *.o *.a *.so main_static main_shared