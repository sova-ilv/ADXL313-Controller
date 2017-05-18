#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartwindow.h"

#include <QInputDialog>

#include "qdebug.h"
#include "adxl313.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ChartWindow receiver;

    connect(ui->enableButton,  &QPushButton::clicked,
            this, &MainWindow::enable_command);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::enable_command()
{

    qDebug() << "adding chart window.";

    ChartWindow * task = new ChartWindow();
    //connect(task, &ChartWindow::removed, this, &MainWindow::removeTask);

    mTasks.append(task);
    ui->mainchartLayout->addWidget(task);

    connect(ui->stopButton,  &QPushButton::clicked,
            task, &ChartWindow::stopAcquisition);

    connect(ui->startButton,  &QPushButton::clicked,
            task, &ChartWindow::startAcquisition);

    connect(task, &ChartWindow::removed, this, &MainWindow::removeChart);
    //connect(ui->removeButton, &QPushButton::clicked,
          //  task, &MainWindow::removeChart);
}

void MainWindow::removeChart(ChartWindow *task)
{
   qDebug() << "removing a Chart";
   mTasks.removeOne(task);
   ui->mainchartLayout->removeWidget(task);
   task->setParent(0);
   delete task;
}

