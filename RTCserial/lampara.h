#ifndef LAMPARA_H
#define LAMPARA_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Lampara;
}

class Lampara : public QDialog
{
    Q_OBJECT

public:
    explicit Lampara(QWidget *parent = 0);
    ~Lampara();
    QList<QSerialPortInfo> serialPortInfoList;
    QSerialPort serial;

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_connect_clicked();

private:
    Ui::Lampara *ui;
};

#endif // LAMPARA_H
