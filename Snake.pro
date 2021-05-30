TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CFLAGS += -std=c99 -masm=intel


SOURCES += \
        field.c \
        game.c \
        menu.c \
        snake_body.c

HEADERS += \
    field.h \
    menu.h \
    movement.h \
    snake_body.h \
    types.h
