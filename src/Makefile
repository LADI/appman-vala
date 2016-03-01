all:
	gcc `pkg-config --cflags gtk+-3.0` RapidLauncher.c `pkg-config --libs gtk+-3.0` -L../build/ -lrocketlauncher `pkg-config --cflags --libs glib-2.0` -o ../build/rapidlauncher -O2

clean:
	rm ../build/rapidlauncher