#ifndef LOGOCLASS_H
#define LOGOCLASS_H

#include <QWidget>
#include "ui_logoclass.h"

class LogoClass : public QWidget
{
    Q_OBJECT
public:
    explicit LogoClass(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::LogoClass* uiLogo;
signals:

};

#endif // LOGOCLASS_H
