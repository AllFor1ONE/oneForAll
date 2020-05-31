#ifndef MAINWINDOWFORCUS_H
#define MAINWINDOWFORCUS_H

#include "connectdb.h"

#include <QMainWindow>
#include <QTableView>

namespace Ui {
class MainWindowForCus;
}

class MainWindowForCus: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForCus(QWidget *parent = nullptr);
    ~MainWindowForCus();
    void getCno(QString cno);
    void setView();

private slots:
    void pushButtonSearch();
    void pushButtonAll();
    void pushButtonPlot();
    void pushButtonScience();
    void pushButtonWar();
    void pushButtonComedy();
    void pushButtonAction();
    void pushButtonThriller();
    void pushButtonAffection();
    void pushButtonBiography();
    void pushButtonHistory();

private:
    Ui::MainWindowForCus *ui;
    QString cno;
    dbconnect *DB = new dbconnect();
    QSqlTableModel *TModel=nullptr;
};

#endif // MAINWINDOWFORCUS_H
