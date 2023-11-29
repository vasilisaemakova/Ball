#include <QApplication>
#include "Ball.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Ball ball;
    ball.show();
    return QApplication::exec();
}