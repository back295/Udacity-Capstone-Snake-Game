#include "data.h"
#include <iostream>
#include <fstream>
#include "algorithm"
#include <sstream>
#include <string>

#define GAME_FILE_PATH "../snake.txt"

Player::Player(std::string name, int age, int score)
: name{name}, age{age}, score {score} {
}

Player::Player(std::string name, int age)
:name {name}, age {age} {
    score = 0;
}

Player::~Player() {}

bool Player::operator<(const Player &des) {
    return score > des.GetPlayerScore();
}

void GameData::StorePlayerData(const Player &player) {
    std::ofstream file;

    file.open(GAME_FILE_PATH, std::ios::in | std::ios::out | std::ios::app);

    if(!file.is_open()) {
        std::cout << "Open game file failed!" << std::endl;
        return;
    } else {
        file << player.GetPlayerName() << " " << player.GetPlayerAge() << " " << player.GetPlayerScore() << std::endl;
    }

    file.close();
}

std::vector<Player> GameData::ReadPlayerData()
{
    std::string name;
    std::string age;
    std::string score;
    std::string line;
     std::vector<Player> players;

    std::ifstream file(GAME_FILE_PATH);

    if(file.is_open()) {
        while(std::getline(file, line)) {
            std::istringstream sline (line);
            while(sline >> name >> age >> score) {
                players.emplace_back(Player(name, std::stoi(age), std::stoi(score)));
            }
        }
        file.close();
        std::cout << "Read player datas from file successfully." << std::endl;
    } else {
        std::cout << "Open file failed!" << std::endl;
    }
    return players;
}

std::vector<Player> GameData::ShowSortedPlayers(void)
{
    std::cout << "Show list of sorted players by score" << std::endl;
    std::vector<Player> players = ReadPlayerData();
    
    std::sort(players.begin(), players.end());

    return players;
}

void GameData::SetNewPlayerScore(int score)
{
    players.back().SetPlayerScore(score);
}

void GameData::AddNewPlayer(const Player &player)
{
    players.emplace_back(player);
}

Player GameData::GetNewPlayer()
{
    return players.back();
}