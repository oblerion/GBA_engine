#! /bin/bash

CC=clang++
DSRC=src
DOBJ=build/linux64/obj
DEXEC=build/linux64
EXEC=main

all: link run

link: main.o ui.o ui_mainbar.o kbd_layout.o Palette.o PaletteManager.o Sprite.o SpriteManager.o ui_palette.o ui_sprite.o
	if [ -f $(EXEC) ];then rm -rf $(EXEC) ;fi
	$(CC) $(DOBJ)/main.o $(DOBJ)/ui.o $(DOBJ)/ui_mainbar.o $(DOBJ)/kbd_layout.o  $(DOBJ)/Palette.o $(DOBJ)/PaletteManager.o $(DOBJ)/Sprite.o $(DOBJ)/SpriteManager.o $(DOBJ)/ui_palette.o $(DOBJ)/ui_sprite.o -g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(EXEC)

main.o: ${DSRC}/main.cpp
	$(CC) -c $(DSRC)/main.cpp -Isrc -Wall -o $(DOBJ)/main.o

Palette.o: $(DSRC)/Palette.cpp
	$(CC) -c $(DSRC)/Palette.cpp -Isrc -Wall -o $(DOBJ)/Palette.o
	
PaletteManager.o: $(DSRC)/PaletteManager.cpp
		$(CC) -c $(DSRC)/PaletteManager.cpp -Isrc -Wall -o $(DOBJ)/PaletteManager.o

Sprite.o: $(DSRC)/Sprite.cpp
		$(CC) -c $(DSRC)/Sprite.cpp -Isrc -Wall -o $(DOBJ)/Sprite.o
		
SpriteManager.o: $(DSRC)/SpriteManager.cpp
		$(CC) -c $(DSRC)/SpriteManager.cpp -Isrc -Wall -o $(DOBJ)/SpriteManager.o
	
ui_palette.o: $(DSRC)/ui_palette.cpp
		$(CC) -c $(DSRC)/ui_palette.cpp -Isrc -Wall -o $(DOBJ)/ui_palette.o
		
ui_sprite.o: $(DSRC)/ui_sprite.cpp
		$(CC) -c $(DSRC)/ui_sprite.cpp -Isrc -Wall -o $(DOBJ)/ui_sprite.o

ui_mainbar.o: $(DSRC)/ui_mainbar.cpp
		$(CC) -c $(DSRC)/ui_mainbar.cpp -Isrc -Wall -o $(DOBJ)/ui_mainbar.o
		
ui.o: $(DSRC)/ui.cpp
		$(CC) -c $(DSRC)/ui.cpp -Isrc -Wall -o $(DOBJ)/ui.o

kbd_layout.o: $(DSRC)/kbd_layout.cpp
		$(CC) -c $(DSRC)/kbd_layout.cpp -Isrc -Wall -o $(DOBJ)/kbd_layout.o
	
run:
	if [ -f $(EXEC) ];then ./$(EXEC) ;fi

clean:
	rm -rf $(DOBJ)/*.o
