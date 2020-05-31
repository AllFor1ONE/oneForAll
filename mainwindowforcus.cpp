#include "mainwindowforcus.h"
#include "ui_mainwindowforcus.h"

#include <QMessageBox>

MainWindowForCus::MainWindowForCus(QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindowForCus)
{
    ui->setupUi(this);
    this->setWindowTitle("顾客");
    connect(ui->searchButton,SIGNAL(released()),this,SLOT(pushButtonSearch()));
    connect(ui->allButton,SIGNAL(released()),this,SLOT(pushButtonAll()));
    connect(ui->plotButton,SIGNAL(released()),this,SLOT(pushButtonPlot()));
    connect(ui->scienceButton,SIGNAL(released()),this,SLOT(pushButtonScience()));
    connect(ui->warButton,SIGNAL(released()),this,SLOT(pushButtonWar()));
    connect(ui->comedyButton,SIGNAL(released()),this,SLOT(pushButtonComedy()));
    connect(ui->actionButton,SIGNAL(released()),this,SLOT(pushButtonAction()));
    connect(ui->thrillerButton,SIGNAL(released()),this,SLOT(pushButtonThriller()));
    connect(ui->affectionButton,SIGNAL(released()),this,SLOT(pushButtonAffection()));
    connect(ui->biographyButton,SIGNAL(released()),this,SLOT(pushButtonBiography()));
    connect(ui->historyButton,SIGNAL(released()),this,SLOT(pushButtonHistory()));
}

MainWindowForCus::~MainWindowForCus()
{
    delete ui;
}

void MainWindowForCus::setView()
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
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindowForCus::getCno(QString cno)
{
    this->cno = cno;
}
void MainWindowForCus::pushButtonSearch()
{
    QString moiveName = ui->searchline->text();
    TModel->setFilter(QObject::tr("dna = '%1'").arg(moiveName));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonAll()
{
    setView();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonPlot()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='剧情片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonWar()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='战争片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonAction()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='动作片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonComedy()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='喜剧片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonScience()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='科幻片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonThriller()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='恐怖片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonAffection()
{
    setView();
    TModel->setFilter(QObject::tr("dit ='爱情片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonBiography()
{
    TModel->setFilter(QObject::tr("dit ='传记片'"));
    TModel->select();
    ui->tableView->show();
}

void MainWindowForCus::pushButtonHistory()
{

    QSqlQuery query(DB->db);
    QString sql = QString("select ct from customer where cno = '%1'").arg(cno);
    query.exec(sql);
    if(query.next())
    {
        if(query.value(0).toInt() == 1)
        {
            TModel->setTable("rental");
            TModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            TModel->setFilter(QObject::tr("cno = '%1'").arg(cno));
            TModel->removeColumn(0);
            TModel->setHeaderData(0,Qt::Horizontal,"碟片号");
            TModel->setHeaderData(1,Qt::Horizontal,"租借开始日期");
            TModel->setHeaderData(2,Qt::Horizontal,"预租时间");
            TModel->setHeaderData(3,Qt::Horizontal,"归还日期");
            TModel->setHeaderData(4,Qt::Horizontal,"预付押金");
            TModel->select();
            ui->tableView->setModel(TModel);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableView->show();
        }
        else QMessageBox::information(this,"提示","您不是尊贵的会员用户！",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"提示","出现了未知的错误！",QMessageBox::Ok);
}

