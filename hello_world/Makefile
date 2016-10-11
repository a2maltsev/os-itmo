SRC=hello_world.c
TARGET=hello_world
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $^ -o $(TARGET)

.c.o:
	gcc -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
