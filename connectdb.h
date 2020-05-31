#ifndef CONNECTDB_H
#define CONNECTDB_H

#include "customer.h"
#include "employee.h"
#include "manager.h"
#include "rental.h"
#include "disc.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDriver>

class dbconnect
{
public:
    dbconnect(){}
    ~dbconnect(){}
    bool openDB();
    int judgeNP(QString name, QString pwd, QString type);
    int insertCus(customer Cus);
    int insertRental(rental Ren);
/*     int insertEmp(employee Emp);
    int insertMan(manager Man);
    int insertDisc(disc Disc);

   int findDiscByNM(QString Dname);
    int findDiscByTP(QString Dtyp);
    int findDiscByNO(QString Dno);*/
    QSqlDatabase db;
};
#endif // CONNECTDB_H
