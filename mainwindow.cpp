#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this)),
    file(new QSaveFile(this))
{   
    // Set the UI to the main program
    ui->setupUi(this);

    // Set serial port status as disconnected when program starts
    ui->connectionStatus->setText("Disconnected");

    // Set all data in cero (call method here in case needed)

    // Set the serial port configurations
    m_serial->setPortName("COM9");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    // To write into serial port unncomment this statement and the slot declaration in header file
    //connect(m_console, &Console::getData, this, &MainWindow::writeData);

    // File settings
    file->setFileName("C:/Users/Axel/Documents/InstrumentacionVirtual/transmitedFile.bin");
    file->open(QIODevice::WriteOnly);
}

MainWindow::~MainWindow()
{
    closeSerialPort();
    delete ui;
}

void MainWindow::openSerialPort()
{
    if (m_serial->open(QIODevice::ReadWrite)) {
        ui->connectionStatus->setText("Connected");
        ui->connectButton->setText("Disconnect");
    } else {
        ui->connectionStatus->setText("Couldn't connect");
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen()) {
        m_serial->close();

        if (!m_serial->isOpen())
            ui->connectionStatus->setText("Disconnected");
    }

    file->commit();
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    writeFile(data);
    updateUI(data);
}

void MainWindow::writeFile(const QByteArray data)
{
  file->write(data);
}

void MainWindow::updateUI(const QByteArray data)
{

}

void MainWindow::on_connectButton_clicked()
{
    if(ui->connectButton->text() == "Connect") {
        openSerialPort();

    } else if (ui->connectButton->text() == "Disconnect") {
        closeSerialPort();
    }
}

