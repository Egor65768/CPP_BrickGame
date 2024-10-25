#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "../brick_game/controller/s21_controller.h"
#include "../brick_game/parametr/parametr.h"
#include "../brick_game/snake/additinal_func/s21_additinal_func.h"
#include "../brick_game/snake/s21_snake.h"

TEST(test_snake, snake_test_start) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  ASSERT_TRUE(!parametr.inPause);
  ASSERT_TRUE(!parametr.inFast);
  ASSERT_TRUE(parametr.size_snake == 4);
  ASSERT_TRUE(parametr.level == 1);
}

TEST(test_snake, snake_test_fast) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  signal = Up;
  snake_controller(signal, &parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  ASSERT_TRUE(!parametr.inPause);
  ASSERT_TRUE(parametr.inFast);
  ASSERT_TRUE(parametr.level == 1);
}

TEST(test_snake, snake_test_Pause) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(!parametr.inPause);
  signal = Pause;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  ASSERT_TRUE(parametr.inPause);
}

TEST(test_snake, snake_test_GameOver) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(!parametr.inPause);
  signal = Skip;
  for (int i = 0; i < 9; i++) {
    snake_controller(signal, &parametr);
  }
  ASSERT_TRUE(!parametr.inGame);
}

TEST(test_snake, snake_test_right) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 5);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  ASSERT_TRUE(parametr.size_snake == 4);
  signal = Right;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 6);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  ASSERT_TRUE(parametr.inGame);
}

TEST(test_snake, snake_test_left) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 5);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  ASSERT_TRUE(parametr.size_snake == 4);
  signal = Left;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 4);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  ASSERT_TRUE(parametr.inGame);
}

TEST(test_snake, snake_test_turn) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 5);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  ASSERT_TRUE(parametr.size_snake == 4);
  signal = Left;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 4);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 11);
  signal = Down;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 4);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 10);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 4);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 9);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 4);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 8);
  ASSERT_TRUE(parametr.inFast);
  ASSERT_TRUE(parametr.inGame);
}

// врезается себе в хвост
TEST(test_snake, snake_test_crash) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.size_snake == 4);
  signal = Skip;
  for (int i = 0; i < 3; i++) {
    parametr.apple.x_p = BOARD_WIDTH / 2;
    parametr.apple.y_p = BOARD_HEIGHT / 2 + 2 + i;
    snake_controller(signal, &parametr);
  }
  ASSERT_TRUE(parametr.inGame);
  signal = Left;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  signal = Down;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  signal = Right;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(!parametr.inGame);
}

TEST(test_snake, snake_test_1) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  s21::Snake_Game snake_game;
  s21::set_defoult_parametr(&parametr);
  snake_game.setSignal(signal);
  snake_game.set_parametrs(&parametr);
  ASSERT_TRUE(parametr.inGame);
  ASSERT_TRUE(parametr.size_snake == 4);
  signal = Pause;
  snake_game.check_speed_in_game(&parametr, signal);
  snake_game.setSignal(signal);
  snake_game.set_parametrs(&parametr);
  ASSERT_TRUE(parametr.inPause);
  signal = Pause;
  snake_game.check_speed_in_game(&parametr, signal);
  snake_game.setSignal(signal);
  snake_game.set_parametrs(&parametr);
  ASSERT_TRUE(!parametr.inPause);
  std::ofstream file(".record.txt");
  if (file.is_open()) {
    file << "ZZZZZ";
    file.close();
  }
  signal = Right;
  snake_game.check_speed_in_game(&parametr, signal);
  snake_game.setSignal(signal);
  snake_game.set_parametrs(&parametr);
  ASSERT_TRUE(parametr.inGame);
}

TEST(test_snake, snake_test_2) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  parametr.size_snake = 191;
  int k = 0;
  for (int i = 0; i < 20 && k != 191; i++) {
    for (int j = 0; j < 10 && k != 191; j++) {
      if (j % 2 == 0) {
        parametr.snake_arr[190 - k].x_p = j;
        parametr.snake_arr[190 - k].y_p = i;
      } else {
        parametr.snake_arr[190 - k].x_p = 9 - j;
        parametr.snake_arr[190 - k].y_p = i;
      }
      k++;
    }
  }
  parametr.apple.x_p = 5;
  parametr.apple.y_p = 19;
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 0);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 19);
  signal = Right;
  for (int i = 0; i < 9; i++) {
    snake_controller(signal, &parametr);
    ASSERT_TRUE(parametr.snake_arr[0].x_p == 1 + i);
    ASSERT_TRUE(parametr.snake_arr[0].y_p == 19);
  }
  ASSERT_TRUE(parametr.inGame);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(!parametr.inGame);
}

TEST(test_snake, snake_test_check_level_and_eat_appple) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  parametr.size_snake = 8;
  for (int i = 0; i < 8; i++) {
    parametr.snake_arr[i].x_p = 5;
    parametr.snake_arr[i].y_p = 15 - i;
  }
  parametr.apple.x_p = 5;
  parametr.apple.y_p = 16;
  signal = Up;
  ASSERT_TRUE(parametr.level == 1);
  ASSERT_TRUE(parametr.size_snake == 8);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.level == 2);
  ASSERT_TRUE(parametr.size_snake == 9);
}

TEST(test_snake, snake_test_fail_2) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  signal = Left;
  for (int i = 0; i < 6; i++) {
    snake_controller(signal, &parametr);
  }
  ASSERT_TRUE(!parametr.inGame);
}

TEST(test_snake, snake_test_3) {
  UserAction_t signal = Start;
  Parametrs parametr;
  s21::set_defoult_parametr(&parametr);
  snake_controller(signal, &parametr);
  parametr.size_snake = 188;
  int k = 0;
  for (int i = 0; i < 20 && k != 188; i++) {
    for (int j = 0; j < 10 && k != 188; j++) {
      if (j % 2 == 0) {
        parametr.snake_arr[187 - k].x_p = j;
        parametr.snake_arr[187 - k].y_p = i;
      } else {
        parametr.snake_arr[187 - k].x_p = 9 - j;
        parametr.snake_arr[187 - k].y_p = i;
      }
      k++;
    }
  }
  parametr.apple.x_p = 1;
  parametr.apple.y_p = 18;
  signal = Right;
  ASSERT_TRUE(parametr.snake_arr[0].x_p == 2);
  ASSERT_TRUE(parametr.snake_arr[0].y_p == 18);
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  signal = Up;
  snake_controller(signal, &parametr);
  ASSERT_TRUE(parametr.inGame);
  s21::Snake_Game snake_game;
  parametr.dir = Skip;
  snake_game.set_parametrs(&parametr);
  ASSERT_TRUE(!snake_game.check_apple_in_snake());
}