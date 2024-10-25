#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_S21_TETRIS_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_S21_TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../parametr/parametr.h"

#define TETRIS_BLOCK_SIZE 4
#define PLAYFIELD_HEIGHT 19
#define PLAYFIELD_WIDTH 9

static const int figures[7][4][4][2] = {{
                                            {{0, -1}, {0, 0}, {0, 1}, {0, 2}},
                                            {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
                                            {{0, -1}, {0, 0}, {0, 1}, {0, 2}},
                                            {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
                                        },
                                        {
                                            {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
                                            {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
                                            {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
                                            {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
                                        },
                                        {
                                            {{0, -1}, {0, 0}, {0, 1}, {1, 1}},
                                            {{-1, 0}, {-1, 1}, {0, 0}, {1, 0}},
                                            {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
                                            {{-1, 0}, {0, 0}, {1, 0}, {1, -1}},
                                        },

                                        {
                                            {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
                                            {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
                                            {{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
                                            {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
                                        },

                                        {
                                            {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
                                            {{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
                                            {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
                                            {{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
                                        },

                                        {
                                            {{0, -1}, {0, 0}, {0, 1}, {1, 0}},
                                            {{-1, 0}, {0, 0}, {0, 1}, {1, 0}},
                                            {{-1, 0}, {0, -1}, {0, 0}, {0, 1}},
                                            {{-1, 0}, {0, -1}, {0, 0}, {1, 0}},
                                        },

                                        {
                                            {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
                                            {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},
                                            {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
                                            {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},
                                        }};

// Возвращает рандомный тип блока
BlockType GetRandomBlockType();

// Функция поворота блока по часовой
Direction GetNextBlockRotation(Direction block_rotation);

// Функция поворота блока против часовой
Direction GetPreviousBlockRotation(Direction block_rotation);

// Инициализация поля
void InitBoard(Parametrs* p_board);

// Функция возвращает число заполненных строк и удаляет их
int HandleBoardCompleteLines(Parametrs* p_board);

// Функция удаляет заполненную строку
void RemoveBoardLine(Parametrs* p_board, int line_index);

// Функция ищет пустую строку и сдвигает вниз строки которые над ней
void ApplyPhysics(Parametrs* p_board);

// Функция смещения строки вниз
void ShiftBoardDown(Parametrs* p_board, int empty_row_index);

// Функция копирования строки из index_src в index_dest
void CopyBoardLine(Parametrs* p_board, int index_dest, int index_src);

// Функция проверяет заполнена строка или нет
bool CheckBoardCompleteLine(Parametrs* p_board, int row_index);

// Главная функция - изменяет параметры в зависимости от сигнала
void setParametrs_tetris(Parametrs* paramet, UserAction_t signal);

// Функция создает новую фигуру
Figura CreateNewFigure();

// Функция добавляет фигуру на игровое поле
void add_figura_to_cell(Parametrs* paramet);

// Функция перемещает фигуру вниз на игровом поле
void move_down(Parametrs* parametr);

// Функция расчитывает новые кординаты фигуры
void MarkPredictedPositions(Parametrs* parametr, BlockType type, int delta_x,
                            int delta_y);

// Функция перемещения фигуры по горизонтали
void move_left_or_right(Parametrs* parametr, int a);

// Функция проверки премещения по горизонтали
bool check_move_left_or_right(Parametrs* parametr, int a);

// Функция проверки перемещения по вертикали
bool check_move_down(Parametrs* parametr);

// Функция проверяет на окончание игры
void check_game_over(Parametrs* parametr);

// Функция поворачивает фигуру
void rotation(Parametrs* parametr);

// Функция проверяет не прожата ли пауза
void check_pause(Parametrs* paramet, UserAction_t signal);

// Функция подсчитывания очков
void result(Parametrs* paramet);

// Функция сохранения результата
void file_record(Parametrs* paramet);

#endif