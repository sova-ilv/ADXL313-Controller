#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QTimer>
#include "../qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.


#include <QWidget>
#include <QStatusBar>

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = 0);
    ~ChartWindow();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);

    void stopAcquisition();
    void startAcquisition();


private slots:
  void realtimeDataSlot();

signals:
  void removed(ChartWindow* chart);

private:
    Ui::ChartWindow *ui;
    QString demoName;
    QTimer dataTimer;

};

#endif // CHARTWINDOW_H
