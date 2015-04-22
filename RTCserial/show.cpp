#include "show.h"
#include "ui_show.h"
#include <QThread>
#include <QScrollBar>
#include <QTime>
#include <QDate>
#include <QMessageBox>
#include <math.h>
#include <QDebug>
#include <QTimer>

Show::Show(QString n,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show)
{
    ui->setupUi(this);

    serial.setPortName(n);
    if (serial.open(QIODevice::ReadWrite)) {
            if (serial.setBaudRate(QSerialPort::Baud9600)
                    && serial.setDataBits(QSerialPort::Data8)
                    && serial.setParity(QSerialPort::NoParity)
                    && serial.setStopBits(QSerialPort::OneStop)
                    && serial.setFlowControl(QSerialPort::NoFlowControl)) {
            }

    }

    QObject::connect(&serial, SIGNAL(readyRead()), this,SLOT(readdata()));


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    count=-1;

}

Show::~Show()
{
    delete ui;
}




void Show::readdata(){

    char buffr[1];
    serial.read(buffr,1);


    count++;  
    uchar bite;
            if(count==0)
            {
                bite = ((RTCSERIAL.CH<<8)|(RTCSERIAL.DEC_SEG<<4)|RTCSERIAL.UNI_SEG);
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==1)
            {
                bite = (0|(RTCSERIAL.DEC_MIN<<4)|RTCSERIAL.UNI_MIN);
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==2)
            {
                bite = (RTCSERIAL._HORA._24._12_24<<5)|(RTCSERIAL._HORA._24.DEC_HOR<<4)|(RTCSERIAL._HORA._24.UNI_HOR);
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==3)
            {
                bite = (RTCSERIAL.DIASEM);
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==4)
            {
                bite = (RTCSERIAL.DEC_DIA<<4)|RTCSERIAL.UNI_DIA;
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==5)
            {
                bite = (RTCSERIAL.DEC_MES<<4)|RTCSERIAL.UNI_MES;
                char buffl[1]={bite};
                serial.write(buffl,1);
            }
            if(count==6)
            {
                bite = (RTCSERIAL.DEC_YEA<<4)|RTCSERIAL.UNI_YEA;
                char buffl[1]={bite};
                serial.write(buffl,1);
                count=-2;

            }

}

void Show::update(){
    hora=hora.currentTime();
    ui->labelhora->setText("Hora: "+ hora.toString("h:m:s ap"));
    ui->labelfecha->setText("Fecha: "+dia.currentDate().toString("dd MMMM yyyy"));
}

void Show::on_pushButton_clicked()
{
    RTCSERIAL.CH = 0; //Habilita el oscilador
            //Segundos
    RTCSERIAL.UNI_SEG = hora.second()%10; //Unidades de los segundos en BCD de 0-9
    RTCSERIAL.DEC_SEG = hora.second()/10; //Decenas de los segundos en BCD de 0-9
            //Minutos
    RTCSERIAL.UNI_MIN = hora.minute()%10; //
    RTCSERIAL.DEC_MIN = hora.minute()/10; //
            //Horas
    RTCSERIAL._HORA._24._12_24 = 0; //Bit que indica el formato
    RTCSERIAL._HORA._24.UNI_HOR = hora.hour()%10; //Unidades de las horas
    RTCSERIAL._HORA._24.DEC_HOR = hora.hour()/10; //Decenas de las horas, son 1 ó 2, que se controla con la unión
            //Días de la semana, de 0 a 7
    RTCSERIAL.DIASEM = dia.currentDate().dayOfWeek();
            //Fecha
                //Día
    RTCSERIAL.UNI_DIA = dia.currentDate().day()%10;//Unidades del día del mes 0-9
    RTCSERIAL.DEC_DIA = dia.currentDate().day()/10;//Decenas del día del mes 0-3
                //Mes
    RTCSERIAL.UNI_MES = dia.currentDate().month()%10;
    RTCSERIAL.DEC_MES = dia.currentDate().month()/10;
                //Año
    RTCSERIAL.UNI_YEA = (dia.currentDate().year()%100)%10;
    RTCSERIAL.DEC_YEA = (dia.currentDate().year()%100)/10;

    char buffl[1]={'A'};
    serial.write(buffl,1);


}

void Show::on_pushButton_2_clicked()
{
    diajustada=ui->calendarWidget->selectedDate();
    horajustada=ui->timeEdit->time();
    RTCSERIAL.CH = 0; //Habilita el oscilador
            //Segundos
    RTCSERIAL.UNI_SEG = horajustada.second()%10; //Unidades de los segundos en BCD de 0-9
    RTCSERIAL.DEC_SEG = horajustada.second()/10; //Decenas de los segundos en BCD de 0-9
            //Minutos
    RTCSERIAL.UNI_MIN = horajustada.minute()%10; //
    RTCSERIAL.DEC_MIN = horajustada.minute()/10; //
            //Horas
    RTCSERIAL._HORA._24._12_24 = 0; //Bit que indica el formato
    RTCSERIAL._HORA._24.UNI_HOR = horajustada.hour()%10; //Unidades de las horas
    RTCSERIAL._HORA._24.DEC_HOR = horajustada.hour()/10; //Decenas de las horas, son 1 ó 2, que se controla con la unión
            //Días de la semana, de 0 a 7
    RTCSERIAL.DIASEM = diajustada.dayOfWeek();
            //Fecha
                //Día
    RTCSERIAL.UNI_DIA = diajustada.day()%10;//Unidades del día del mes 0-9
    RTCSERIAL.DEC_DIA = diajustada.day()/10;//Decenas del día del mes 0-3
                //Mes
    RTCSERIAL.UNI_MES = diajustada.month()%10;
    RTCSERIAL.DEC_MES = diajustada.month()/10;
                //Año

    RTCSERIAL.UNI_YEA = (diajustada.year()%100)%10;
    RTCSERIAL.DEC_YEA = (diajustada.year()%100)/10;

    char buffl[1]={'A'};
    serial.write(buffl,1);
}
