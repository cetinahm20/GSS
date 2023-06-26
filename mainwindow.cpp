#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUdpSocket>
#include <QUrl>
#include <QMediaContent>
#include <QMediaRecorder>






void MainWindow::playVideo(){



    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/uyvid1.mpg"));
    player->setVolume(10);


    vw->setFixedSize(480,270);
    vw->move(10,1020);
    player->play();



}


void MainWindow::playSound(){



    sound= new QMediaPlayer(this);
    sound->setMedia(QUrl::fromLocalFile("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/buzzer.mp3"));

    sound->play();

}




void MainWindow::readData()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());




        QDataStream stream(datagram);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream >>telemetri.bas1>>telemetri.bas2>>telemetri.yuk1>>telemetri.yuk2>> telemetri.fark>> telemetri.hiz
                >>telemetri.sic>>telemetri.ger>>telemetri.lat>>telemetri.lon>>telemetri.alt>>telemetri.pitch
                >>telemetri.roll>>telemetri.yaw >> telemetri.pakNo >>telemetri.takNo>>telemetri.hataKodu
                >>telemetri.state;



}

}


void MainWindow::writeData(){


        int aK= 1;

    QByteArray datagram = QByteArray::number(aK);
    QHostAddress receiverAddress("192.168.1.104");

    socket2->writeDatagram(datagram,datagram.size(),receiverAddress, 5010);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    playVideo();






    timer = new QTimer(this);
    connect(timer, SIGNAL (timeout()),this,SLOT(timerFunc()));


    QFile File("Veriler.txt");

    File.open(QIODevice::WriteOnly);


          QTextStream stream(&File);
          stream<< "";




          socket = new QUdpSocket(this);

          socket->bind(QHostAddress::Any, 5005);


          socket2 = new QUdpSocket(this);

          socket2->bind(QHostAddress::Any, 5010);


    QPixmap logo("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2023-2024 Model Uydu Yarışması/Organizasyon/TayfLogo.png");
    QPixmap sta1("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/1.png");
    QPixmap durus("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/uydu.png");


        ui->logo->setPixmap(logo.scaled(350,350,Qt::KeepAspectRatio));
        ui->durum->setPixmap(sta1.scaled(300,300,Qt::KeepAspectRatio));
        ui->durusb->setPixmap(durus.scaled(300,300,Qt::KeepAspectRatio));


        QCPScatterStyle myScatter;
        myScatter.setShape(QCPScatterStyle::ssDisc);
        myScatter.setPen(QPen(Qt::black));
        myScatter.setSize(2);

        QFont plotFont= font();
        plotFont.setPointSize(6);



        ui->bas1p->addGraph();

        ui->bas1p->graph(0)->setScatterStyle(myScatter);
        ui->bas1p->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->bas1p->graph(0)->setPen(QPen(QColor(9,45,47)));
        ui->bas1p->setBackground(QColor(197,241,242));

        ui->bas1p->xAxis->setLabel("Paket Numarası");
        ui->bas1p->xAxis->setLabelFont(plotFont);
        ui->bas1p->xAxis->setTickLabelFont(plotFont);
        ui->bas1p->yAxis->setLabel("Basınç(Pa)");
        ui->bas1p->yAxis->setLabelFont(plotFont);
        ui->bas1p->yAxis->setTickLabelFont(plotFont);



        ui->bas2p->addGraph();

        ui->bas2p->graph(0)->setScatterStyle(myScatter);
        ui->bas2p->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->bas2p->graph(0)->setPen(QPen(QColor(9,45,47)));
        ui->bas2p->setBackground(QColor(197,241,242));


        ui->bas2p->xAxis->setLabel("Paket Numarası");
        ui->bas2p->yAxis->setLabel("Basınç(Pa)");
        ui->bas2p->xAxis->setLabelFont(plotFont);
        ui->bas2p->xAxis->setTickLabelFont(plotFont);
        ui->bas2p->yAxis->setLabelFont(plotFont);
        ui->bas2p->yAxis->setTickLabelFont(plotFont);



               ui->yuk1p->addGraph();

               ui->yuk1p->graph(0)->setScatterStyle(myScatter);
               ui->yuk1p->graph(0)->setLineStyle(QCPGraph::lsLine);
               ui->yuk1p->graph(0)->setPen(QPen(QColor(9,45,47)));
               ui->yuk1p->setBackground(QColor(197,241,242));


               ui->yuk1p->xAxis->setLabel("Paket Numarası");
               ui->yuk1p->yAxis->setLabel("Yükseklik(m)");
               ui->yuk1p->xAxis->setLabelFont(plotFont);
               ui->yuk1p->xAxis->setTickLabelFont(plotFont);
               ui->yuk1p->yAxis->setLabelFont(plotFont);
               ui->yuk1p->yAxis->setTickLabelFont(plotFont);



               ui->yuk2p->addGraph();

               ui->yuk2p->graph(0)->setScatterStyle(myScatter);
               ui->yuk2p->graph(0)->setLineStyle(QCPGraph::lsLine);
               ui->yuk2p->graph(0)->setPen(QPen(QColor(9,45,47)));
               ui->yuk2p->setBackground(QColor(197,241,242));


               ui->yuk2p->xAxis->setLabel("Paket Numarası");
               ui->yuk2p->yAxis->setLabel("Yükseklik(m)");
               ui->yuk2p->xAxis->setLabelFont(plotFont);
               ui->yuk2p->xAxis->setTickLabelFont(plotFont);
               ui->yuk2p->yAxis->setLabelFont(plotFont);
               ui->yuk2p->yAxis->setTickLabelFont(plotFont);



                      ui->sicp->addGraph();

                      ui->sicp->graph(0)->setScatterStyle(myScatter);
                      ui->sicp->graph(0)->setLineStyle(QCPGraph::lsLine);
                      ui->sicp->graph(0)->setPen(QPen(QColor(9,45,47)));
                      ui->sicp->setBackground(QColor(197,241,242));


                      ui->sicp->xAxis->setLabel("Paket Numarası");
                      ui->sicp->yAxis->setLabel("Sıcaklık(C°)");
                      ui->sicp->xAxis->setLabelFont(plotFont);
                      ui->sicp->xAxis->setTickLabelFont(plotFont);
                      ui->sicp->yAxis->setLabelFont(plotFont);
                      ui->sicp->yAxis->setTickLabelFont(plotFont);



                      ui->inisp->addGraph();

                      ui->inisp->graph(0)->setScatterStyle(myScatter);
                      ui->inisp->graph(0)->setLineStyle(QCPGraph::lsLine);
                      ui->inisp->graph(0)->setPen(QPen(QColor(9,45,47)));
                      ui->inisp->setBackground(QColor(197,241,242));

                      ui->inisp->xAxis->setLabel("Paket Numarası");
                      ui->inisp->yAxis->setLabel("İniş Hızı(m/s)");
                      ui->inisp->xAxis->setLabelFont(plotFont);
                      ui->inisp->xAxis->setTickLabelFont(plotFont);
                      ui->inisp->yAxis->setLabelFont(plotFont);
                      ui->inisp->yAxis->setTickLabelFont(plotFont);



                             ui->farkp->addGraph();

                             ui->farkp->graph(0)->setScatterStyle(myScatter);
                             ui->farkp->graph(0)->setLineStyle(QCPGraph::lsLine);
                             ui->farkp->graph(0)->setPen(QPen(QColor(9,45,47)));
                             ui->farkp->setBackground(QColor(197,241,242));


                             ui->farkp->xAxis->setLabel("Paket Numarası");
                             ui->farkp->yAxis->setLabel("Fark (m)");
                             ui->farkp->xAxis->setLabelFont(plotFont);
                             ui->farkp->xAxis->setTickLabelFont(plotFont);
                             ui->farkp->yAxis->setLabelFont(plotFont);
                             ui->farkp->yAxis->setTickLabelFont(plotFont);



                             ui->voltp->addGraph();

                             ui->voltp->graph(0)->setScatterStyle(myScatter);
                             ui->voltp->graph(0)->setLineStyle(QCPGraph::lsLine);
                             ui->voltp->graph(0)->setPen(QPen(QColor(9,45,47)));
                             ui->voltp->setBackground(QColor(197,241,242));


                             ui->voltp->xAxis->setLabel("Paket Numarası");
                             ui->voltp->yAxis->setLabel("Gerilim (Volt)");
                             ui->voltp->xAxis->setLabelFont(plotFont);
                             ui->voltp->xAxis->setTickLabelFont(plotFont);
                             ui->voltp->yAxis->setLabelFont(plotFont);
                             ui->voltp->yAxis->setTickLabelFont(plotFont);












}

MainWindow::~MainWindow()
{
    delete ui;


}


void MainWindow::on_basla_toggled(bool checked)
{

    if(checked==true){

  ui->basla->setText("Durdur");


   timer->start(1000);


    }

 else{

        ui->basla->setText("Başlat");
        timer->stop();


    }
}




void MainWindow::on_pushButton_2_toggled(bool checked)
{

    QString filename = QFileDialog::getOpenFileName(this,"Bir Dosya Seçin","","Video Dosyası (*.mpg)");


    player->setMedia(QUrl::fromLocalFile(filename));
    player->play();
}




void MainWindow::on_vidb_toggled(bool checked)
{




    ui->vidd->setText("Video Gönderildi!");
}



void MainWindow::on_ayril_toggled(bool checked)
{


    writeData();

}




void MainWindow::timerFunc(){


        readData();


        telemetri.zaman= QDateTime::currentSecsSinceEpoch();



        int  x=telemetri.pakNo;
        double  y1=telemetri.bas1;
        double  y2=telemetri.bas2;
        double  y3=telemetri.yuk1;
        double  y4=telemetri.yuk2;
        double  y5=telemetri.sic;
        double  y6=telemetri.hiz;
        double  y7=telemetri.fark;
        double  y8=telemetri.ger;


        ui->bas1p->addGraph();
        ui->bas1p->graph(0)->addData(x, y1);



              ui->bas1p->rescaleAxes();
              ui->bas1p->replot();
              ui->bas1p->update();


              ui->bas2p->addGraph();
              ui->bas2p->graph(0)->addData(x, y2);



                      ui->bas2p->rescaleAxes();
                      ui->bas2p->replot();
                      ui->bas2p->update();


                      ui->yuk1p->addGraph();
                      ui->yuk1p->graph(0)->addData(x, y3);



                              ui->yuk1p->rescaleAxes();
                              ui->yuk1p->replot();
                              ui->yuk1p->update();


                              ui->yuk2p->addGraph();
                              ui->yuk2p->graph(0)->addData(x, y4);



                                      ui->yuk2p->rescaleAxes();
                                      ui->yuk2p->replot();
                                      ui->yuk2p->update();


                                      ui->sicp->addGraph();
                                      ui->sicp->graph(0)->addData(x, y5);



                                              ui->sicp->rescaleAxes();
                                              ui->sicp->replot();
                                              ui->sicp->update();


                                              ui->inisp->addGraph();
                                              ui->inisp->graph(0)->addData(x, y6);



                                                      ui->inisp->rescaleAxes();
                                                      ui->inisp->replot();
                                                      ui->inisp->update();


                                                      ui->farkp->addGraph();
                                                      ui->farkp->graph(0)->addData(x, y7);



                                                              ui->farkp->rescaleAxes();
                                                              ui->farkp->replot();
                                                              ui->farkp->update();


                                                              ui->voltp->addGraph();
                                                              ui->voltp->graph(0)->addData(x, y8);



                                                                      ui->voltp->rescaleAxes();
                                                                      ui->voltp->replot();
                                                                      ui->voltp->update();



        QString data= QString::number(telemetri.pakNo)+ ", " + QString::number(telemetri.state) + ", "
              + QString::number(telemetri.hataKodu) + ", " + QString::number(telemetri.zaman) + ", " +
              QString::number(telemetri.bas1) + ", "  + QString::number(telemetri.bas2) + ", " + QString::number(telemetri.yuk1) +
              ", " + QString::number(telemetri.yuk2) + ", " + QString::number(telemetri.fark) + ", " +
              QString::number(telemetri.hiz)+ ", " +QString::number(telemetri.sic) + ", " + QString::number(telemetri.ger) +
              ", " + QString::number(telemetri.lat) + ", " + QString::number(telemetri.lon) + ", " +
              QString::number(telemetri.alt) + ", " +QString::number(telemetri.pitch)+"," + QString::number(telemetri.roll)+
              ", " + QString::number(telemetri.yaw) + ", " + QString::number(telemetri.takNo);



        ui->telemetry->addItem(data);



    QPixmap sta1("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/1.png");
    QPixmap sta2("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/2.png");
    QPixmap sta3("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/3.png");

if(telemetri.state == 1){

    ui->durum->setPixmap(sta1.scaled(300,300,Qt::KeepAspectRatio));

}

if(telemetri.state == 2) {

   ui->durum->setPixmap(sta2.scaled(300,300,Qt::KeepAspectRatio));

}
if(telemetri.state == 3) {

   ui->durum->setPixmap(sta3.scaled(300,300,Qt::KeepAspectRatio));

}

if(telemetri.hataKodu!=1){


    playSound();


}




ui->irtifa->setText("İRTİFA FARKI: " + QString::number(telemetri.fark));





QFile File("Veriler.csv");

File.open(QIODevice::Append |QIODevice::WriteOnly);


      QTextStream stream(&File);
      stream<< data +"\n";



File.close();



}



