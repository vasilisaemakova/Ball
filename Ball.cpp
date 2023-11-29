#include "Ball.h"

namespace values
{
    uint LoW = 800; // размеры площадки
    uint HoH = 600;
    uint speed = 20;
    uint angle = 45;
    uint radius = 25;
};

Ball::Ball(QWidget *parent) : QWidget(parent)
{
    reset(); // начальное состояние шарика и размера окна
    timer = new QTimer(this); // таймер для обновления экрана
    connect(timer, &QTimer::timeout, this, &Ball::move); // подключаем обработчик движения
    timer->start(20); // запускаем таймер с интервалом 20 мс

    startButton = new QPushButton("Start", this);
    stopButton = new QPushButton("Stop", this);
    connect(startButton, &QPushButton::clicked, this, &Ball::onStartButtonClicked);
    startButton->move(10, 10);
    connect(stopButton, &QPushButton::clicked, this, &Ball::onStopButtonClicked);
    stopButton->move(10, 60);

    speedLineEdit = new QLineEdit(this);
    speedButton = new QPushButton("Enter speed", this);
    connect(speedButton, &QPushButton::clicked, this, &Ball::onSpeedButtonClicked);
    speedButton->move(10, 100);
    speedLineEdit->move(10, 140);

    angleLineEdit = new QLineEdit(this);
    angleButton = new QPushButton("Enter angle", this);
    connect(angleButton, &QPushButton::clicked, this, &Ball::onAngleButtonClicked);
    angleButton->move(10, 180);
    angleLineEdit->move(10, 220);

    radiusLineEdit = new QLineEdit(this);
    radiusButton = new QPushButton("Enter radius", this);
    connect(radiusButton, &QPushButton::clicked, this, &Ball::onRadiusButtonClicked);
    radiusButton->move(10, 260);
    radiusLineEdit->move(10, 300);

    fieldSizeLineEdit = new QLineEdit("Format: WxH", this);
    fieldSizeButton = new QPushButton("Enter field size", this);
    connect(fieldSizeButton, &QPushButton::clicked, this, &Ball::onFieldSizeButtonClicked);
    fieldSizeButton->move(10, 340);
    fieldSizeLineEdit->move(10, 380);
}

void Ball::reset()
{
    LoW = values::LoW;
    HoH = values::HoH;
    x = LoW / 2;
    y = HoH / 2;
    vx = 0;
    vy = 0;
    angle = (360 - values::angle) * M_PI / 180;
    speed = 0;
    radius = values::radius;
    resize(LoW, HoH);
}

void Ball::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
}

void Ball::move()
{
    double dt = 0.02; // шаг по времени
    double g = 9.81; // ускорение свободного падения
    double k = 0.9; // коэффициент упругости стенок

    // движение по прямой с постоянной скоростью
    x += vx * dt;
    y += vy * dt;

    // гравитация
    vy += g * dt;

    // столкновение со стенками
    if (x - radius < 0) {
        vx = -vx * k;
        x = radius;
        angle = M_PI - angle;
    }
    if (x + radius > LoW) {
        vx = -vx * k;
        x = LoW - radius;
        angle = M_PI - angle;
    }
    if (y - radius < 0) {
        vy = -vy * k;
        y = radius;
        angle = -angle;
    }
    if (y + radius > HoH) {
        vy = -vy * k;
        y = HoH - radius;
        angle = -angle;
    }

    // поворот направления движения
    vx = speed * cos(angle);
    vy = -speed * sin(angle);

    update(); // обновляем экран
}

void Ball::hideAllButtonsExceptStop()
{
    startButton->hide();
    speedButton->hide();
    speedLineEdit->hide();
    radiusButton->hide();
    radiusLineEdit->hide();
    angleButton->hide();
    angleLineEdit->hide();
    fieldSizeButton->hide();
    fieldSizeLineEdit->hide();
}

void Ball::showAllButtonsExceptStop()
{
    startButton->show();
    speedButton->show();
    speedLineEdit->show();
    radiusButton->show();
    radiusLineEdit->show();
    angleButton->show();
    angleLineEdit->show();
    fieldSizeButton->show();
    fieldSizeLineEdit->show();
}

void Ball::onStartButtonClicked()
{
    reset();
    speed = values::speed;
    hideAllButtonsExceptStop();
    update();
}

void Ball::onStopButtonClicked()
{
    showAllButtonsExceptStop();
    reset();
    update();
}

void Ball::onSpeedButtonClicked()
{
    QString text = speedLineEdit->text();
    bool ok;
    uint data = text.toUInt(&ok, 10);
    if (!ok) {
        return;
    }
    values::speed = data;
}

void Ball::onRadiusButtonClicked()
{
    QString text = radiusLineEdit->text();
    bool ok;
    uint data = text.toUInt(&ok, 10);
    if (!ok) {
        return;
    }
    values::radius = data;
}

void Ball::onAngleButtonClicked()
{
    QString text = angleLineEdit->text();
    bool ok;
    uint data = text.toUInt(&ok, 10);
    if (!ok) {
        return;
    }
    values::angle = data;
}

void Ball::onFieldSizeButtonClicked()
{
    QString text = fieldSizeLineEdit->text();
    QRegularExpression re;
    re.setPattern(R"(^\d+x\d+$)");
    if (!re.match(text).hasMatch()) {
        return;
    }
    auto str = text.toStdString();
    auto i = str.find('x');
    char *end;
    values::LoW = std::strtol(str.substr(0, i).c_str(), &end, 10);
    values::HoH = std::strtol(str.substr(i + 1).c_str(), &end, 10);
}