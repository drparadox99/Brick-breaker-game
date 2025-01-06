
all: main_ clean

main_: main.o erreurMessage.o Init.o libPointeur.o 

	gcc -o main main.o erreurMessage.o Init.o libPointeur.o -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


main.o : main.c headers/Init.h
	
	gcc -c main.c -I/opt/homebrew/include/SDL2   

erreurMessage.o : sources/erreurMessage.c headers/erreurMessage.h 
	
	gcc -c sources/erreurMessage.c -I/opt/homebrew/include/SDL2 

Init.o : sources/Init.c headers/Init.h headers/erreurMessage.h
	
	gcc -c sources/Init.c -I/opt/homebrew/include/SDL2 

libPointeur.o : sources/libPointeur.c headers/libPointeur.h
	
	gcc  -c sources/libPointeur.c -I/opt/homebrew/include/SDL2 

clean:
	rm -f *.o    #removes all the objects file and the file named output



