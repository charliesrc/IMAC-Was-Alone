CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -lSDL -lGLU -lGL -lm -lSDL_image
INCLUDES = 

OBJ      = main.o functions.o
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

main.o : main.c functions.c
	@echo "compile main"
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) -c $<  
	@echo "done..."


functions.o : functions.c
	@echo "compile functions"
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

