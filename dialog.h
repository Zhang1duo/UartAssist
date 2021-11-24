#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public:
    bool getSerialPortConfig(void);

private slots:
    void on_BtnOpen_clicked();

    void on_BtnSend_clicked();

    void on_SerialPort_readyRead();

private:
    Ui::Dialog *ui;
    QSerialPort mSerialPort;
    bool mIsOpen;
    QString mPortName;
    QString mBaudRate;
    QString mParity;
    QString mDataBits;
    QString mStopBits;
};
#endif // DIALOG_H
