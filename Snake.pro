TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CFLAGS += -std=c99 -masm=intel


SOURCES += \
        field.c \
        game.c \
        snake_body.c

HEADERS += \
    field.h \
    movement.h \
    snake_body.h \
    types.h
