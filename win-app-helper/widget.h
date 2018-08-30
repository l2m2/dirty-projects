#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Windows.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_findProcess_clicked();

    void on_pushButton_findWindowHandle_clicked();

    void on_pushButton_closeWindowHandle_clicked();

    void on_pushButton_bind_clicked();

    void on_pushButton_go_clicked();

private:
    Ui::Widget *ui;
    HWND wnd_;
};

#endif // WIDGET_H
