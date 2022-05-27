#include "Arena.cpp"
#include "Player.cpp"

void runMenu();
void runGame();

std::vector<Player> playersArray;
Arena MyArena;

int main()
{

    system("cls");

    runMenu();
    std::cout << "See you next time";

    return 0;

}

void runMenu()
{
    bool isRunGame{false};
    int playerNumber{1};

    bool isPlayerTypeSucces{0};

    bool isRunning{true};
    while( isRunning )
    {
        std::cout << "1 : New Player, 2 : Start Game, 3 : Exit Game\n\n";
        for(;;)
        {

            if( isKeyPressed( '1' ) )
            {
                system("cls");
                if( playersArray.size() >= MAXIMUM_NUMBER_OF_PLAYERS )
                {
                    std::cout << "Maximum number of Players already reached\n"
                                 "2 : Start Game, 3 : Exit Game\n\n";
                    continue;
                }

                Player MyPlayer;
                MyPlayer.setPlayerNumber( playerNumber );

                isPlayerTypeSucces = MyPlayer.setType();

                if( isPlayerTypeSucces )
                {
                    playersArray.push_back( MyPlayer );
                    ++playerNumber;
                }

                break;
            }
            else if( isKeyPressed( '2' ) )
            {
                system("cls");
                if( playersArray.size() >= 2 )
                {
                    isRunGame = true;
                    isRunning = false;

                    MyArena.setSurfaceType( rand() % PROB_ARENA_SURFACE );
                }
                else
                {
                    std::cout << "Number of Players should be 2 or more to play\n\n";
                }

                break;
            }
            else if( isKeyPressed( '3' ) )
            {
                system("cls");
                isRunning = false;

                break;
            }
        }
    }
    if( isRunGame )
    {
        runGame();
    }
}


void runGame()
{
    bool isNext{false};

    int shieldBeforeAttack{0};
    int attackDamage{0};

    bool isRunning{true};
    while( isRunning )
    {
        for( size_t i{0}; i < playersArray.size(); ++i )
        {
            playersArray[i].selectEnemy();

            system("cls");

            std::cout << "Enemy : ";
            playersArray[playersArray[i].getEnemyNumber()].showShortStats();

            for(;;)
            {
                isNext = false;
                while( !isAnyKeyPressed() );

                if( isKeyPressed( 'H' ) )
                {
                    std::cout << "Help\n"
                              << "    Simple Attack Damages : " << ATTACK_SIMPLE_DAMAGE  << '\n'
                              << "    Simple Attack Stamina : " << ATTACK_SIMPLE_STAMINA << '\n'
                              << "    Double Attack Damages : " << ATTACK_DOUBLE_DAMAGE  << '\n'
                              << "    Double Attack Stamina : " << ATTACK_DOUBLE_STAMINA << '\n'
                              << "    Press S for simple attack, D for double attack\n"
                              << "    Press N to skip turn\n"
                              << "    Press P to show stats\n"
                              << "    Press ESCAPE to exit\n\n";
                }
                else if( isKeyPressed( 'S' ) )
                {
                    if( playersArray[i].getStamina() < ATTACK_SIMPLE_STAMINA )
                    {
                        std::cout << "Insufficient Stamina\n";
                    }
                    else
                    {
                        attackDamage = ATTACK_SIMPLE_DAMAGE;

                        if( (rand() % PROB_MALUS_SIMPLE_ATTACK == 0) and (playersArray[i].getCounterType() == MyArena.getSurfaceType()) )
                        {
                            attackDamage = ATTACK_SIMPLE_DAMAGE * MALUS_SIMPLE_ATTACK_MULTIPLIER;
                            std::cout << "Damage reducted because of surface and player type\n";
                        }
                        else if( (rand() % PROB_BONUS_DAMAGE_TAKEN == 0) and (playersArray[playersArray[i].getEnemyNumber()].getCounterType() == MyArena.getSurfaceType()) )
                        {
                            attackDamage = ATTACK_SIMPLE_DAMAGE * BONUS_DAMAGE_TAKEN_MULTIPLIER;
                            std::cout << "Damage increased because of surface and player type\n";
                        }

                        if( (rand() % PROB_DOUBLE_DAMAGE == 0) )
                        {
                            std::cout << "Double damage available\n"
                                         "1 : Yes, 2 : No\n";
                            for(;;)
                            {
                                if( isKeyPressed( '1' ) )
                                {
                                    attackDamage *= 2 ;
                                    break;
                                }
                                else if( isKeyPressed( '2' ) )
                                {
                                    break;
                                }
                            }
                        }

                        if( playersArray[i].getSkippedTurns() > 0 )
                        {
                            playersArray[i].setSkippedTurns( 0 );
                        }

                        shieldBeforeAttack = playersArray[playersArray[i].getEnemyNumber()].getShield();

                        if( shieldBeforeAttack > 0 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceShield( ATTACK_SIMPLE_SHIELD_DAMAGE );
                        }

                        if( shieldBeforeAttack == 0 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceHealth( attackDamage );
                            std::cout << "Simple Attack inflicted\n";
                        }
                        else if( shieldBeforeAttack == 1 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceHealth( attackDamage / 2 );
                            std::cout << "Damage divided by 2 because of shield\n"
                                      << "Simple Attack inflicted\n";
                        }
                        else
                        {
                            std::cout << "Damage stopped by shield\n";
                        }

                        playersArray[i].reduceStamina( ATTACK_SIMPLE_STAMINA );

                        isNext = true;
                    }
                }
                else if( isKeyPressed( 'D' ) )
                {
                    if( playersArray[i].getStamina() < ATTACK_DOUBLE_STAMINA )
                    {
                        std::cout << "Insufficient Stamina\n";
                    }
                    else
                    {
                        attackDamage = ATTACK_DOUBLE_DAMAGE;

                        if( (rand() % PROB_MALUS_DOUBLE_ATTACK == 0) and (playersArray[i].getCounterType() == MyArena.getSurfaceType()) )
                        {
                            attackDamage = ATTACK_DOUBLE_DAMAGE * MALUS_DOUBLE_ATTACK_MULTIPLIER;
                            std::cout << "Damage reducted because of surface and player type\n";
                        }
                        else if( (rand() % PROB_BONUS_DAMAGE_TAKEN == 0) and (playersArray[playersArray[i].getEnemyNumber()].getCounterType() == MyArena.getSurfaceType()) )
                        {
                            attackDamage = ATTACK_DOUBLE_DAMAGE * BONUS_DAMAGE_TAKEN_MULTIPLIER;
                            std::cout << "Damage increased because of surface and player type\n";
                        }

                        if( playersArray[i].getSkippedTurns() > 0 )
                        {
                            playersArray[i].setSkippedTurns( 0 );
                        }

                        shieldBeforeAttack = playersArray[playersArray[i].getEnemyNumber()].getShield();

                        if( shieldBeforeAttack > 0 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceShield( ATTACK_DOUBLE_SHIELD_DAMAGE );
                        }

                        if( shieldBeforeAttack == 0 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceHealth( attackDamage );
                            std::cout << "Double Attack inflicted\n";
                        }
                        else if( shieldBeforeAttack == 1 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceHealth( attackDamage * 2 / 3 );
                            std::cout << "Damage divided by 1.5 because of shield\n"
                                      << "Double Attack inflicted\n";
                        }
                        else if( shieldBeforeAttack == 2 )
                        {
                            playersArray[playersArray[i].getEnemyNumber()].reduceHealth( attackDamage / 3 );
                            std::cout << "Damage divided by 3 because of shield\n"
                                      << "Double Attack inflicted\n";
                        }
                        else
                        {
                            std::cout << "Damage stopped by shield\n";
                        }

                        playersArray[i].reduceStamina( ATTACK_DOUBLE_STAMINA );

                        isNext = true;
                    }
                }
                else if( isKeyPressed( 'N' ) )
                {
                    playersArray[i].increaseSkippedTurns( 1 );
                    std::cout << playersArray[i].getSkippedTurns() << " skipped turns in a row\n";

                    if( playersArray[i].getSkippedTurns() == 1 )
                    {
                        playersArray[i].increaseStamina( 1 );
                        playersArray[i].increaseHealth( 5 );
                    }
                    else if( playersArray[i].getSkippedTurns() == 2 )
                    {
                        playersArray[i].increaseStamina( 2 );
                        playersArray[i].increaseHealth( 6 );
                        playersArray[i].increaseShield( 1 );
                    }
                    else if( playersArray[i].getSkippedTurns() == 3 )
                    {
                        playersArray[i].increaseShield( 2 );
                    }

                    isNext = true;
                }
                else if( isKeyPressed( 'P' ) )
                {
                    playersArray[i].showShortStats();
                }
                else if( isKeyPressed( VK_ESCAPE ) )
                {
                    return;
                }

                if( isNext )
                {
                    std::cout << "\nPress anything\n";
                    while( !isAnyKeyPressed() );
                    while( isAnyKeyPressed() );

                    system("cls");
                    break;
                }
            }
        }
    }
}