#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui -> pushButton_0, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_1, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_2, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_3, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_4, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_5, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_6, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_7, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_8, SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui -> pushButton_9, SIGNAL(released()), this,SLOT(digit_pressed()));

    connect(ui -> pushButton_MinusPlus, SIGNAL(released()), this,SLOT(unary_operation_pressed()));
    connect(ui -> pushButton_Percent, SIGNAL(released()), this,SLOT(unary_operation_pressed()));

    connect(ui -> pushButton_Plus, SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_Less, SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_Times, SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui -> pushButton_Division, SIGNAL(released()), this,SLOT(binary_operation_pressed()));

    ui -> pushButton_Plus -> setCheckable(true);
    ui -> pushButton_Less -> setCheckable(true);
    ui -> pushButton_Times -> setCheckable(true);
    ui -> pushButton_Division -> setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if ((ui -> pushButton_Plus -> isChecked() || ui -> pushButton_Times -> isChecked() || ui -> pushButton_Less -> isChecked() || ui -> pushButton_Division -> isChecked()) && (!userIsTypingSecondNumber)) {
        labelNumber =  button -> text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber, 'g',15);
    }
    else {
        if(ui -> label -> text().contains('.') && button -> text() == "0") {
            newLabel = ui -> label -> text() + button -> text();
        }
        else {
            labelNumber = (ui -> label -> text() + button -> text()).toDouble();
            newLabel = QString::number(labelNumber, 'g',15);
        }
    }

    ui -> label -> setText(newLabel);
}

void MainWindow::on_pushButton_Dot_released()
{
    ui -> label -> setText(ui -> label -> text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    if (button -> text() == "+/-") {
       labelNumber = ui -> label -> text().toDouble();
       labelNumber = labelNumber * -1;
       newLabel = QString::number(labelNumber, 'g', 15);
       ui -> label -> setText(newLabel);
    }

    if (button -> text() == "%") {
       labelNumber = ui -> label -> text().toDouble();
       labelNumber = labelNumber * 0.01;
       newLabel = QString::number(labelNumber, 'g', 15);
       ui -> label -> setText(newLabel);
    }
}

void MainWindow::on_pushButton_Clear_released()
{
    ui -> pushButton_Plus -> setChecked(false);
    ui -> pushButton_Less -> setChecked(false);
    ui -> pushButton_Division -> setChecked(false);
    ui -> pushButton_Times -> setChecked(false);

    userIsTypingSecondNumber = false;

    ui -> label -> setText("0");
}


void MainWindow::on_pushButton_Equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui -> label->text().toDouble();

    if (ui -> pushButton_Plus -> isChecked()) {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label -> setText(newLabel);
        ui -> pushButton_Plus -> setChecked(false);
    }
    else if (ui -> pushButton_Less -> isChecked()) {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label -> setText(newLabel);
        ui -> pushButton_Less -> setChecked(false);
    }
    else if (ui -> pushButton_Times -> isChecked()) {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label -> setText(newLabel);
        ui -> pushButton_Times -> setChecked(false);
    }
    else if (ui -> pushButton_Division -> isChecked()) {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui -> label -> setText(newLabel);
        ui -> pushButton_Division -> setChecked(false);
    }
    userIsTypingSecondNumber = false;
}


void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui -> label -> text().toDouble();


    button -> setChecked(true);

}
