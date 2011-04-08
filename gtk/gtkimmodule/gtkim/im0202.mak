im0202: im0202.c
	gcc -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
