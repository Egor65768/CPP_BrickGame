#include "s21_controller.h"

void snake_controller(UserAction_t signal, Parametrs* paramet) {
  s21::Snake_Game snake;
  snake.check_speed_in_game(paramet, signal);
  snake.setSignal(signal);
  if (signal != UserAction_t::Pause) {
    snake.set_parametrs(paramet);
  }
}