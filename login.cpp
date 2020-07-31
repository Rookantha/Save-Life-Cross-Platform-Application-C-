#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include<QIntValidator>//The QIntValidator class provides a validator that ensures a string contains a valid integer within a specified range
#include<QScrollArea>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/saveLife.png");

    ui->labelLogo->setPixmap(pix);
    ui->labelLogo->setScaledContents( true );
    ui->labelLogo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
/*int w=ui->labelLogo->width();
    int h=ui->labelLogo->height();
    ui->labelLogo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
*/

    ui->lineEditUserName->setValidator(new QIntValidator);  //The QIntValidator class provides a validator that ensures a string contains a valid integer
    ui->lineEditUserName->setPlaceholderText("enter your username ");
    ui->lineEditPsw->setPlaceholderText("enter your password");
    if(!connOpen())
        ui->labelDb->setText("Failed to Open Database");
    else
         ui->labelDb->setText("Database Connected ...");
}

Login::~Login()
{
    delete ui;
}


void Login::on_btnLog_clicked()
{

    QString userID = ui->lineEditUserName->text();
    QString profession= ui->comboBoxUser->currentText();
    //, profession='"+profession+"'
    QString psw = ui->lineEditPsw->text();

  if(!connOpen()){
      qDebug()<<"failed";
      return;
  }
  connOpen();
  QSqlQuery qry;
  qry.prepare("select * from users where userID='"+userID+"' and psw='"+psw+"'");
  if (qry.exec())
  {
      int count=0;
            while(qry.next())
                          {
                          count++;

                          } if (count==1){
                             // ui->labelDb->setText("ok");
                              connClose();
                              this->hide();

                              Laboratory labo;
                              labo.setModal(true);
                              labo.exec();
  /*
                              Doctor doctor;
                              doctor.setModal(true);
                              doctor.exec();
*/
                               }
                            if (count>1)
                              ui->labelDb->setText("duplicate");

                              else if (count<1)
                                ui->labelDb->setText("Username Or Password Incorrect");

                   }

}

void Login::on_btnExit_clicked()
{

}
