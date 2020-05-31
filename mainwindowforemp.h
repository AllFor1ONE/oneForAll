#ifndef MAINWINDOWFOREMP_H
#define MAINWINDOWFOREMP_H

#include <QMainWindow>
#include <QTableView>
#include "connectdb.h"

namespace Ui {
class MainWindowForEmp;
}

class MainWindowForEmp: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForEmp(QWidget *parent = nullptr);
    ~MainWindowForEmp();
    void setDiscView();
    void setCusView();
    void setRentalView();

private slots:
    void pushButtonSave();
    void pushButtonDisc();
    void pushButtonCus();
    void pushButtonAdd();
    void pushButtonDelet();
    void pushButtonSearch();
    void pushButtonAddRental();

private:
    Ui::MainWindowForEmp *ui;
    QSqlTableModel *TModel;
    dbconnect *DB;
};

#endif // MAINWINDOWFOREMP_H
