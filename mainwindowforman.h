#ifndef MIANWINDOWFORMAN_H
#define MIANWINDOWFORMAN_H

#include <QMainWindow>
#include <QTableView>
#include "connectdb.h"

namespace Ui {
class MainWindowForMan;
}

class MainWindowForMan: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForMan(QWidget *parent = nullptr);
    ~MainWindowForMan();
    void setDiscView();
    void setCusView();
    void setEmpView();

private slots:
    void pushButtonSave();
    void pushButtonDisc();
    void pushButtonCus();
    void pushButtonAdd();
    void pushButtonDelet();
    void pushButtonSearch();
    void pushButtonEmp();

private:
    Ui::MainWindowForMan *ui;
    dbconnect *DB;
    QSqlTableModel *TModel;
};

#endif // MIANWINDOWFORMAN_H
