#include "zametkatime.h"
#include "ui_zametkatime.h"
QFile dateswrite("dates.txt");

zametkatime::zametkatime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zametkatime)
{
    ui->setupUi(this);

}

zametkatime::~zametkatime()
{
    delete ui;
}

void zametkatime::on_pushButton_clicked()
{
    zakril = false;
    bool ready = true;
    QString strochka;
    bool est_v_faile = false;
    QString b = ui->textEdit->toPlainText();
    if (b.isEmpty() or b.count(' ') == b.length()) {
        QMessageBox::information(this, "Вы не написали задачу", "Напишите задачу или вернитесь назад.");
        ready = false;
    }
    QString h, m;
    h = ui->comboBox_2->currentText();
    m = ui->comboBox->currentText();
    if (h.isEmpty() or h.count(' ') == h.length()) {
        QMessageBox::information(this, "Вы не написали время", "Напишите время или вернитесь назад.");
        ready = false;
    }
    if (ready == true) {
        strochka = data + ";" + h + ":" + m + ";" + b;
        dateswrite.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&dateswrite);
        while (!in.atEnd() and est_v_faile == false) {
            QString line = in.readLine();
            if (strochka == line) {
                est_v_faile = true;
                close();
            }
        }
        dateswrite.close();
        if (est_v_faile == false) {
            dateswrite.open(QIODevice::Append | QIODevice::Text);
            QTextStream out(&dateswrite);
            out << data << ";" << h << ":" << m << ";" << b << endl;
            ui->textEdit->clear();
            dateswrite.close();
            v_faile_netu = true;
            zakril = true;
            close();
        }

    }
}






