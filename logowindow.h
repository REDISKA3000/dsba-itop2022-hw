#ifndef LOGOWINDOW_H
#define LOGOWINDOW_H

#include <QWidget>
#include <logoclass.h>

namespace Ui {
class LogoWindow;
}

class LogoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogoWindow(QWidget *parent = nullptr);
    ~LogoWindow();

private:
    Ui::LogoWindow *ui;
    LogoClass* _logo;
signals:
    void goBack();
};

#endif // LOGOWINDOW_H
