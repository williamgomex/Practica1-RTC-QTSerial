#ifndef SHOW_H
#define SHOW_H

#define PI (3.141592653589793)
#include <QDialog>
#include <QSerialPort>
#include <QVector>
#include <QTime>
#include <QDate>


//Estuctura del RTC
typedef struct
{
  // Segundos
  unsigned char UNI_SEG :4;
  unsigned char DEC_SEG :3;
  unsigned char CH      :1;
  // Minutos
  unsigned char UNI_MIN :4;
  unsigned char DEC_MIN :3;
  unsigned char         :1;
  // Horas
  union
  {
    struct
    {
      // Horas 24
      unsigned char UNI_HOR :4;
      unsigned char DEC_HOR :2;
      unsigned char _12_24  :1;
      unsigned char         :1;
    }_24;
    struct
    {
      // Horas 12
      unsigned char UNI_HOR :4;
      unsigned char DEC_HOR :1;
      unsigned char AM_PM   :1;
      unsigned char         :2;
    }_12;
  }_HORA;
  // Día de la semana
  unsigned char DIASEM  :3;
  unsigned char         :5;
  // Día del mes
  unsigned char UNI_DIA :4;
  unsigned char DEC_DIA :2;
  unsigned char         :2;
  // Mes
  unsigned char UNI_MES :4;
  unsigned char DEC_MES :1;
  unsigned char         :3;
  // Año
  unsigned char UNI_YEA :4;
  unsigned char DEC_YEA :4;
}_STR_RTC;



namespace Ui {
class Show;
}

class Show : public QDialog
{
    Q_OBJECT
    _STR_RTC  RTCSERIAL;
    QSerialPort serial;
    QVector<double> vectorx;
    QVector<double> signalvector;
    QTime hora;
    QDate dia;
    QTime horajustada;
    QDate diajustada;
    int count,flag;
public:
    explicit Show(QString n,QWidget *parent = 0);
    ~Show();


private slots:
    void readdata();
    void update();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Show *ui;
};






#endif // SHOW_H
