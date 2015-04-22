#include "lampara.h"
#include "ui_lampara.h"
#include <QMessageBox>
#include "show.h"

Lampara::Lampara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lampara)
{
    ui->setupUi(this);
    serialPortInfoList = QSerialPortInfo::availablePorts();

    for(int i=0;i<serialPortInfoList.count();i++){
        QSerialPortInfo* PortInfo = new QSerialPortInfo(serialPortInfoList[i]); //  Se pasa la información
         ui->comboBox->addItem(PortInfo->portName()); //Se agregan todos los puertos al menu
    }

    for(int i=0;i<serialPortInfoList.count();i++){
        QSerialPortInfo* PortInfo = new QSerialPortInfo(serialPortInfoList[i]);
         if(   PortInfo->portName()   ==   ui->comboBox->itemText(ui->comboBox->currentIndex())   ){
             ui->spuerto->setText(PortInfo->portName());
             ui->sbusy->setText((PortInfo->isBusy() ? QObject::tr("Yes") : QObject::tr("No")));
         }
    }
}

Lampara::~Lampara()
{
    delete ui;
}

void Lampara::on_comboBox_activated(const QString &arg1)
{
    for(int i=0;i<serialPortInfoList.count();i++){
        QSerialPortInfo* PortInfo = new QSerialPortInfo(serialPortInfoList[i]);
         if(   PortInfo->portName()   ==   ui->comboBox->itemText(ui->comboBox->currentIndex())   ){
             ui->spuerto->setText(PortInfo->portName());
             ui->sbusy->setText((PortInfo->isBusy() ? QObject::tr("Yes") : QObject::tr("No")));
         }
    }
}

void Lampara::on_connect_clicked()
{
    if( ui->sbusy->text() == "No" ){
            QString port;
            serial.setPortName( port = ui->comboBox->itemText(ui->comboBox->currentIndex()) );
            Show a(port);
            a.exec();
    }
    else{
        QMessageBox::critical(this, tr("Error"), "No es posible la conexión debido a que otro programa lo está usando");
    }
}
