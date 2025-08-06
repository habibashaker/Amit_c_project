build:
	gcc -Iinclude -o program.exe main.c src/SDB.c src/SDBAPP.c
clean:
	rm *.exe
	rm *.o
run:
	./program.exe
