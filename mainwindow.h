#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLayout>

#include <QMainWindow>
#include <QLineSeries>
#include <oscillatorcontrol.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void __changeTheRange(int range);
    void __changeTheShow(int);

private:
    Ui::MainWindow *ui;

    int theScaleRange;
    bool showSinCosComponents;

    Signal *primo;
};

#endif // MAINWINDOW_H
