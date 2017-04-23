#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLayout>

#include <QMainWindow>
#include <QLineSeries>
#include <oscillatorcontrol.h>
#include "signal.h"

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
    void _setUpOneOscillator(QString n,float f,float a,float p, QWidget *parent);

private:
    Ui::MainWindow *ui;

    int theScaleRange;
    bool showSinCosComponents;

    Signal *primo;
    QList<OscillatorControl *> Oscillators;
    QList<QColor> colorTable;

};

#endif // MAINWINDOW_H
