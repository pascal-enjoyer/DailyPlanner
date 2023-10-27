#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zametkatime.h"
#include "nezadacha.h"
QString thisdate;
QFile datesread("dates.txt");
QFile zametkiread("zametki.txt");
int sizee = 100;
QString *arr = new QString[sizee];
QString MainWindow::stroka = "";
int MainWindow::kak_otkrito = 0;



bool MainWindow::udalili_zametku = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    on_calendarWidget_clicked(QDate::currentDate());

    tmr = new QTimer(this);
    tmr->setInterval(100);
    connect(tmr, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    tmr->start();

    datesread.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&datesread);
    int i = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        arr[i] = line;
        QStringList parts = line.split(';');
        if (parts.size() == 3) {
            QString datae = parts.at(0);
            QString timee = parts.at(1);
            QString zametka = parts.at(2);
            if (datae == thisdate) {
                ui->delalist->addItem(QString(datae) + " | " + QString(timee) + " | " + QString(zametka));
            }
            i++;
        }
    }
    if (arr[i] != "99.99.9999;99:99;99999" and arr[i+1] == "")
        arr[i] = "99.99.9999;99:99;99999";
    datesread.close();
    datesread.open(QIODevice::WriteOnly | QIODevice::Truncate);
    datesread.resize(0);
    datesread.close();
}
MainWindow::~MainWindow()
{
    datesread.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&datesread);
    int i = 0;
    while (arr[i] != "99.99.9999;99:99;99999") {
        out<<arr[i] << endl;
        i++;
    }
    datesread.close();
    tmr->stop();
    delete ui;
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    thisdate = date.toString(Qt::SystemLocaleShortDate);
    ui->selecteddate_label->setText(thisdate);
    ui->AddpushButton_3->setEnabled(true);
    ui->DeletepushButton_4->setEnabled(true);
}



void MainWindow::UpdateTime() {
    ui->MainWindowTimeLabel->setText(QTime::currentTime().toString(Qt::SystemLocaleShortDate) + "\n" + QDate::currentDate().toString(Qt::SystemLocaleLongDate));
}
void MainWindow::on_AddpushButton_3_clicked()
{
    zametkatime b;
    b.setModal(true);
    b.data = thisdate;
    b.exec();

    if (b.zakril == true) {
        bool gotovo = false;
        QString temparr[100]{};
        datesread.open(QIODevice::ReadOnly | QIODevice::Truncate);
        QTextStream in(&datesread);
        QString line = in.readLine();
        for (int k = 0; arr[k] != ""; k++) {
            if (line == arr[k]) {
                gotovo = true;
            }
        }
        QStringList parts = line.split(";");
        QString timee = parts.at(1);
        QStringList partsoftime = timee.split(":");
        int h = partsoftime.at(0).toInt();
        int m = partsoftime.at(1).toInt();
        int j =0;
        while (gotovo != true) {
            QStringList parts2 = arr[j].split(";");
            QString timee2 = parts2.at(1);
            QStringList partsoftime2 = timee2.split(":");
            int h2 = partsoftime2.at(0).toInt();
            int m2 = partsoftime2.at(1).toInt();
            if (h*60 + m <= h2 * 60 + m2) {
                int i = 0;
                bool flajok = false;
                while (flajok == false) {
                    temparr[i] = arr[i+j];
                    arr[j+i] = "";
                    if (temparr[i] == "99.99.9999;99:99;99999") {
                        flajok = true;
                        arr[j] = line;
                    }
                    i++;
                }
                i = 0;
                while (temparr[i] != "") {
                    arr[j+1] = temparr[i];
                    temparr[i] = "";
                    i++;
                    j++;
                }
                gotovo = true;
            }
            j++;
        }
        int i = 0;
        ui->delalist->clear();
        while (arr[i] != "99.99.9999;99:99;99999") {
            if (ui->calendarWidget->selectedDate().toString(Qt::SystemLocaleShortDate) == arr[i].split(";").at(0)) {
                ui->delalist->addItem(arr[i].split(";").at(0) + " | " + arr[i].split(";").at(1) + " | " + arr[i].split(";").at(2));
            }
            i++;
        }
        datesread.close();
        datesread.resize(0);
    }
}
void MainWindow::on_calendarWidget_selectionChanged()
{
    on_calendarWidget_clicked(ui->calendarWidget->selectedDate());
    ui->delalist->clear();
    bool nashlos = 0;
    QString strochechka = ui->calendarWidget->selectedDate().toString(Qt::SystemLocaleShortDate);
    for(int i = 0; arr[i] != ""; i++) {
        QStringList parts = arr[i].split(";");
        if (parts.size() == 3) {
            QString datae = parts.at(0);
            QString timee = parts.at(1);
            QString zametka = parts.at(2);
            if (datae == strochechka) {
                ui->delalist->addItem(QString(datae) + " | " + QString(timee) + " | " + QString(zametka));
                nashlos += 1;
            }
        }
    }
}
void MainWindow::on_DeletepushButton_4_clicked()
{
    bool loh = false;
    for (int i = 0; arr[i+1] != ""; i++) {
        if (arr[i] == (ui->delalist->currentItem()->text().split(" | ").at(0) + ";" + ui->delalist->currentItem()->text().split(" | ").at(1) + ";" + ui->delalist->currentItem()->text().split(" | ").at(2))) {
            loh = true;
        }
        if (loh == true) {
            if (arr[i+1] != "") {
                arr[i] = arr[i+1];
                arr[i+1] = "";
            }
        }
    }
    int i = 0;
    ui->delalist->clear();
    while (arr[i] != "99.99.9999;99:99;99999") {
        if (ui->calendarWidget->selectedDate().toString(Qt::SystemLocaleShortDate) == arr[i].split(";").at(0)) {
            ui->delalist->addItem(arr[i].split(";").at(0) + " | " + arr[i].split(";").at(1) + " | " + arr[i].split(";").at(2));
        }
        i++;
    }
}
void MainWindow::on_pushButton_clicked()
{
    kak_otkrito = 0;
    nezadacha b;
    b.setModal(true);
    b.exec();
    if (b.zakril == true) {
        ui->zametkilist->addItem(b.vnutritextovika);
    }
    ui->delalist->clear();
}
void MainWindow::on_action_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_action_2_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->zametkilist->clear();
    zametkiread.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&zametkiread);
    while(!in.atEnd()) {
        QString line = in.readLine();
        if (line.split(";").size() == 2)
         ui->zametkilist->addItem(line.split(";").at(0));
    }
    zametkiread.close();
}
void MainWindow::on_action_3_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_zametkilist_itemDoubleClicked(QListWidgetItem *item)
{
    kak_otkrito = 1;
    zametkiread.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&zametkiread);
    while(!in1.atEnd()) {
        QString line = in1.readLine();
        if (line.split(";").size() == 2 and line.split(";").at(0) == ui->zametkilist->currentItem()->text()) {
            stroka = line.split(";").at(1);
        }
    }
    zametkiread.close();
    nezadacha v;
    v.setModal(true);
    v.exec();
    qDebug() << udalili_zametku;
    if (udalili_zametku == true) {
        ui->zametkilist->clear();
        zametkiread.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&zametkiread);
        while(!in.atEnd()) {
            QString line = in.readLine();
            if (line.split(";").size() == 2)
             ui->zametkilist->addItem(line.split(";").at(0));
        }
        zametkiread.close();
    }
}

