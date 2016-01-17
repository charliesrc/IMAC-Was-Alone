MakefileCC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -L/usr/local/lib -lSDL -lSDLmain -lSDL_mixer -lSDL_image
INCLUDES = -I/usr/local/include -framework Cocoa -framework OpenGL

OBJ      = main.o functions.o menu.o level.o
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

main.o : main.c functions.c menu.c level.c
	@echo "compile main"
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) -c $<
	@echo "done..."

functions.o : functions.c
	@echo "compile functions"
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) -c $<
	@echo "done..."

menu.o : menu.c
	@echo "compile menu"
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) -c $<
	@echo "done..."

level.o : level.c
	@echo "compile menu"
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
