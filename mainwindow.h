#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTextStream>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUdpSocket>
#include <QMediaRecorder>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#pragma pack(push,1)
typedef struct tTelemetri{

    int pakNo ;
    unsigned char state = 3;
    unsigned char hataKodu = 0 <<0 | 0<< 1 | 0 << 2| 0 << 3| 0 << 4;
    long long zaman;
    double bas1 ;
    double bas2 ;
    double yuk1 ;
    double yuk2 ;
    double fark ;
    double hiz ;
    double sic ;
    double ger ;
    double lon ;
    double lat ;
    double alt ;
    double pitch ;
    double roll ;
    double yaw ;
    int takNo ;


}Telemetri;
#pragma pack(pop)



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Telemetri telemetri;


private slots:
    void timerFunc();

    void on_basla_toggled(bool checked);

    void on_pushButton_2_toggled(bool checked);

    void on_ayril_toggled(bool checked);

    void on_vidb_toggled(bool checked);

    void readData();

    void writeData();

    void playVideo();

    void playSound();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QMediaPlayer* sound;
    QMediaRecorder* recorder;
    QUdpSocket *socket;
    QUdpSocket *socket2;


};
#endif // MAINWINDOW_H
