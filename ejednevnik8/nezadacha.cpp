        #include "nezadacha.h"
#include "ui_nezadacha.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"
QFile zametkiwrite("zametki.txt");
nezadacha::nezadacha(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nezadacha)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    qDebug() << MainWindow::kak_otkrito;
    ui->lineEdit->setPlaceholderText("Заголовок");
    ui->textEdit->setPlaceholderText("Заметка");
    if (MainWindow::kak_otkrito == 1) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->textBrowser->setText(MainWindow::stroka);
    if (MainWindow::kak_otkrito == 0)
        ui->stackedWidget->setCurrentIndex(0);
    }
}

nezadacha::~nezadacha()
{
    delete ui;
}

void nezadacha::on_pushButton_clicked()
{
    bool ready = false;
    if (ui->textEdit->toPlainText().isEmpty() or ui->textEdit->toPlainText().count(' ') == ui->textEdit->toPlainText().length()) {
        QMessageBox::information(this, "Вы не написали заметку", "Напишите заметку или вернитесь назад.");
        ready = true;
    }
    if (ui->lineEdit->text().isEmpty() or ui->lineEdit->text().count(' ') == ui->lineEdit->text().length()) {
        QMessageBox::information(this, "Вы не написали заголовок", "Напишите заголовок или вернитесь назад.");
        ready = true;
    }
    if (ready == false) {
        textovik = ui->textEdit->toPlainText();
        vnutritextovika = ui->lineEdit->text();
        zametkiwrite.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&zametkiwrite);
        out << vnutritextovika << ";" << textovik << endl;
        ui->textEdit->clear();
        zametkiwrite.close();
        zakril = true;
        close();
    }

}


void nezadacha::on_pushButton_3_clicked()
{
    zametkiwrite.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&zametkiwrite);
    QString s;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(!line.contains(MainWindow::stroka)) {
            s.append(line + "\n");
        }
    }
    zametkiwrite.resize(0);
    in << s;
    zametkiwrite.close();
    MainWindow::udalili_zametku = true;
    close();
}

