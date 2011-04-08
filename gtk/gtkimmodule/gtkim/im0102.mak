im0102: im0102.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
