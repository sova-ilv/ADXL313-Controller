#include "chartwindow.h"
#include "ui_chartwindow.h"


#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QStatusBar>
#include <QFont>

ChartWindow::ChartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
    //createStatusBar();
    setupRealtimeDataDemo(ui->customPlot);

}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    demoName = "Real Time Data Demo Jess Valdez";

    // include this section to fully disable antialiasing for higher performance:
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */
    setWindowTitle("QCustomPlot: "+demoName);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(customPlot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("ADXL313 - Accelerometer");
    textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text


    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes) ;
      //                                QCP::iSelectLegend | QCP::iSelectPlottables);
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->graph(0)->setName("xG");

    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->graph(1)->setName("yG");

    customPlot->legend->setVisible(true);

    customPlot->xAxis->setLabel("Time");
    QFont labelfont = font(); //QFont serifFont("Times", 10, QFont::Bold);
    labelfont.setPointSize(10);
    customPlot->xAxis->setLabelFont(labelfont);


    customPlot->yAxis->setLabel("G force");
    customPlot->yAxis->setLabelFont(labelfont);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(50); // Interval 0 means to refresh as fast as possible
}


void ChartWindow::stopAcquisition()
{
    dataTimer.stop();
}

void ChartWindow::startAcquisition()
{
    dataTimer.start(50);
}

void ChartWindow::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.005) // at most add point every 2 ms
    {
      // add data to lines:
       ui->customPlot->graph(0)->addData(key, (double)rand()/(double)RAND_MAX);
       ui->customPlot->graph(1)->addData(key, (double)rand()/(double)RAND_MAX);
      //ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      //ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    /*
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;

    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
    */

    //QCPItemText *xtext = new QCPItemText(customPlot);
    //xtext->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    //xtext->position->setType(QCPItemPosition::ptAxisRectRatio);
    //xtext->position->setCoords(0, 10); // place position at center/top of axis rect
    //xtext->setText("x=xxxx");
    //xtext->setFont(QFont(font().family(), 12)); // make font a bit larger
    //xtext->setPen(QPen(Qt::black)); // show black border around text
}
