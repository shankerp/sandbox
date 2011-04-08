im0101: im0101.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
