#include "Sprites.h"

Sprites::Sprites(){

  for(int i = 0; i < 8; i++){
    pieceTypes[0][i] = Square[i];
    pieceTypes[1][i] = Pipe_0[i];
    pieceTypes[2][i] = Zig_0[i];
    pieceTypes[3][i] = T_0[i];
    pieceTypes[4][i] = L_0[i];
  }
}