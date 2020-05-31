#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include "connectdb.h"

#include <QDialog>
#include <QMessageBox>

#include "customer.h"

namespace Ui {
class registerDlg;
}

class registerDlg: public QDialog
{
    Q_OBJECT

public:
    explicit registerDlg(QWidget *parent = nullptr);
    ~registerDlg();

signals:
    void sendMessage();

private slots:
    void pushButtonConfirm();
    void pushButtonQuit();

private:
    Ui::registerDlg *ui;
    dbconnect *db;
    customer cus;
};

#endif // REGISTERDLG_H

