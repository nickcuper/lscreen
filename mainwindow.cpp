#include "mainwindow.h"
#include "ui_mainwindow.h"


// Init widget
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Remove ui
MainWindow::~MainWindow()
{
    delete ui;
}
