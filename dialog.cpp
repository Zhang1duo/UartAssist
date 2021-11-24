#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //To do user's work
    mIsOpen = false;
    ui->BtnSend->setEnabled(mIsOpen);

    //识别串口号
    QList<QSerialPortInfo> serialPortInfo  = QSerialPortInfo::availablePorts();
    int count = serialPortInfo.count();
    for(int i = 0;i < count;i++)
    {
        ui -> CboxSerialPort->addItem(serialPortInfo.at(i).portName());
    }

    connect(&mSerialPort,SIGNAL(readyRead()),this,SLOT(on_SerialPort_readyRead()));
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::getSerialPortConfig()
{
    //获取串口配置
    mPortName = ui->CboxSerialPort->currentText();
    mBaudRate = ui->CBoxBaudRate->currentText();
    mParity = ui->CBoxParity->currentText();
    mDataBits = ui->CboxDataBits->currentText();
    mStopBits = ui->CboxStopBits->currentText();

    //设置串口
    mSerialPort.setPortName(mPortName);

    if("9600" == mBaudRate)
    {
        mSerialPort.setBaudRate(QSerialPort::Baud9600);
    }
    else if("19200" == mBaudRate)
    {
        mSerialPort.setBaudRate(QSerialPort::Baud19200);
    }
    else
    {
        mSerialPort.setBaudRate(QSerialPort::Baud115200);
    }

    if("NONE" == mParity)
    {
        mSerialPort.setParity(QSerialPort::NoParity);
    }
    else if("ODD" == mParity)
    {
        mSerialPort.setParity(QSerialPort::OddParity);
    }
    else
    {
        mSerialPort.setParity(QSerialPort::EvenParity);
    }

    if("5" == mDataBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data5);
    }
    else if("6" == mDataBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data6);
    }
    else if("7" == mDataBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data7);
    }
    else
    {
        mSerialPort.setDataBits(QSerialPort::Data8);
    }

    if("1.5" == mStopBits)
    {
        mSerialPort.setStopBits(QSerialPort::OneAndHalfStop);
    }
    else  if("2" == mStopBits)
    {
        mSerialPort.setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        mSerialPort.setStopBits(QSerialPort::OneStop);
    }

    return mSerialPort.open(QSerialPort::ReadWrite);
}

void Dialog::on_BtnOpen_clicked()
{
    if(true == mIsOpen)
    {
        mSerialPort.close();
        ui->BtnOpen->setText("打开");
        mIsOpen = false;
        ui->BtnSend->setEnabled(mIsOpen);
        ui->CboxSerialPort->setEnabled(true);
        ui->CBoxBaudRate->setEnabled(true);
        ui->CBoxParity->setEnabled(true);
        ui->CboxDataBits->setEnabled(true);
        ui->CboxStopBits->setEnabled(true);
    }
    else
    {
       if(true == getSerialPortConfig())
        {
            mIsOpen = true;
            ui->BtnOpen->setText("关闭");
            qDebug() << "成功打开串口" << mPortName;
            ui->BtnSend->setEnabled(mIsOpen);
            ui->CboxSerialPort->setEnabled(false);
            ui->CBoxBaudRate->setEnabled(false);
            ui->CBoxParity->setEnabled(false);
            ui->CboxDataBits->setEnabled(false);
            ui->CboxStopBits->setEnabled(false);
        }
        else
        {
            mIsOpen = false;
        }
    }
}


void Dialog::on_BtnSend_clicked()
{
    if(true == mIsOpen)
    {
        mSerialPort.write(ui->TeditSend->toPlainText().toStdString().c_str());
    }
}

void Dialog::on_SerialPort_readyRead()
{
    if(true == mIsOpen)
    {
        QByteArray recvData = mSerialPort.readAll();
        ui->TeditRecv->append(QString(recvData));
    }
}

