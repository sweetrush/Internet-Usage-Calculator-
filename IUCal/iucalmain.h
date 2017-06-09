#ifndef IUCALMAIN_H
#define IUCALMAIN_H

#include <QMainWindow>

namespace Ui {
class IUCalMain;
}

class IUCalMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit IUCalMain(QWidget *parent = 0);
    ~IUCalMain();

    //SelfDefind Fucations
    double BandWidth;     //Value of the BandWidth
    double SecPerHour;    //Number of Seconds Per Hour
    double SecPerDay;     //Number of Seconds Per Day

    double SP1;        //Sample 1 Data in Gigbytes
    double SP2;        //Sample 2 Data in Gigbytes
    double SP3;        //Sample 3 Data in Gigbytes
    double CSP;        //Custom Data in Gigbytes

    double Sp1BandWidth;   //Store Bandwidth Value Sample 1
    double Sp2BandWidth;   //Store Bandwidth Value Sample 2
    double Sp3BandWidth;   //Store BandWidth Value Sample 3

    //Accumulation fuctions Calculation

    //Calculates the Amount of Daya for a paticular Day
    double cAcculateInDays(int Days){
        return((BandWidth * SecPerDay * Days)/(1000000000));
    }

    //Calculates the Amount fo Data for a paticular Week
    double cAcculateInWeeks(double DayFiveTotal,  int WeekIndex){
        return(WeekIndex * DayFiveTotal);
    }

    //Actual Accumulation funcations

    double acAcculateInDays(double SP_DataValue, int Days){
        return(SP_DataValue * Days);
    }

    double acAcculateInWeeks(double DayFiveTotal, int WeekIndex){
        return(DayFiveTotal * WeekIndex);
    }

    double CalSampleBandWidth(double getSampleDayOne, double SecondsPerDay){
        return((getSampleDayOne * 1000)/SecondsPerDay);

    }



private slots:
    void on_pushButton_clicked();

    void on_inBandwidth_textChanged(const QString &arg1);

    void on_LoadDefaults_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::IUCalMain *ui;
};

#endif // IUCALMAIN_H
