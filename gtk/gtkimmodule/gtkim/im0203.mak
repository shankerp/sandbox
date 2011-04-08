im0203: im0203.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
