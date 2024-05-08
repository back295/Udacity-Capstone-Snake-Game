#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "data.h"
#include <memory>
class GameManager {
    public:
        GameManager(bool quit = false);
        bool GameManagerInit(void);
        void GameManagerSetNewPlayerScore(int score);
        void GameManagerStoreNewPlayerData();
        bool quit;
        ~GameManager() = default;
    private:
        std::unique_ptr<GameData> gameData;
};

#endif /* _GAMEMANAGER_H */