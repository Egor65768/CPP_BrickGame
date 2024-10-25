#include "s21_additinal_func.h"

namespace s21 {
void set_defoult_parametr(Parametrs* par) {
  par->inGame = false;
  par->inFast = false;
  par->inPause = false;
  par->numFast = 0;
  par->level = 1;
  par->record = 0;
  par->next_fig.block = kBlockL;
  par->next_fig.dir = kDirectionFirst;
  par->dir = Skip;
  par->size_snake = 0;
  par->apple.x_p = 0;
  par->apple.y_p = 0;
}

void save_record_to_file(int current_size) {
  std::ifstream inputFile(".record.txt");
  int record;
  if (inputFile.is_open()) {
    if (inputFile >> record) {
      inputFile.close();
    } else {
      inputFile.close();
      std::ofstream outputFile(".record.txt");
      if (outputFile.is_open()) {
        outputFile << 0;
        outputFile.close();
      }
      return;
    }
    if (record < current_size) {
      std::ofstream outputFile(".record.txt");
      if (outputFile.is_open()) {
        outputFile << current_size;
        outputFile.close();
      }
    }
  } else {
    std::ofstream outputFile(".record.txt");
    if (outputFile.is_open()) {
      outputFile << 0;
      outputFile.close();
    }
  }
}

int record_in_file() {
  std::ifstream inputFile(".record.txt");
  int record = 0;
  if (inputFile.is_open()) {
    if (inputFile >> record) {
      inputFile.close();
    }
  }
  return record;
}
};  // namespace s21