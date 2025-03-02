OBJECTS = grid.o maze_gen.o pool.o sampler.o cmaze.o
all: cmaze clean

cmaze: $(OBJECTS)
	gcc $(OBJECTS) -o $@

%.o: %.c
	gcc -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS)
