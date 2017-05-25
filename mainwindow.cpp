#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartwindow.h"

#include <QInputDialog>
#include <QString>
#include "QtCore/qstring.h"

#include "qdebug.h"
#include "adxl313.h"
#include "usbserialapp.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->enableButton,  &QPushButton::clicked,
            this, &MainWindow::enable_command);

    connect(ui->readInfoButton, &QPushButton::clicked,
            this, &MainWindow::readInfoReg);

    connect(ui->readRegButton, &QPushButton::clicked,
            this, &MainWindow::readReg);

    connect(ui->writeRegButton, &QPushButton::clicked,
            this, &MainWindow::writeReg);

    usbSerialApp myserial;
    myserial.initSerialUsb();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_command()
{
    qDebug() << "adding chart window.";
    ChartWindow * task = new ChartWindow();

    mTasks.append(task);
    ui->mainchartLayout->addWidget(task);

    connect(ui->stopButton,  &QPushButton::clicked,
            task, &ChartWindow::stopAcquisition);

    connect(ui->startButton,  &QPushButton::clicked,
            task, &ChartWindow::startAcquisition);

    //removed is emitted by ChartWindow, removedChart is defined here (MainWindow)
    connect(task, &ChartWindow::removed, this, &MainWindow::removeChart);

}

void MainWindow::removeChart(ChartWindow *task)
{
   qDebug() << "removing a Chart";
   mTasks.removeOne(task);
   ui->mainchartLayout->removeWidget(task);
   task->setParent(0);
   delete task;
}


void MainWindow::readInfoReg()
{
    ADXL313 accel;

    int iarray[3];
    accel.readInfoRegisters(iarray);

    //qDebug() << "I got - 0" << iarray[0];
    //qDebug() << "I got - 1" << iarray[1];
    //qDebug() << "I got - 2" << iarray[2];

    QString outStr;

    outStr.sprintf("\n0x00 == 0x%02x",iarray[0]);
    ui->infoText->setText(outStr);
    outStr.sprintf("\n0x01 == 0x%02x",iarray[1]);
    ui->infoText->append(outStr);
    outStr.sprintf("\n0x02 == 0x%02x",iarray[2]);
    ui->infoText->append(outStr);

}

void MainWindow::readReg()
{
    ADXL313 adxlr;

    QString str = ui->regAddrText->text();
    int addr = str.toInt();
    int dat = adxlr.readByteAddr(addr);

    QString result;
    result.sprintf("%02x", dat);
    ui->dataIOText->setText(result);
}

void MainWindow::writeReg()
{
    ADXL313 adxlw;

}

