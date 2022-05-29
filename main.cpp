#include "Player.cpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runMenu();
void runGame();
void showAllStats();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Player> playersArray;   // get playerArray      from global.h
int arenaSurfaceType;               // get arenaSurfaceType from global.h

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    system("cls");   // clear cli

    runMenu();
    std::cout << "See you next time";

    return 0;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
            while( !isAnyKeyPressed() );   // while nothing pressed do nothing

            // if 1, 2 or 3 pressed //
            if( isKeyPressed( '1' ) )
            {
                system("cls");

                if( playersArray.size() >= MAXIMUM_NUMBER_OF_PLAYERS )
                {
                    std::cout << "Maximum number of Players already reached\n"
                                 "2 : Start Game, 3 : Exit Game\n\n";
                    continue;
                }

                Player MyPlayer;                           // new instance of Player
                MyPlayer.setPlayerNumber( playerNumber );

                isPlayerTypeSucces = MyPlayer.setType();   // true if MyPlayer chose a type not taken

                if( isPlayerTypeSucces )
                {
                    playersArray.push_back( MyPlayer );    // add MyPlayer to playersArray
                    ++playerNumber;
                }

                break;
            }

            else if( isKeyPressed( '2' ) )
            {
                system("cls");

                if( playersArray.size() >= 2 )   // if 2 players or more
                {
                    isRunning = false;   // exit menu
                    isRunGame = true;    // go to game

                    arenaSurfaceType = rand() % PROB_ARENA_SURFACE;   // surface is random
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

                isRunning = false;   // exit menu

                break;
            }
        }
    }

    if( isRunGame )
    {
        runGame();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runGame()
{
    bool isNext{false};

    bool isRunning{true};
    while( isRunning )
    {
        for( size_t i{0}; i < playersArray.size(); ++i )
        {
            playersArray[i].selectEnemy();   // set enemy of current player

            system("cls");

            std::cout << "Enemy : ";
            playersArray[playersArray[i].getEnemyNumber()].showShortStats();   // show current player's enemy's stats

            //showAllStats();

            for(;;)
            {
                isNext = false;
                while( !isAnyKeyPressed() );   // while nothing pressed do nothing

                // if H, S, D, N or P pressed //
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
                    if( playersArray[i].getStamina() < ATTACK_SIMPLE_STAMINA )   // stamina check for simple attack
                    {
                        std::cout << "Insufficient Stamina\n";
                    }
                    else
                    {
                        playersArray[i].reduceStamina( ATTACK_SIMPLE_STAMINA );

                        if( rand() % PROB_DODGE == 0 )
                            std::cout << "Enemy dodged attack\n";
                        else
                            playersArray[i].simpleAttack();   // do simple attack

                        isNext = true;   // go to next player
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
                        playersArray[i].reduceStamina( ATTACK_DOUBLE_STAMINA );

                        if( rand() % PROB_DODGE == 0 )
                            std::cout << "Enemy dodged attack\n";
                        else
                            playersArray[i].doubleAttack();

                        isNext = true;
                    }
                }

                else if( isKeyPressed( 'N' ) )
                {
                    playersArray[i].skipTurn();

                    isNext = true;
                }

                else if( isKeyPressed( 'P' ) )
                {
                    playersArray[i].showShortStats();
                }

                else if( isKeyPressed( VK_ESCAPE ) )
                {
                    return;   // exit run and game
                }


                if( isNext )
                {
                    // wait for press and release any button to go to next player //
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

void showAllStats()
{
    for( size_t i{0}; i < playersArray.size(); ++i )
    {
        std::cout << "Player "        << playersArray[i].getPlayerNumber() << '\n'
                  << "Counter type  " << playersArray[i].getCounterType()  << '\n'
                  << "Enemy number  " << playersArray[i].getEnemyNumber()  << '\n'
                  << "Health points " << playersArray[i].getHealthPoints() << '\n'
                  << "Shield        " << playersArray[i].getShield()       << '\n'
                  << "Skipped turns " << playersArray[i].getSkippedTurns() << '\n'
                  << "Stamina       " << playersArray[i].getStamina()      << '\n'
                  << "Type          " << playersArray[i].getType()         << "\n\n";
    }
}