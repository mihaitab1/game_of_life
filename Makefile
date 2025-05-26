build:
	gcc -o tema gameoflife.h gameoflife.c app.c

run:
	./checker-linux-amd64 -i

clean:
	rm -rf tema