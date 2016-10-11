SRC=cat.c
TARGET=cat
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $^ -o $(TARGET)

.c.o:
	gcc -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
