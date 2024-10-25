#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_S21_SNAKE_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_S21_SNAKE_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../parametr/parametr.h"
#include "additinal_func/s21_additinal_func.h"

namespace s21 {

class Snake_Game {
 public:
 // Конструктор по умолчанию
  Snake_Game();

  // Этот метод устанавливает начальные параметры 
  void init_defolt_snake_game();

  // Этот метод синхронизирует состояние класса с переданными параметрами 
  void converting_parametr_to_game(Parametrs* paramet);

  // Этот метод устанавливает яблоко на поле 
  void apple_location();

  // Этот метод отвечает за перемещение змеи 
  void move_snake();

  // Этот метод проверяет статус игры
  void check_fail_game();

  // Этот метод проверяет сигнал 
  void check_signal();

  // Этот метод проверяет сьедено ли яблоко
  void check_apple_in_game();

  // Этот метод управляет скоростью игры и состояние паузы
  void check_speed_in_game(Parametrs* paramet, UserAction_t signal1);

  // Этот метод переносит змейку из класса в parametr
  void copy_snake(Parametrs* paramet);
  void setSignal(UserAction_t signal1);
  void set_parametrs(Parametrs* paramet);
  void conversion_to_parametrs(Parametrs* paramet);
  bool check_apple_in_snake();

 private:
  static constexpr int FIELD_HEIGHT = 20;
  static constexpr int FIELD_WIDTH = 10;
  static constexpr int INITION_POSITION_SNAKE_X = FIELD_WIDTH / 2;
  static constexpr int INITION_POSITION_SNAKE_Y = FIELD_HEIGHT / 2 + 1;
  static constexpr int START_SIZE_SNAKE = 4;
  static constexpr int MAX_LEVEL = 10;
  static constexpr int DIFFERENCE_BETWEEN_LEVEL = 5;
  bool game_status = false;
  int current_level;
  std::vector<My_snake> m_snake;
  UserAction_t m_dir;
  UserAction_t signal = Start;
  My_snake m_apple;
};

};  // namespace s21
#endif