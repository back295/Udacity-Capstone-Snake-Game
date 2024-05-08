#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
#include <memory>

class Player {
    private:
        std::string name;
        int age;
        int score;
    public:
        Player(std::string name, int age);
        Player(std::string name, int age, int score);
        ~Player();
        std::string GetPlayerName(void) const {return name;};
        int GetPlayerAge(void) const {return age;};
        int GetPlayerScore(void) const {return score;};
        void SetPlayerName(std::string name) {this->name = name;};
        void SetPlayerAge(int age) {this->age = age;};
        void SetPlayerScore(int score) {this->score = score;}; 
        bool operator<(const Player &des);
};

class GameData {
    private:
        std::vector<Player> players;
    public:
        void StorePlayerData(const Player &player);
        std::vector<Player> ReadPlayerData(void);
        std::vector<Player> ShowSortedPlayers(void);
        void SetNewPlayerScore(int score);
        void AddNewPlayer(const Player &player);
        Player GetNewPlayer();
};

#endif /* DATA_H */