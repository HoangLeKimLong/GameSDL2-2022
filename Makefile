#OBJS specifies which files to compile as part of the project
OBJS = main.cpp RenderWindow.cpp Common_Func.cpp MenuGame.cpp Entity.cpp ThreatObject.cpp
#CC specifies which compiler we're using
CC = g++
#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:/sdl2_make/include
#LIBRARY_PATHS specifies the additional library paths we'll need
INCLUDE_PATHS = -LC:/sdl2_make/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w 
# -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =  -Imingw32 -ISDL2main -ISDL2 -ISDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME SDL_Platform.exe