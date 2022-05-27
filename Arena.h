#include <iostream>

#ifndef MY_ARENA_H
#define MY_ARENA_H

// je sais pas pourquoi j ai fait ce fichier //

class Arena
{
    int surfaceType;


public:
    Arena();

    // set //
    void setSurfaceType( int sur );

    // get //
    int getSurfaceType();

};

#endif // MY_ARENA_H