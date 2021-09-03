#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawGraph(bool notEmpty = 0);
    void recountPixels();
    void resetData();

    QTcpSocket *socket;
    QByteArray Data;

    //Параметры отрисовки
    QVector<double> values;
    double step;//Шаг
    double width;//Ширина
    double heigth;//Высота


public slots:
    //Готовность к чтению данных
    void socketReady();
    //Отключение от сокета
    void socketDisconnect();

private slots:
    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
