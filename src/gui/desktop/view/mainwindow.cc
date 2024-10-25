#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timerId = startTimer(DELAY);
  renderingStartSidebar();
  s21::set_defoult_parametr(&parametr);
}

void MainWindow::timerEvent(QTimerEvent *e) {
  Q_UNUSED(e);
  if (INGame && game_snake) {
    timeEventSnake();
  } else if (INGame && !game_snake) {
    timeEventTetris();
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key == Qt::Key_A) {
    signal = UserAction_t::Left;
  } else if (key == Qt::Key_W) {
    signal = UserAction_t::Down;
  } else if (key == Qt::Key_D) {
    signal = UserAction_t::Right;
  } else if (key == Qt::Key_S) {
    signal = UserAction_t::Up;
  } else if (key == Qt::Key_Q) {
    signal = UserAction_t::Action;
  } else if ((key == Qt::Key_Return || key == Qt::Key_Enter) &&
             INGame == false) {
    signal = UserAction_t::Start;
    INGame = true;
    if (radiobutton1->isChecked()) {
      s21::set_defoult_parametr(&parametr);
      game_snake = true;
    } else {
      s21::set_defoult_parametr(&parametr);
      game_snake = false;
      FastGame = true;
    }
    label->setText("Игра.Для паузы:\nнажмите P");
  } else if (key == Qt::Key_P && INGame == true) {
    signal = UserAction_t::Pause;
    if (parametr.inPause) {
      label->setText("Игра.Для паузы:\nнажмите P");
    } else {
      label->setText("Пауза.Для продолжения:\nнажмите P");
    }
  } else if (key == Qt::Key_Escape) {
    gameOver();
  }
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (game_snake) {
    doDrawing();
  } else {
    doDrawingTetris();
  }
}

void MainWindow::doDrawingTetris() {
  for (int j = 0; j < FIELD_HEIGHT; j++) {
    for (int i = 0; i < FIELD_WIGTH; i++) {
      paintPole(i, j);
    }
  }
  paintNextFigure();
}

void MainWindow::paintPole(int i, int j) {
  QPainter qp(this);
  if (parametr.pole[i][j].block == kBlockI) {
    qp.setBrush(Qt::red);
  } else if (parametr.pole[i][j].block == kBlockJ) {
    qp.setBrush(Qt::magenta);
  } else if (parametr.pole[i][j].block == kBlockL) {
    qp.setBrush(Qt::yellow);
  } else if (parametr.pole[i][j].block == kBlockO) {
    qp.setBrush(Qt::darkMagenta);
  } else if (parametr.pole[i][j].block == kBlockS) {
    qp.setBrush(Qt::green);
  } else if (parametr.pole[i][j].block == kBlockT) {
    qp.setBrush(Qt::blue);
  } else if (parametr.pole[i][j].block == kBlockZ) {
    qp.setBrush(Qt::cyan);
  } else if (parametr.pole[i][j].block == kBlockRes) {
    qp.setBrush(Qt::darkBlue);
  } else {
    qp.setBrush(Qt::white);
  }
  qp.drawRect(i * PIX_WIGTH, j * PIX_HEIGHT, PIX_WIGTH, PIX_HEIGHT);
}

void MainWindow::paintNextFigure() {
  QPainter qp(this);
  int x1, y1;
  int x = CORDINATE_X_OF_NEXT_FIGURA;
  int y = CORDINATE_Y_OF_NEXT_FIGURA;
  for (int i = 0; i < SIZE_FIGURA; i++) {
    x1 = x + figures[parametr.next_fig.block][parametr.next_fig.dir][i][0];
    y1 = y + figures[parametr.next_fig.block][parametr.next_fig.dir][i][1];
    qp.setBrush(Qt::darkGray);
    qp.drawRect(x1 * PIX_WIGTH, y1 * PIX_HEIGHT, PIX_WIGTH, PIX_HEIGHT);
  }
}

void MainWindow::timeEventTetris() {
  if (signal != UserAction_t::Down && FastGame) {
    FastGame = false;
  }
  if (signal == UserAction_t::Start ||
      (signal != UserAction_t::Up && FastGame == false &&
       parametr.inFast == true)) {
    killTimer(timerId);
    timerId = startTimer(DELAY_TETRIS);
    parametr.inFast = false;
  } else if (signal == UserAction_t::Up) {
    killTimer(timerId);
    timerId = startTimer(FAST_DELAY);
    FastGame = true;
    parametr.inFast = true;
  }
  tetris_controller(signal, &parametr);
  if (parametr.inGame) {
    this->repaint();
  } else {
    gameOver();
  }
  renderingSidebarDuringTheTetrisGame();
  signal = UserAction_t::Skip;
}

void MainWindow::timeEventSnake() {
  settingUpFPSforSnake();
  snake_controller(signal, &parametr);
  if (parametr.inGame) {
    this->repaint();
  } else {
    gameOver();
  }
  renderingSidebarDuringTheSnakeGame();
  if (parametr.size_snake == FIELD_HEIGHT * FIELD_WIGTH) {
    youwin();
  }
  signal = UserAction_t::Skip;
}

void MainWindow::renderingStartSidebar() {
  label = new QLabel("Для старта игры:\nнажмите Enter", this);
  label->setGeometry(260, 110, 270, 50);
  label1 = new QLabel("Текущий счет : ", this);
  label1->setGeometry(260, 30, 200, 50);
  label2 = new QLabel("Максимальный счет : ", this);
  label2->setGeometry(260, 65, 200, 50);
  label3 = new QLabel("Уровень : ", this);
  label3->setGeometry(260, 0, 200, 50);
  label4 = new QLabel("Скорость игры : ", this);
  label4->setGeometry(260, 150, 200, 50);
  radiobutton1 = new QRadioButton("Змейка", this);
  radiobutton2 = new QRadioButton("Тетрис", this);
  radiobutton1->setGeometry(260, 180, 200, 50);
  radiobutton2->setGeometry(260, 210, 200, 50);
  radiobutton1->setChecked(true);
}

void MainWindow::renderingSidebarDuringTheSnakeGame() {
  label1->setText("Текущий счет : " + QString::number(parametr.size_snake - 4));
  label2->setText("Максимальный счет : " + QString::number(parametr.record));
  label3->setText("Уровень : " + QString::number(parametr.level));
  label4->setText(
      "Скорость игры : " +
      QString::number(DELAY - inGamelevel * ACCELERATION_COEFFICIENT));
}

void MainWindow::renderingSidebarDuringTheTetrisGame() {
  label1->setText("Текущий счет : " + QString::number(parametr.size_snake));
  label2->setText("Максимальный счет : " + QString::number(parametr.record));
  label3->setText("Уровень : ");
  label4->setText("Скорость игры : ");
}

void MainWindow::settingUpFPSforSnake() {
  if (inGamelevel != parametr.level) {
    inGamelevel = parametr.level;
    killTimer(timerId);
    timerId = startTimer(DELAY - inGamelevel * ACCELERATION_COEFFICIENT);
  } else if (FastGame == false && parametr.inFast == true) {
    killTimer(timerId);
    timerId = startTimer(FAST_DELAY);
    FastGame = true;
  } else if (FastGame == true && parametr.inFast == false) {
    killTimer(timerId);
    timerId = startTimer(DELAY - inGamelevel * ACCELERATION_COEFFICIENT);
    FastGame = false;
  }
}

void MainWindow::doDrawing() {
  QPainter qp(this);
  for (int i = 0; i < FIELD_WIGTH; i++) {
    for (int j = 0; j < FIELD_HEIGHT; j++) {
      qp.drawRect(i * PIX_WIGTH, j * PIX_HEIGHT, PIX_WIGTH, PIX_HEIGHT);
    }
  }
  qp.setBrush(Qt::red);
  qp.drawRect(parametr.apple.x_p * PIX_WIGTH, parametr.apple.y_p * PIX_HEIGHT,
              PIX_WIGTH, PIX_HEIGHT);
  for (int i = 1; i < parametr.size_snake; i++) {
    qp.setBrush(Qt::green);
    qp.drawRect(parametr.snake_arr[i].x_p * PIX_WIGTH,
                parametr.snake_arr[i].y_p * PIX_HEIGHT, PIX_WIGTH, PIX_HEIGHT);
  }
  qp.setBrush(Qt::darkGreen);
  qp.drawRect(parametr.snake_arr[0].x_p * PIX_WIGTH,
              parametr.snake_arr[0].y_p * PIX_HEIGHT, PIX_WIGTH, PIX_HEIGHT);
}

void MainWindow::initGameSnake() {
  this->signal = UserAction_t::Start;
  parametr.inGame = false;
  this->setWindowTitle("BreakGame School 21");
  snake_controller(signal, &parametr);
  this->signal = UserAction_t::Pause;
}

void MainWindow::gameOver() {
  INGame = false;
  killTimer(timerId);
  timerId = startTimer(DELAY);
  QMessageBox::StandardButton replay =
      QMessageBox::question(this, "Game over", "Do you want to play again?",
                            QMessageBox::Yes | QMessageBox::No);
  if (replay == QMessageBox::No) {
    QApplication::quit();
  }
  label->setText("Для старта игры:\nнажмите Enter");
}

void MainWindow::youwin() {
  QMessageBox::information(this, "You Win", "You realy win");
  INGame = false;
  initGameSnake();
  label->setText("Для старта игры нажмите Enter");
}

MainWindow::~MainWindow() { delete ui; }
