#include "Player.cpp"

void runMenu();
void runGame();

std::vector<Player> playersArray;
int arenaSurfaceType;

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

                    arenaSurfaceType = rand() % PROB_ARENA_SURFACE;
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
                        playersArray[i].simpleAttack();

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