#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSaveFile>
#include <QSerialPort>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    QSerialPort *m_serial = nullptr;
    QSaveFile *file = nullptr;
    void openSerialPort();
    void closeSerialPort();
};

#endif // MAINWINDOW_H
