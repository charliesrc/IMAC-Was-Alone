CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -L/usr/local/lib -lSDL -lSDLmain -lSDL_image
INCLUDES = -I/usr/local/include -framework Cocoa -framework OpenGL

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

OBJ      = main.o functions.o
RM       = rm -f
BIN      = IMACWasAlone
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB) $(INCLUDES) -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean :
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ_FILES) $(BIN)

tar : clean
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)
