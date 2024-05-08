#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <thread>
#include "gamemanager.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  bool res;

  GameManager gameManager;
  std::cout << "WELCOM TO MY SNAKE GAME" << std::endl;
  std::cout << "=================================" << std::endl;
  while(!gameManager.quit) {
    res = gameManager.GameManagerInit();
    if(res) {
      Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
      Controller controller;
      Game game(kGridWidth, kGridHeight);
      game.Run(controller, renderer, kMsPerFrame);
      std::cout << "=================================" << std::endl;
      std::cout << "Your score: " << game.GetScore() << "\n";
      std::cout << "=================================" << std::endl;
      std::cout << std::endl;
      gameManager.GameManagerSetNewPlayerScore(game.GetScore());
      gameManager.GameManagerStoreNewPlayerData();
    } else if(!res && gameManager.quit) {
      return 0;
    } else {
      //Nothing
    };
  }

  return 0;
}