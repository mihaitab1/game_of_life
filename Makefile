build:
	gcc tema.c -o a.out

run:
	./checker-linux-amd64 -i

clean:
	rm -rf a.out