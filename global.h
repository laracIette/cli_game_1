#include <windows.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------- constants --------------------------*/

// probas // rand() % PROB_EXEMPLE //
extern const int PROB_DODGE_GAIN{14};
extern const int PROB_DOUBLE_DAMAGE{30};
extern const int PROB_ARENA_SURFACE{6};
extern const int PROB_MALUS_SIMPLE_ATTACK{3};
extern const int PROB_MALUS_DOUBLE_ATTACK{2};
extern const int PROB_BONUS_DAMAGE_TAKEN{4};


// other //
extern const int MAX_HEALTH_POINTS{100};
extern const int MAX_STAMINA{10};
extern const int MAX_SHIELD{3};

extern const int ATTACK_SIMPLE_DAMAGE{9};
extern const int ATTACK_SIMPLE_STAMINA{1};

extern const int ATTACK_DOUBLE_DAMAGE{17};
extern const int ATTACK_DOUBLE_STAMINA{2};

extern const int SKIP_FIRST_TURN_STAMINA_GAIN{1};
extern const int SKIP_FIRST_TURN_HEALTH_POINTS_GAIN{5};

extern const int SKIP_SECOND_TURN_STAMINA_GAIN{2};
extern const int SKIP_SECOND_TURN_HEALTH_POINTS_GAIN{6};

extern const int ATTACK_SIMPLE_SHIELD_DAMAGE{2};
extern const int ATTACK_DOUBLE_SHIELD_DAMAGE{3};

extern const int MAXIMUM_NUMBER_OF_PLAYERS{5};


// multipliers // MULTIPLIED * MULTIPLIER //
extern const float MALUS_SIMPLE_ATTACK_MULTIPLIER{0.66f};
extern const float MALUS_DOUBLE_ATTACK_MULTIPLIER{0.50f};
extern const float BONUS_DAMAGE_TAKEN_MULTIPLIER{1.50f};


// arrays //
extern const std::string SURFACE_TYPES[6]{
    "electric",
    "water",
    "fire",
    "earth",
    "sand",
    "ice"
};

extern const std::string ATTACKS_ARRAY[3][2]{
    {"Zap",        "Lightning"},
    {"Splash",     "Tsunami"  },
    {"Fire punch", "Fireball" },
};

/*-------------------------- variables --------------------------*/

extern int arenaSurfaceType;


// vector for Player instances
extern std::vector<Player> playersArray;


/*-------------------------- functions --------------------------*/
bool isKeyPressed( char key )   // return if key is pressed
{
    if( GetKeyState( key ) & 0x8000 )   // if key pressed
    {
        while( GetKeyState( key ) & 0x8000 );   // while key pressed do nothing
        return true;
    }

    return false;
}


bool isAnyKeyPressed()   // return if any key is pressed
{
    for( char i{0}; i < 127; ++i)
    {
        if( GetKeyState( i ) & 0x8000 ) return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MY_GLOBALS_H