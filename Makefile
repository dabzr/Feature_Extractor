all: ./bin/imagefilter

./bin/imagefilter: ./obj/Directory.o ./obj/Filter.o ./obj/Image.o ./obj/main.o ./obj/SCM.o
	gcc ./obj/*.o -o ./bin/imagefilter -O3 -march=native -w
./obj/Directory.o: ./src/Directory.c
	gcc -o ./obj/Directory.o -c ./src/Directory.c
./obj/Filter.o: ./src/Filter.c
	gcc -o ./obj/Filter.o -c ./src/Filter.c
./obj/Image.o: ./src/Image.c
	gcc -o ./obj/Image.o -c ./src/Image.c
./obj/SCM.o: ./src/SCM.c
	gcc -o ./obj/SCM.o -c ./src/SCM.c
./obj/main.o: ./src/main.c
	gcc -o ./obj/main.o -c ./src/main.c

clean:
	rm ./obj/*.o ./bin/imagefilter
