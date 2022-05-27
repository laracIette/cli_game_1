#include "Player.h"
#include "global.h"


Player::Player()
{
}

// set //
void Player::setHealthPoints( int hPoints )
{
    healthPoints = hPoints;
}
void Player::setStamina( int sta )
{
    this->stamina = sta;
}
void Player::setShield( int shl )
{
    this->shield = shl;
}
void Player::setSkippedTurns( int skp )
{
    this->skippedTurns = skp;
}
void Player::setPlayerNumber( int num )
{
    this->playerNumber = num;
}
void Player::setEnemyNumber( int num )
{
    this->enemyNumber = num;
}



// get //
int Player::getHealthPoints()
{
    return this->healthPoints;
}
int Player::getStamina()
{
    return this->stamina;
}
int Player::getShield()
{
    return this->shield;
}
int Player::getSkippedTurns()
{
    return this->skippedTurns;
}
int Player::getType()
{
    return this->playerType;
}

int Player::getCounterType()
{
    return this->counterType;
}
int Player::getPlayerNumber()
{
    return this->playerNumber;
}
int Player::getEnemyNumber()
{
    return this->enemyNumber;
}



// game //
bool Player::setType()
{
    std::cout << "Choose your type\n\n"
                 "1 : Electric\n"
                 "2 : Water\n"
                 "3 : Fire\n\n";

    for(;;)
    {
        for( int i{0}; i < 3; ++i )
        {
            if( isKeyPressed( i + '1' ) )
            {
                for( size_t k{0}; k < playersArray.size(); ++k )
                {
                    if( playersArray[k].getType() == i )
                    {
                        std::cout << "Type already taken\n\n";
                        return 0;
                    }
                }
                this->playerType = i;
                std::cout << "New Player added\n\n";
                return 1;
            }
        }
    }
}

void Player::setCounterType( int typ )
{
    if     ( getType() == 0 ) this->counterType = 2;
    else if( getType() == 1 ) this->counterType = 0;
    else if( getType() == 2 ) this->counterType = 1;
}

void Player::showAttacks()
{
    std::cout << "Simple attack (" << ATTACK_SIMPLE_DAMAGE << ")  : " << ATTACKS_ARRAY[this->playerType][0] << '\n'
              << "Double attack (" << ATTACK_DOUBLE_DAMAGE << ") : "  << ATTACKS_ARRAY[this->playerType][1] << '\n';
}

int Player::selectAttack()
{
    int number;

    for(;;)
    {
        if     ( isKeyPressed( '1' ) ) { number = 1; break; }
        else if( isKeyPressed( '2' ) ) { number = 2; break; }
    }


    if( number == 1 ) return ATTACK_SIMPLE_DAMAGE;
    else              return ATTACK_DOUBLE_DAMAGE;
}

void Player::reduceHealth( int dmg )
{
    if( getHealthPoints() - dmg > 0 )
    {
        setHealthPoints( getHealthPoints() - dmg );
    }
    else
    {
        setHealthPoints( 0 );
    }
}

void Player::increaseHealth( int hps )
{
    if( getHealthPoints() + hps < MAX_HEALTH_POINTS )
    {
        setHealthPoints( getHealthPoints() + hps );
    }
    else
    {
        setHealthPoints( MAX_HEALTH_POINTS );
    }
}

void Player::reduceStamina( int sta )
{
    setStamina( getStamina() - sta );
}

void Player::increaseStamina( int sta )
{
    if( getStamina() + sta < MAX_STAMINA )
    {
        setStamina( getStamina() + sta );
    }
    else
    {
        setStamina( MAX_STAMINA );
    }
}

void Player::reduceShield( int shd )
{
    if( getShield() - shd > 0 )
    {
        setShield( getShield() - shd );
    }
    else
    {
        setShield( 0 );
    }
}

void Player::increaseShield( int shd )
{
    if( getShield() + shd < MAX_SHIELD )
    {
        setShield( getShield() + shd );
    }
    else
    {
        setShield( MAX_SHIELD );
    }
}

void Player::increaseSkippedTurns(int skp)
{
    setSkippedTurns( getSkippedTurns() + skp );
}

void Player::showShortStats()
{
    std::cout << "Player "              << getPlayerNumber() << '\n'
              << "    Health Points : " << getHealthPoints() << '\n'
              << "    Stamina       : " << getStamina()      << "\n\n";
}

void Player::selectEnemy()
{
    for( size_t j{0}; j < playersArray.size(); ++j )
    {
        if( (int)(j + 1) != getPlayerNumber() )
        {
            playersArray[j].showShortStats();
        }
    }

    std::cout << "Player " << getPlayerNumber() <<" : Choose your enemy";

    for(;;)
    {
        for( size_t k{0}; k < playersArray.size(); ++k )
        {
            if( !isKeyPressed( k + 49 ) ) continue;

            if( (int)(k + 1) == getPlayerNumber() ) continue;

            setEnemyNumber( k );
            return;
        }
    }
}