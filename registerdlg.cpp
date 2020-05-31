#include "registerDlg.h"
#include "ui_registerDlg.h"

registerDlg::registerDlg(QWidget *parent):
    QDialog (parent),
    ui(new Ui::registerDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
    db = new dbconnect();
    connect(ui->confirmButton, SIGNAL(released()),this,SLOT(pushButtonConfirm()));
    connect(ui->quitButton,SIGNAL(released()),this,SLOT(pushButtonQuit()));
}

registerDlg::~registerDlg()
{
    delete ui;
}

void registerDlg::pushButtonConfirm()
{
    cus.cno = cus.cte = ui->phoneline->text();
    cus.cna = ui->nameline->text();
    cus.sex = ui->manButton->isChecked()?"男":"女";
    cus.cps = ui->passline->text();
    QString confirmpwd = ui->cnfmPwLn->text();
    if(cus.cps != confirmpwd)
        QMessageBox::information(this,"提示","两次密码不相符",QMessageBox::Ok);
    else if((!cus.cno.isEmpty())&&(!cus.cna.isEmpty())&&(!cus.cps.isEmpty())&&(!cus.cte.isEmpty())&&(!cus.sex.isEmpty()))
        {
            int i = db->insertCus(cus);
            if(i == 1)
            {
                QMessageBox::information(this,"提示","注册成功！",QMessageBox::Ok);
                emit sendMessage();
            }
            else
                QMessageBox::information(this,"提示","注册失败！",QMessageBox::Ok);
        }
        else
            QMessageBox::information(this,"提示","请将信息填写完整！",QMessageBox::Ok);

}

void registerDlg::pushButtonQuit()
{
    emit sendMessage();
    this->close();
}
