#include "radiusprogressbar.h"
#include <QPainter>

RadiusProgressBar::RadiusProgressBar(QWidget *parent) : QProgressBar(parent)
{
    setMinimum(0);
    setMaximum(589);
    setValue(0);
}

void RadiusProgressBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect = QRect(0, 0, width(), height()/2);
    QRect textRect = QRect(0, height()/2, width(), height()/2);

    const double k = (double)(value() - minimum()) / (maximum()-minimum());
    int x = (int)(rect.width() * k);
    QRect fillRect = rect.adjusted(0, 0, x-rect.width(), 0);

    QString valueStr = QString("%1%").arg(QString::number(value()));
    QPixmap buttomMap = QPixmap("C:\\Users\\jsjtx\\Desktop\\bowbow\\resource\\radius_back.png");
    QPixmap fillMap = QPixmap("C:\\Users\\jsjtx\\Desktop\\bowbow\\resource\\radius_front.png");

    //画进度条
    p.drawPixmap(rect, buttomMap);
    p.drawPixmap(fillRect, fillMap);

}

