#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>


/*
 * Некоторый функционал так и остался не реализован.
 * Наблюдаются проблемы с производительностью (форма зависает при перерисовке графика и\или при масштабировании)
 * Возможные пути решения:
 *  1)Изменение способа хранения координат(хранить массив, а не пересоздавать его для каждой новой операции)
 *  2)Добавление логики при взаимодействии пользователя с элементами масштабирования
 *      2.1)Перерисовка формы после того, как пользователь отпустит слайдер, а не при изменении значения.
 *      2.2)Создание таймаута для перерисовки.
 *  3)Вынос расчетов для перерисовки в отдельный поток. Начинать перерисовку на форме по сигналу о конце расчета.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnect()));


    //Параметры отрисовки графика
    this->ui->widget->xAxis->setLabel("t");
    this->ui->widget->yAxis->setLabel("value");
    this->ui->widget->xAxis->setRange(0,10);
    this->ui->widget->yAxis->setRange(0,10);
    this->ui->widget->replot();

    //Подключение к серверу
    socket->connectToHost("127.0.0.1",80);

}

MainWindow::~MainWindow()
{
    this->ui->widget->clearGraphs();
    values.clear();
    delete socket;
    delete ui;
}

void MainWindow::socketDisconnect()
{
    socket->deleteLater();
}

void MainWindow::socketReady()
{
        //Ожидаем считывания данных 0,5 секунд
        socket->waitForReadyRead(500);
        //инициализируем Data полученными с сервера данными
        Data = socket->readAll();
        //записываем value в вектор значений
        values.push_back(Data.toInt());
        this->ui->lcdNumber->display(values.last());
        //очищаем график
        this->ui->widget->clearGraphs();
        //создаем новый график
        this->ui->widget->addGraph();
        //инициализируем вспомогательный вектор х для передачи данных в формате value(x,y) в функцию setData
        QVector<double> x(values.size());

        for(int i=0;i<x.size();i++){
            x[i]=i;
        }

        this->ui->widget->graph(0)->setData(x,values);
        //перерисовываем график
        this->ui->widget->replot();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    this->ui->widget->yAxis->setRange(0,value);
    this->ui->widget->replot();
}
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->ui->widget->xAxis->setRange(0,value);
    this->ui->widget->replot();
}

void MainWindow::on_pushButton_clicked()
{
    values.clear();
    this->ui->widget->clearGraphs();
    this->ui->widget->replot();
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0://Синий
        break;
    case 1://Красный
        break;
    case 2://Зеленый
        break;
    case 3://Черный
        break;
    }
}


