#include "mainwindowforman.h"
#include "ui_mainwindowforman.h"

#include <QMessageBox>

MainWindowForMan::MainWindowForMan(QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindowForMan)
{
    ui->setupUi(this);
    this->setWindowTitle("店长");
    DB = new dbconnect();
    TModel = new QSqlTableModel(this, DB->db);
    connect(ui->Save,SIGNAL(clicked()),this, SLOT(pushButtonSave()));
    connect(ui->switch_2,SIGNAL(clicked()),this,SLOT(pushButtonDisc()));
    connect(ui->deletRow,SIGNAL(clicked()),this,SLOT(pushButtonDelet()));
    connect(ui->addRow,SIGNAL(clicked()),this,SLOT(pushButtonAdd()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(pushButtonSearch()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(pushButtonCus()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushButtonEmp()));
}

MainWindowForMan::~MainWindowForMan()
{
    delete ui;
}

void MainWindowForMan::setDiscView()
{
    DB->openDB();
    TModel = new QSqlTableModel(this, DB->db);
    TModel->setTable("disc");
    TModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    TModel->setHeaderData(0,Qt::Horizontal,"碟片号");
    TModel->setHeaderData(1,Qt::Horizontal,"碟片名");
    TModel->setHeaderData(2,Qt::Horizontal,"租借费");
    TModel->setHeaderData(3,Qt::Horizontal,"影片类型");
    TModel->setHeaderData(4,Qt::Horizontal,"租借状态");
    TModel->setHeaderData(5,Qt::Horizontal,"租借次数");
    TModel->select();
    ui->tableView->setModel(TModel);
}

void MainWindowForMan::setCusView()
{
    DB->openDB();
    TModel = new QSqlTableModel(this, DB->db);
    TModel->setTable("customer");
    TModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    TModel->removeColumn(6);
    TModel->setHeaderData(0,Qt::Horizontal,"顾客号");
    TModel->setHeaderData(1,Qt::Horizontal,"顾客名");
    TModel->setHeaderData(2,Qt::Horizontal,"电话");
    TModel->setHeaderData(3,Qt::Horizontal,"顾客类型");
    TModel->setHeaderData(4,Qt::Horizontal,"顾客折扣");
    TModel->setHeaderData(5,Qt::Horizontal,"顾客性别");
    TModel->select();
    ui->tableView->setModel(TModel);
}

void MainWindowForMan::setEmpView()
{
    DB->openDB();
    TModel = new QSqlTableModel(this, DB->db);
    TModel->setTable("employee");
    TModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    TModel->removeColumn(4);
    TModel->setHeaderData(0,Qt::Horizontal,"店员号");
    TModel->setHeaderData(1,Qt::Horizontal,"店员名");
    TModel->setHeaderData(2,Qt::Horizontal,"入职时间");
    TModel->setHeaderData(3,Qt::Horizontal,"薪资");
    TModel->select();
    ui->tableView->setModel(TModel);
}

void MainWindowForMan::pushButtonSave()
{
    QSqlTableModel *TModel2 = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    TModel2->database().transaction();
    if (TModel2->submitAll())
        {
            TModel2->database().commit(); //提交成功，事务将真正修改数据库数据
        } else {
            TModel2->database().rollback(); //提交失败，事务回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(TModel2->lastError().text()));
        }
    TModel->revertAll();
}

void MainWindowForMan::pushButtonDisc()
{
    setDiscView();
    ui->tableView->show();
}

void MainWindowForMan::pushButtonCus()
{
    setCusView();
    ui->tableView->show();
}

void MainWindowForMan::pushButtonEmp()
{
    setEmpView();
    ui->tableView->show();
}

void MainWindowForMan::pushButtonAdd()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
        QSqlRecord record = pMode->record();
        record.setValue(0, "number");
        record.setValue(1, "空");
        record.setValue(2, "空");
        record.setValue(3, "空");
        record.setValue(4, "空");
        record.setValue(5, "空");
        pMode->insertRecord(pMode->rowCount(), record);
        pMode->submitAll();
}

void MainWindowForMan::pushButtonDelet()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    pMode->removeRow(ui->tableView->currentIndex().row());
    pMode->submitAll();
}

void MainWindowForMan::pushButtonSearch()
{
    QString Name = ui->searchline->text();
    if(!ui->discSearch->isChecked()&&!ui->customerSearch->isChecked()&&!ui->radioButton->isChecked())
        QMessageBox::information(this,"提示","请选择搜索类型！",QMessageBox::Ok);
    QString searchtype;
    if(ui->discSearch->isChecked())searchtype = "disc";
    if(ui->customerSearch->isChecked())searchtype = "customer";
    if(ui->radioButton->isChecked())searchtype = "employee";
    if(searchtype == "disc")
    {
        setDiscView();
        TModel->setFilter(QObject::tr("dna = '%1'").arg(Name));
        TModel->select();
    }
    else if(searchtype == "customer")
    {
        setCusView();
        TModel->setFilter(QObject::tr("cna = '%1'").arg(Name));
        TModel->select();
    }
    else
    {
        setEmpView();
        TModel->setFilter(QObject::tr("ena = '%1'").arg(Name));
        TModel->select();
    }
    ui->tableView->show();
}
