#include "Arena.h"

Arena::Arena()
{
}

// set //
void Arena::setSurfaceType( int sur )
{
    this->surfaceType = sur;
}

// get //
int Arena::getSurfaceType()
{
    return this->surfaceType;
}
