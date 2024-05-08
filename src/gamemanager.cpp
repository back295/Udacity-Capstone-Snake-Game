#include <iostream>
#include "gamemanager.h"
#include "data.h"
#include <vector>
#include <memory>

GameManager::GameManager(bool quit) : quit{quit} {
    gameData = std::make_unique<GameData>();
};
bool GameManager::GameManagerInit(void)
{
    char keyPress;
    std::string name, temp;
    int age, score;
    bool completed = false;

    std::cout << "Press S  : Start a new game" << std::endl;
    std::cout << "Press H  : Get top of best score" << std::endl;
    std::cout << "Press Q  : Quit the game" << std::endl;
    std::cout << ">> : ";

    while((std::cin >> keyPress)) {
        std::cin.clear();
        while(std::cin.get() != '\n') {
            break;
        }

        if(keyPress != 'S' && keyPress != 'H'  && keyPress != 'Q' && keyPress != 's' && keyPress != 'h' && keyPress != 'q') {
            std::cout << "Please press correct key according to the guide above." << std::endl;
            std::cout << "Please re-enter your choice." << std::endl ;
            std::cout << " >> : ";
        } else {
            break;
        } 
    }
    switch (keyPress) {
        case 's':
        case 'S':
        {
            std::cout << "Starting a new game ..." << std::endl;
            std::cout << "Enter your nickname: ";
            std::cin >> name;
            while(std::cin.get() != '\n') {break;}
            std::cin.clear();
            do {
                std::cout << "Enter your age: ";
                std::cin >> temp;
                for(char &c : temp) {
                    if((c < '0' || c > '9')) {
                        std::cout << "Please re-enter your age, only number characters" << std::endl;
                        break;
                    } else {
                        completed = true;
                    }
                }
                if(completed) {
                    age = std::stoi(temp);
                }
                if((age < 10 || age > 100) && completed) {
                    completed = false;
                    std::cout << "Your age is between 10 and 99, please re-enter your age." << std::endl;
                }
            }while(!completed);
            completed = false;
            while(std::cin.get() != '\n') {break;}
            std::cout << std::endl;
            Player newPlayer (name, age);
            gameData->AddNewPlayer(newPlayer);
            return true;
            break;
        }
        case 'h':
        case 'H': {
            std::cout << "Get top 10 of best scores" << std::endl;
            std::vector<Player> players = gameData->ShowSortedPlayers();
            int count = 0;
            for(auto &item : players) {
                count++;
                std::cout << "Name: " << item.GetPlayerName() << " | Age: " << std::to_string(item.GetPlayerAge()) << " | Score: " << std::to_string(item.GetPlayerScore()) << std::endl;
                if(count >= 10) {
                    break;
                }
            }
            return false;
            break;
        }
        case 'q':
        case 'Q': {
            std::cout << "Quit the game." << std::endl;
            quit = true;
            return false;
        }
        default:
            return false;
            break;
    }
}   

void GameManager::GameManagerSetNewPlayerScore(int score) {
    gameData->SetNewPlayerScore(score);
}

void GameManager::GameManagerStoreNewPlayerData()
{
    gameData->StorePlayerData(gameData->GetNewPlayer());
}