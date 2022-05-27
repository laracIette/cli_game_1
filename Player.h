#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MY_PLAYER_H
#define MY_PLAYER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Player
{
    int healthPoints{100};
    int stamina{10};

    int shield{3};

    int skippedTurns{0};

    int playerType;
    int counterType;

    int playerNumber{0};
    int enemyNumber{0};


public:
    Player();


    // set //
    void setHealthPoints( int hps );
    void setStamina( int sta );

    void setShield( int shl );

    void setDodge( int ddg );
    void setSkippedTurns( int skp );

    bool setType();
    void setCounterType( int typ );

    void setPlayerNumber( int num );
    void setEnemyNumber( int num );


    // get //
    int getHealthPoints();
    int getStamina();

    int getShield();

    int getDodge();
    int getSkippedTurns();

    int getType();
    int getCounterType();

    int getPlayerNumber();
    int getEnemyNumber();


    // game //
    void showAttacks();

    int selectAttack();

    void reduceHealth( int dmg );
    void increaseHealth( int hps );

    void reduceStamina( int sta );
    void increaseStamina( int sta );

    void reduceShield( int shd );
    void increaseShield( int shd );

    void increaseSkippedTurns( int skp );

    void showShortStats();

    void selectEnemy();

    void simpleAttack();
    void doubleAttack();

    void skipTurn();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MY_PLAYER_H