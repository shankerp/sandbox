im0201: im0201.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
