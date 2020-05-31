#ifndef LOGIN_H
#define LOGIN_H

#include "connectdb.h"
#include "mainwindowforcus.h"
#include "mainwindowforemp.h"
#include "mainwindowforman.h"
#include "registerDlg.h"

#include <QDialog>

namespace Ui {
class login;
}

class login: public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *ui;
    MainWindowForCus mwfc;
    MainWindowForEmp mwfe;
    MainWindowForMan mwfm;
    registerDlg *RD=nullptr;
    dbconnect *db=nullptr;

private slots:
    void pushButtonLogin();
    void pushButtonRegister();
    void getMessage();
};

#endif // LOGIN_H
