#include "iucalmain.h"
#include "ui_iucalmain.h"
#include <QString>
#include <QList>
#include <QDebug>


//Defind Store Variables
QList<QString> DayStoreForAcc;
QList<QString> WeeksStoreForAcc;

//Defind Store Variables for Samples
//For Days
QList<QString> SampleOneUsageForDays;
QList<QString> SampleTwoUsageForDays;
QList<QString> SampleThreeUsageForDays;

//For Weeks
QList<QString> SampleOneUsageForWeeks;
QList<QString> SampleTwoUsageForWeeks;
QList<QString> SampleThreeUsageForWeeks;

//For Sample Bandwidth
QList<QString> BandwidthSamplesResult;

//Defind Utility Variables
int Start = 5;
int i,SimCountAC1;

int Kone = 1000000;


IUCalMain::IUCalMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IUCalMain)
{
    ui->setupUi(this);
}

IUCalMain::~IUCalMain()
{
    delete ui;
}

//Simulate Button_Left
void IUCalMain::on_pushButton_clicked()
{

    IUCalMain::SecPerDay = ui->inSecPerDay->text().toDouble();
    IUCalMain::SecPerHour = ui->inSecPerHr->text().toDouble();
    int inc;
    SimCountAC1 = SimCountAC1 + 1;

    //Refresh for New simulation
    DayStoreForAcc.clear();
    WeeksStoreForAcc.clear();

    //Calculate and Store Days Information

    qDebug() << "------Days--------";
    ui->AC_OutputDays->append("######[ Simulation-"+QString::number
                              (SimCountAC1)
                              +" ]#############"
                              );

    for(i = 0; i<Start; i++){
       inc = i+1;

       //Storing Values to List
        DayStoreForAcc << QString::number(IUCalMain::cAcculateInDays(inc));

        //Output Results to Terminal and UI_Text-Area
       qDebug() <<"[ " << inc << " ]"<< DayStoreForAcc[i] << "GiB";

       ui->AC_OutputDays->append(" [ "+QString::number
                                 (inc)+" ] <b>"
                                 +DayStoreForAcc[i]
                                 +"</b> GiB"
                                 );

    }

    qDebug() << "---------Weeks---------";
    ui->AC_OutputWeeks->append("#####[ Simulation-"+QString::number
                              (SimCountAC1)+" ]#############"
                               );

    for(i=0;i<Start;i++){
        inc = i+1;

        WeeksStoreForAcc << QString::number
                            (IUCalMain::cAcculateInWeeks
                            (DayStoreForAcc[4].toDouble(),inc)
                            );

        qDebug() <<"[ " << inc << " ]"<< DayStoreForAcc[i] << "GiB";

        ui->AC_OutputWeeks->append("["
                                   +QString::number(inc)
                                   +"]<b>"+WeeksStoreForAcc[i]
                                   +"</b> GiB"
                                   );
    }


}

//Loads when the Input Bandwidth Changes
void IUCalMain::on_inBandwidth_textChanged(const QString &arg1)
{
    IUCalMain::BandWidth = arg1.toDouble();
    qDebug() << "Bandwidth Change to :  " << IUCalMain::BandWidth ;
}

//Loading Defaults for Simulator
void IUCalMain::on_LoadDefaults_clicked()
{
    if(ui->inBandwidth->text() == ""){
        IUCalMain::BandWidth = 1000000;   //1 MegaByte
    }else{
       IUCalMain::BandWidth = 1000000;   //1 MegaByte
    }

     if(ui->inSecPerHr->text() == ""){
         IUCalMain::SecPerHour = 3600;     // Seconds
     }

     if(ui->inSecPerDay->text() == ""){
         IUCalMain::SecPerDay = 28800;     //Seconds
     }

     ui->inSecPerDay->setText(QString::number
                              (IUCalMain::SecPerDay )
                              );

     ui->inSecPerHr->setText(QString::number
                            (IUCalMain::SecPerHour)
                             );

     ui->inBandwidth->setText(QString::number
                             (IUCalMain::BandWidth)
                             );
}

//Simulation Button_Right
void IUCalMain::on_pushButton_2_clicked()
{
    IUCalMain::SP1 = ui->inSP1->text().toDouble();
    IUCalMain::SP2 = ui->inSP2->text().toDouble();
    IUCalMain::SP3 = ui->inSP3->text().toDouble();

    int inb;
    SimCountAC1 = SimCountAC1 + 1;

    //Apply Refresh the List
    //For Days
    SampleOneUsageForDays.clear();
    SampleTwoUsageForDays.clear();
    SampleThreeUsageForDays.clear();

    //For Weeks
    SampleOneUsageForWeeks.clear();
    SampleTwoUsageForWeeks.clear();
    SampleThreeUsageForWeeks.clear();

    //Calculate Days and Store them
    qDebug() << "/////////| Data Samples Days |/////////" ;
    ui->SampleDayOutput->append("\t\t####"+QString::number(SimCountAC1)+"####");
    ui->SampleDayOutput->append("Day\tSample 1\tSample 2\tSample 3");
    for(i=0;i<Start;i++){
        inb = i+1;
        SampleOneUsageForDays << QString::number
                                 (IUCalMain::acAcculateInDays
                                 (IUCalMain::SP1,inb)
                                 );

        SampleTwoUsageForDays << QString::number
                                 (IUCalMain::acAcculateInDays
                                 (IUCalMain::SP2,inb)
                                 );

        SampleThreeUsageForDays << QString::number
                                   (IUCalMain::acAcculateInDays
                                   (IUCalMain::SP3,inb)
                                   );

        qDebug() << "[ " << inb << " ] "
                 << SampleOneUsageForDays[i] << "\t| "
                 << SampleTwoUsageForDays[i] << "\t| "
                 << SampleThreeUsageForDays[i] << "\t| "
                 ;

        ui->SampleDayOutput->append("[ "+QString::number(inb)+" ]\t"
                                    +SampleOneUsageForDays[i]+"\t"
                                    +SampleTwoUsageForDays[i]+"\t"
                                    +SampleThreeUsageForDays[i]
                                    );
    }

    //Calulate Weeks and Store Them
    qDebug() << "///////| Data Samples Weeks |/////////" ;
    ui->SampleWeekOutput->append("\t\t####"+QString::number(SimCountAC1)+"####");
    ui->SampleWeekOutput->append("Week\tSample 1\tSample 2\tSample 3");
    for(i =0;i<Start;i++){
        inb = i+1;
        SampleOneUsageForWeeks << QString::number
                                  (IUCalMain::acAcculateInWeeks
                                  (SampleOneUsageForDays[4].toDouble(),inb)
                                  );

        SampleTwoUsageForWeeks << QString::number
                                  (IUCalMain::acAcculateInWeeks
                                  (SampleTwoUsageForDays[4].toDouble(),inb)
                                  );

        SampleThreeUsageForWeeks << QString::number
                                    (IUCalMain::acAcculateInWeeks
                                    (SampleThreeUsageForDays[4].toDouble(),inb)
                                    );

        qDebug() << "[ " << inb << " ] "
                 << SampleOneUsageForWeeks[i] << "\t| "
                 << SampleTwoUsageForWeeks[i] << "\t| "
                 << SampleThreeUsageForWeeks[i] << "\t| "
                 ;

        ui->SampleWeekOutput->append("[ "+QString::number(inb)+" ]\t"
                                    +SampleOneUsageForWeeks[i]+"\t"
                                    +SampleTwoUsageForWeeks[i]+"\t"
                                    +SampleThreeUsageForWeeks[i]
                                    );

    }

    IUCalMain::on_LoadDefaults_clicked();


    //Calculating and Storing Bandwidth
    IUCalMain::Sp1BandWidth = IUCalMain::CalSampleBandWidth
                             (
                                SampleOneUsageForDays[0].toDouble(),
                                ui->inSecPerDay->text().toDouble()
                              );

    IUCalMain::Sp2BandWidth = IUCalMain::CalSampleBandWidth
                              (
                                  SampleTwoUsageForDays[0].toDouble(),
                                  ui->inSecPerDay->text().toDouble()
                              );

    IUCalMain::Sp3BandWidth = IUCalMain::CalSampleBandWidth
                              (
                                 SampleThreeUsageForDays[0].toDouble(),
                                 ui->inSecPerDay->text().toDouble()
                              );

    qDebug() << IUCalMain::Sp1BandWidth << IUCalMain::Sp2BandWidth << IUCalMain::Sp3BandWidth ;

    //Loading Bandwidth Results to UI
    ui->Sp1BWout->setText(QString::number(Sp1BandWidth));
    ui->Sp2BWout->setText(QString::number(Sp2BandWidth));
    ui->Sp3BWout->setText(QString::number(Sp3BandWidth));

    //Extending Simulation to Accumilation Bandwidth Similation Part
    if(ui->Sp1Toggle->isChecked()){
        ui->inBandwidth->setText(QString::number(Sp1BandWidth*Kone));
        ui->AC_OutputDays->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        ui->AC_OutputWeeks->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        on_pushButton_clicked();
    }

    if(ui->Sp2Toggle->isChecked()){
        ui->inBandwidth->setText(QString::number(Sp2BandWidth*Kone));
        ui->AC_OutputDays->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        ui->AC_OutputWeeks->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        on_pushButton_clicked();
    }

    if(ui->Sp3Toggle->isChecked()){
        ui->inBandwidth->setText(QString::number(Sp3BandWidth*Kone));
        ui->AC_OutputDays->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        ui->AC_OutputWeeks->append("////////SP-BW |"+ui->inBandwidth->text()+"|////////");
        on_pushButton_clicked();
    }


}
