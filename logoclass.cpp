#include "logoclass.h"
#include <QPainter>

LogoClass::LogoClass(QWidget *parent)
    : QWidget{parent},
      uiLogo(new Ui::LogoClass)
{
    uiLogo->setupUi(this);
}

void LogoClass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);
    QBrush backGr(Qt::GlobalColor::magenta);
    painter.setBrush(backGr);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    QBrush figBrush(Qt::GlobalColor::green);
    painter.setBrush(figBrush);
    QPen pen(Qt::blue, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawEllipse(500, 300, width()-150, height()-250 );
    QPen pencil(Qt::red, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pencil);
    painter.drawEllipse(3, 210, width()- 500 , height()-600 );


}
