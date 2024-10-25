QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    mainwindow.cc \
    ../../../brick_game/snake/s21_snake.cc \
    ../../../brick_game/controller/s21_controller.cc \
    ../../../brick_game/controller/s21_tetris_controller.c \
    ../../../brick_game/tetris/s21_tetris.c \
    ../../../brick_game/snake/additinal_func/s21_additinal_func.cc

HEADERS += \
    mainwindow.h \
    ../../../brick_game/snake/s21_snake.h \
    ../../../brick_game/controller/s21_controller.h \
    ../../../brick_game/controller/s21_tetris_controller.h \
    ../../../brick_game/tetris/s21_tetris.h \
    ../../../brick_game/snake/additinal_func/s21_additinal_func.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
