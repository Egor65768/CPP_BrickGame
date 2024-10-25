#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_S21_ADDITIONAL_FUNC
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_S21_ADDITIONAL_FUNC

#include <fstream>

#include "../../parametr/parametr.h"

namespace s21 {
void set_defoult_parametr(Parametrs* par);
void save_record_to_file(int record);
int record_in_file();
};  // namespace s21

#endif