im0301: im0301.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
