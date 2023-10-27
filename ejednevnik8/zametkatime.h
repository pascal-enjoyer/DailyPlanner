#ifndef ZAMETKATIME_H
#define ZAMETKATIME_H
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QIntValidator>
namespace Ui {
    class zametkatime;
}

class zametkatime : public QDialog
{
    Q_OBJECT

public:
    explicit zametkatime(QWidget *parent = nullptr);
    ~zametkatime();
    QString data;
    bool napisal = false;
    bool v_faile_netu = false;
    bool zakril = false;
private slots:
    void on_pushButton_clicked();



private:
    Ui::zametkatime *ui;
};

#endif // ZAMETKATIME_H
