#include "login.h"
#include "ui_login.h"
#include "registerDlg.h"


login::login(QWidget *parent):
    QDialog (parent),
    ui(new Ui::login)
{
    db = new dbconnect();
    RD = new registerDlg(this);
    ui->setupUi(this);
    this->setWindowTitle("登录界面");
    connect(ui->login_2, SIGNAL(released()), this, SLOT(pushButtonLogin()));
    connect(ui->register_2, SIGNAL(released()), this ,SLOT(pushButtonRegister()));
    connect(ui->quitButton,SIGNAL(released()),this,SLOT(close()));
    connect(RD,SIGNAL(sendMessage()),this, SLOT(getMessage()));
}

login::~login()
{
    delete ui;
}

void login::pushButtonLogin()
{
    QString name = ui->nameword->text();
    QString pwd = ui->password->text();
    QString ptype;//存放登录人员类型
    if(ui->cusButton->isChecked())ptype = "customer";
    if(ui->empButton->isChecked())ptype = "employee";
    if(ui->manButton->isChecked())ptype = "manager";
    if(ptype.isEmpty())
    {
        QMessageBox::information(this,"提示","请选择登录类型！",QMessageBox::Ok);
    }
    else if((!name.isEmpty())&&(!pwd.isEmpty()))
        {
            int i = db->judgeNP(name, pwd, ptype);
            if(i == 1)
            {
                if(ptype == "customer")
                {
                    //mwfc.setAttribute(Qt::WA_DeleteOnClose);
                    mwfc.show();
                    mwfc.getCno(name);
                    this->close();
                }
               if(ptype == "employee")
                {
                    //mwfe.setAttribute(Qt::WA_DeleteOnClose);
                    mwfe.show();
                    this->close();
                }
                if(ptype == "manager")
                {
                    //mwfm.setAttribute(Qt::WA_DeleteOnClose);
                    mwfm.show();
                    this->close();
                }
            }
            else if(i == 0)
               QMessageBox::information(this,"提示","登录失败！账号或密码错误",QMessageBox::Ok);
            else if(i == -1)
               QMessageBox::information(this,"提示","未注册用户请先注册！",QMessageBox::Ok);
            else
               QMessageBox::information(this,"提示","登录失败！出现了未知的错误",QMessageBox::Ok);
        }
        else QMessageBox::information(this,"提示","请输入账号和密码！",QMessageBox::Ok);
}

void login::pushButtonRegister()
{
    RD->show();
    this->hide();
}

void login::getMessage()
{
    this->show();
}
