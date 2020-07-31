#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QMessageBox>
#include<QLabel>
#include<QSqlQuery>
#include"doctor.h"
#include"ward.h"
#include"laboratory.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
      QSqlDatabase healthdb;
      void connClose(){
          healthdb.close();
          healthdb.removeDatabase(QSqlDatabase::defaultConnection);
      }
      bool connOpen(){
          healthdb = QSqlDatabase::addDatabase("QSQLITE");
          QString currPath = qApp->applicationDirPath();
          //QFile::copy("", qApp->applicationDirPath() + "savelifedb.db");
          healthdb.setDatabaseName(qApp->applicationDirPath() + "savelifedb.db");
          if(!healthdb.open()){

              qDebug()<<("Failed to Open Database");
              return false;

        }
          else{
               qDebug()<<("connected");
               return true;
          }

      }


public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnLog_clicked();

    void on_btnExit_clicked();

private:
    Ui::Login *ui;

};
#endif // LOGIN_H
