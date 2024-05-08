#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  running = true;
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  
  obstacle_thread = std::thread(&Game::PlaceObstacle, this);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    mutex.lock();
    if((!running && !snake.alive) || (!running & snake.alive)) {
      obstacle_thread.join();
    }
    renderer.Render(snake, food, obstacle);
    mutex.unlock();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
void Game::PlaceObstacle()
{
  int x, y;
  SDL_Point new_obstacle;

  std::chrono::time_point start = std::chrono::steady_clock::now();
  while(true) {
    mutex.lock();
    if(running && snake.alive) {
      if(std::chrono::steady_clock::now() - start > std::chrono::seconds(10)) {
        x = random_w(engine);
        y = random_h(engine);
        if(!snake.SnakeCell(x,y) && food.x != x && food.y != y) {
          new_obstacle.x = x;
          new_obstacle.y = y;
          obstacle.emplace_back(new_obstacle);
          start = std::chrono::steady_clock::now();
        }
      }
    } else {
        mutex.unlock();
        break;
    }
    mutex.unlock();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) {
      return;
  };

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  mutex.lock();
  for(const SDL_Point &item : obstacle) {
    if(item.x == new_x && item.y == new_y) {
      snake.alive = false;
      mutex.unlock();
      break;
    }
  }
  mutex.unlock();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
