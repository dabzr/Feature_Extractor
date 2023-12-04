all: imagefilter

imagefilter: Directory.o Filter.o Image.o main.o SCM.o
	gcc ./obj/*.o -o ./bin/imagefilter -O3 -march=native -w
Directory.o: ./src/Directory.c
	gcc -o ./obj/Directory.o -c ./src/Directory.c
Filter.o: ./src/Filter.c
	gcc -o ./obj/Filter.o -c ./src/Filter.c
Image.o: ./src/Image.c
	gcc -o ./obj/Image.o -c ./src/Image.c
SCM.o: ./src/SCM.c
	gcc -o ./obj/SCM.o -c ./src/SCM.c
main.o: ./src/main.c
	gcc -o ./obj/main.o -c ./src/main.c

clean:
	rm ./obj/*.o ./bin/imagefilter
