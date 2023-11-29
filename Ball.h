#pragma once

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
// #include <cmath>
#include <QPushButton>
#include <QLineEdit>
#include <QRegularExpression>


class Ball : public QWidget {
public:
    explicit Ball(QWidget* parent = nullptr);

    void reset();

protected:
    void paintEvent(QPaintEvent*) override;
private:
    void move();

    void hideAllButtonsExceptStop();

    void showAllButtonsExceptStop();

    void onStartButtonClicked();

    void onStopButtonClicked();

    void onSpeedButtonClicked();

    void onRadiusButtonClicked();

    void onAngleButtonClicked();

    void onFieldSizeButtonClicked();

    double x, y; // координаты центра шарика
    double vx, vy; // скорости по осям
    double angle; // угол направления движения
    double speed; // скорость
    double radius; // радиус шарика
    int LoW, HoH;

    QTimer* timer; // таймер для обновления экрана

    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* speedButton;
    QPushButton* angleButton;
    QPushButton* radiusButton;
    QPushButton* fieldSizeButton;

    QLineEdit *speedLineEdit;
    QLineEdit *angleLineEdit;
    QLineEdit *radiusLineEdit;
    QLineEdit *fieldSizeLineEdit;
};
