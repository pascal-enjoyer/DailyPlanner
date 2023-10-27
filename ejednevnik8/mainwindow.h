#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QDebug>
#include <QMainWindow>
#include <QDateTime>
#include <QTextStream>
#include <QListWidgetItem>
#include <QTimer>
#include <QCalendarWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static int kak_otkrito;
    static bool udalili_zametku;
    static QString stroka;
    static QString interface_language;
    static QString interface_scale;
    static QString time_format;
    static QString chasovoy_poyas;
    ~MainWindow();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_AddpushButton_3_clicked();

    void UpdateTime();

    void on_calendarWidget_selectionChanged();

    void on_DeletepushButton_4_clicked();
    void on_pushButton_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_zametkilist_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
};
#endif // MAINWINDOW_H
