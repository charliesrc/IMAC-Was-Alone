CC       =  gcc
CFLAGS   = -Wall -O2 -g
LDFLAGS = 'sdl-config --cflags --libs'
LIB      = -L/usr/local/lib -lSDL -lSDLmain -lSDL_mixer
INCLUDES = -I/usr/local/include -framework Cocoa -framework OpenGL

OBJ      = main.o
RM       = rm -f
BIN      = main
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

main.o : main.c
	@echo "compile main"
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) -c $<
	@echo "done..."

clean :
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)

tar : clean
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)


#gcc -Wall -framework OpenGL -lSDL -lSDLmain -framework cocoa -o exo5 exo5.c
