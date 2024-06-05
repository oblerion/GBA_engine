#! /bin/bash

CC=clang
DSRC=src
DOBJ=build/linux64/obj
DEXEC=build/linux64
EXEC=main

all:
	./make
# link run
#
# link: main.o atlas.o ui.o ui_runner.o ui_mainbar.o kbd_layout.o Palette.o Sprite.o ui_palette.o ui_sprite.o
# 	if [ -f $(EXEC) ];then rm -rf $(EXEC) ;fi
# 	$(CC) $(DOBJ)/main.o $(DOBJ)/atlas.o $(DOBJ)/ui.o $(DOBJ)/ui_runner.o $(DOBJ)/ui_mainbar.o $(DOBJ)/kbd_layout.o  $(DOBJ)/Palette.o $(DOBJ)/Sprite.o $(DOBJ)/ui_palette.o $(DOBJ)/ui_sprite.o -g -Wall -llua -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(EXEC)
#
# main.o: ${DSRC}/main.c
# 	$(CC) -c $(DSRC)/main.c -Isrc -Wall -o $(DOBJ)/main.o
#
# Palette.o: $(DSRC)/Palette.c
# 	$(CC) -c $(DSRC)/Palette.c -Isrc -Wall -o $(DOBJ)/Palette.o
#
# Sprite.o: $(DSRC)/Sprite.c
# 		$(CC) -c $(DSRC)/Sprite.c -Isrc -Wall -o $(DOBJ)/Sprite.o
#
# ui_palette.o: $(DSRC)/ui_palette.c
# 		$(CC) -c $(DSRC)/ui_palette.c -Isrc -Wall -o $(DOBJ)/ui_palette.o
#
# ui_sprite.o: $(DSRC)/ui_sprite.c
# 		$(CC) -c $(DSRC)/ui_sprite.c -Isrc -Wall -o $(DOBJ)/ui_sprite.o
#
# ui_mainbar.o: $(DSRC)/ui_mainbar.c
# 		$(CC) -c $(DSRC)/ui_mainbar.c -Isrc -Wall -o $(DOBJ)/ui_mainbar.o
#
# ui_runner.o: $(DSRC)/ui_runner.c
# 		$(CC) -c $(DSRC)/ui_runner.c -Isrc -Wall -o $(DOBJ)/ui_runner.o
#
# ui.o: $(DSRC)/ui.c
# 		$(CC) -c $(DSRC)/ui.c -Isrc -Wall -o $(DOBJ)/ui.o
#
# kbd_layout.o: $(DSRC)/kbd_layout.c
# 		$(CC) -c $(DSRC)/kbd_layout.c -Isrc -Wall -o $(DOBJ)/kbd_layout.o
# atlas.o: $(DSRC)/atlas.c
# 	$(CC) -c $(DSRC)/atlas.c -Isrc -Wall -o $(DOBJ)/atlas.o
# clua.o: $(DSRC)/clua.c
# 	$(CC) -c $(DSRC)/clua.c -Isrc -Wall -o $(DOBJ)/clua.o
# run:
# 	if [ -f $(EXEC) ];then ./$(EXEC) ;fi
#
# clean:
# 	rm -rf $(DOBJ)/*.o
