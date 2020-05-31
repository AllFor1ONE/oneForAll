#include "connectdb.h"

bool dbconnect::openDB()
{
    /*db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString::fromLocal8Bit("QTDSN");
    db.setHostName("172.0.0.1");
    db.setDatabaseName(dsn);
    db.setUserName("admin");
    db.setPassword("sasasasa");*/
    db = QSqlDatabase::addDatabase("QODBC");
    QString serverName = "DESKTOP-0HB1MU9\\SQLEXPRESS";
    QString dbName = "discRentalSystem";
    QString dsn = QString("Driver={SQL Server};Server=%1;Database=%2;Trusted_Connection=yes").arg(serverName).arg(dbName);
    db.setDatabaseName(dsn);
    if(!db.open())return false;
    return true;
}
int dbconnect::judgeNP(QString name, QString pwd, QString ptype)
{
    if(!openDB())return -2;
    QSqlQuery query(db);
    if(ptype == "manager")
    {
        QString sql1 = QString("select mps from manager where mno = '%1'").arg(name);
        query.exec(sql1);
        if(query.next())
        {
            if(query.value(0).toString()==pwd)
                return 1;
            return 0;
        }
        return -1;
    }
    if(ptype == "employee")
    {
        QString sql2 = QString("select eps from employee where eno = '%1'").arg(name);
        query.exec(sql2);
        if(query.next())
        {
            if(query.value(0).toString()==pwd)
                return 1;
            return 0;
        }
        return -1;
    }
    if(ptype == "customer")
    {
        QString sql3 = QString("select cps from customer where cno = '%1'").arg(name);
        query.exec(sql3);
        if(query.next())
        {
            if(query.value(0).toString()==pwd)
                return 1;
            return 0;
        }
        return -1;
    }
    return -2;
}

int dbconnect::insertCus(customer Cus)
{
    if(!openDB())return -2;
    QSqlQuery query2(db);
    query2.prepare("insert into customer(cno,cna,cte,sex,cps) values(?,?,?,?,?)");
    query2.bindValue(0,Cus.cno);
    query2.bindValue(1,Cus.cna);
    query2.bindValue(2,Cus.cte);
    query2.bindValue(3,Cus.sex);
    query2.bindValue(4,Cus.cps);
    if(!query2.exec())
        return 0;
    return 1;
}

/*int dbconnect::insertEmp(employee Emp)
{
    if(!openDB())return -1;
    QSqlQuery query(db);
    QString sql = QString("insert into employee valus('%1','%2','%3',%4,'%5')")
            .arg(Emp.eno)
            .arg(Emp.ena)
            .arg(Emp.eed)
            .arg(Emp.es)
            .arg(Emp.eps);
    if(!query.exec(sql))
        return 0;
    db.close();
    return 1;
}

int dbconnect::insertMan(manager Man)
{
    if(!openDB())return -1;
    QSqlQuery query(db);
    QString sql = QString("insert into manager valus('%1','%2','%3')")
            .arg(Man.mno)
            .arg(Man.mna)
            .arg(Man.mps);
    if(!query.exec(sql))
        return 0;
    db.close();
    return 1;
}

int dbconnect::insertDisc(disc Disc)
{
    if(!openDB())return -1;
    QSqlQuery query(db);
    QString sql = QString("insert into Disc valus('%1','%2',%3,'%4')")
            .arg(Disc.dno)
            .arg(Disc.dna)
            .arg(Disc.drf)
            .arg(Disc.dit);
    if(!query.exec(sql))
        return 0;
    db.close();
    return 1;
}
*/
int dbconnect::insertRental(rental Ren)
{
    if(!openDB())return -1;
    QSqlQuery query(db);
    QString sql = QString("insert into rental(cno,dno,rsd,dlt,dpf) valus('%1','%2','%3',%4,'%5')")
            .arg(Ren.cno)
            .arg(Ren.dno)
            .arg(Ren.rsd)
            .arg(Ren.dlt)
            .arg(Ren.dpf);
    if(!query.exec(sql))
        return 0;
    db.close();
    return 1;
}
