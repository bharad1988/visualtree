#-I/home/ajay/code/libs/raylib/src/
#-lraylib
#-L/home/ajay/code/libs/raylib/src/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ajay/code/libs/raylib/src/
gcc main.c  -o tree -I/home/ajay/code/libs/raylib/src/ -I../../src -lraylib  -lm -L/home/ajay/code/libs/raylib/src/
