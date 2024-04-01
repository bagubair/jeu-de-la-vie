projet: fonctions.p main.p
	gcc $^ -o $@ $(shell sdl2-config --cflags --libs )

%.p:%.c
	gcc $^ -c -o $@ $(shell sdl2-config --cflags --libs )

run :
	./projet
clean:
	rm *.p
