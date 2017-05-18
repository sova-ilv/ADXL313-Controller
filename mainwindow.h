#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "chartwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readInfoRegisters();

private:
    Ui::MainWindow *ui;
    QVector<ChartWindow*> mTasks;

private slots:
    void enable_command();
    void removeChart(ChartWindow* task);

};

#endif // MAINWINDOW_H
