#include "ward.h"
#include "ui_ward.h"
#include"login.h"
#include<QtSql>
#include"ward.h"
#include"login.h"
#include<QIntValidator>//The QIntValidator class provides a validator that ensures a string contains a valid integer within a specified range
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QImage>
#include<QPixmap>

Ward::Ward(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ward)
{    
    ui->setupUi(this);
    ui->lineEditPID->setPlaceholderText("Enter Patient ID Number ");
    ui->textEditDetails->setPlaceholderText("This basic text-editing program enables users to create a document, save a document and upload a document to the database. ");
    ui->lineEditPID->setValidator(new QIntValidator);  //The QIntValidator class provides a validator that ensures a string contains a valid integer
    Login conn;
    if(!conn.connOpen())
                ui->labelWardDb->setText("Failed to open Database");
            else
                ui->labelWardDb->setText("Database Connected....");
}

Ward::~Ward()
{
    delete ui;
}

void Ward::on_btnLoadTable_clicked()
{
Login conn;
QSqlQueryModel *model= new QSqlQueryModel();
conn.connOpen();
QSqlQuery* qry= new QSqlQuery(conn.healthdb);
qry->prepare("SELECT * FROM patient" );
qry->exec();
model->setQuery(*qry);
ui->tableView->setModel(model);
model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
model->setHeaderData(1,Qt::Horizontal,tr("Name"));
model->setHeaderData(2,Qt::Horizontal,tr("Age"));
model->setHeaderData(3,Qt::Horizontal,tr("Address"));
model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
model->setHeaderData(8,Qt::Horizontal,tr("Description"));
model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
conn.connClose();

qDebug()<<(model->rowCount());
}

void Ward::on_btnPatientAdd_clicked()
{
    Login conn;

    QString pID,pName,pAge,pAddress,pWard,pGuardian,bedNumber,NurseNote;
    pID=ui->lineEditPID->text();
    pName=ui->lineEditPName->text();
    pAge=ui->lineEditPAge->text();
    pAddress=ui->lineEditAddress->text();
    pWard=ui->lineEditWard->text();
    pGuardian=ui->lineEditGuardian->text();
    bedNumber=ui->lineEditlineEditbedNumber->text();
    NurseNote=ui->textEditDetails->toPlainText();

    if(pID.isEmpty() && pName.isEmpty() && pAge.isEmpty() && pAddress.isEmpty() && pWard.isEmpty() && pGuardian.isEmpty() && bedNumber.isEmpty()){
         QMessageBox::critical(this,tr("Error"),tr("Complete all fields "));
            return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("insert into patient(patientID,patientName,age,address,ward,guardian,bedNumber,nurseNote)""values('"+pID+"','"+pName+"','"+pAge+"','"+pAddress+"','"+pWard+"','"+pGuardian+"','"+bedNumber+"','"+NurseNote+"')");


  if(qry.exec())
  {
    QMessageBox::critical(this,tr(" Admitted"),tr("Admission successfully"));
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->textEditDetails->setText("");
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
      // QMessageBox::information(this,"not connect","DB not connect");
  }
}

void Ward::on_btnAbnormal_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE scanResults ='Abnormal'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Age"));
    model->setHeaderData(3,Qt::Horizontal,tr("Address"));
    model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
    model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
    model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
    model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());

}

void Ward::on_btnCritical_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE scanResults ='Critical'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Age"));
    model->setHeaderData(3,Qt::Horizontal,tr("Address"));
    model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
    model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
    model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
    model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Ward::on_btnNormal_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE scanResults ='Normal'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Age"));
    model->setHeaderData(3,Qt::Horizontal,tr("Address"));
    model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
    model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
    model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
    model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Ward::on_btnInvestigationAbnormal_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE investigationResults ='Abnormal'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Age"));
    model->setHeaderData(3,Qt::Horizontal,tr("Address"));
    model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
    model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
    model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
    model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Ward::on_btnInvestigationCritical_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE investigationResults ='Critical'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Ward::on_btnInvestigationNormal_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE investigationResults ='Normal'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,tr("Age"));
    model->setHeaderData(3,Qt::Horizontal,tr("Address"));
    model->setHeaderData(4,Qt::Horizontal,tr("Ward Number"));
    model->setHeaderData(5,Qt::Horizontal,tr("Bed Number"));
    model->setHeaderData(6,Qt::Horizontal,tr("Guardian Details"));
    model->setHeaderData(7,Qt::Horizontal,tr("Nurse Notes"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Ward::on_btnPatientUpdate_clicked()
{
    Login conn;
    QString pID,pName,pAge,pAddress,pWard,pGuardian,bedNumber,NurseNote;
    pID=ui->lineEditPID->text();
    pName=ui->lineEditPName->text();
    pAge=ui->lineEditPAge->text();
    pAddress=ui->lineEditAddress->text();
    pWard=ui->lineEditWard->text();
    pGuardian=ui->lineEditGuardian->text();
    bedNumber=ui->lineEditlineEditbedNumber->text();
    NurseNote=ui->textEditDetails->toPlainText();


    if(pID.isEmpty() && pName.isEmpty() && pAge.isEmpty() && pAddress.isEmpty() && pWard.isEmpty() && pGuardian.isEmpty() && bedNumber.isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("Complete all fields "));
           return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("update patient set patientID='"+pID+"', patientName='"+pName+"',age='"+pAge+"',address='"+pAddress+"',ward='"+pWard+"',guardian='"+pGuardian+"',bedNumber='"+bedNumber+"',nurseNote='"+NurseNote+"'where patientID='"+pID+"'");


  if(qry.exec())
  {
    QMessageBox::information(this,tr("updated"),tr("Updated Sucuessfull"));
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->textEditDetails->setText("");
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());

  }
}

void Ward::on_btnDischarge_clicked()
{
    Login conn;
    QString pID;
    pID=ui->lineEditPID->text();

    if(pID.isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("Complete all fields "));
           return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("delete from patient where patientID='"+pID+"'");


  if(qry.exec())
  {
    QMessageBox::information(this,tr("Deleted"),tr("Deleted Sucuessfull"));
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->textEditDetails->setText("");
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());

  }
}

void Ward::on_btnSearch_clicked()
{
    Login conn;
    QString pID=ui->lineEditPID->text();

    if(pID.isEmpty()){
         QMessageBox::critical(this,tr("Error"),tr(" ID Field is Empty"));
            return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("select * from patient where patientID='"+pID+"'");

  if(qry.exec())
  {
      while (qry.next()) {
          ui->lineEditPName->setText(qry.value(1).toString());
          ui->lineEditPAge->setText(qry.value(2).toString());
          ui->lineEditAddress->setText(qry.value(3).toString());
          ui->lineEditWard->setText(qry.value(4).toString());
          ui->lineEditlineEditbedNumber->setText(qry.value(5).toString());
          ui->lineEditGuardian->setText(qry.value(6).toString());
      }
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
  }
}

void Ward::on_btnNewFile_clicked()
{
    filePath = "";
    ui->textEditDetails->setText("");// resetting the text edit and globle variable file path
}

void Ward::on_btnOpenFile_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Open file");
    QFile file(fileName);
    filePath=fileName;

    if(!file.open(QFile::ReadOnly | QFile::Text)){
       QMessageBox::warning(this,"..","File Not Open");
       return;
    }
    QTextStream in(&file);
    QString text =in.readAll();
    ui->textEditDetails->setText(text);
    file.close();
}

void Ward::on_btnSaveFile_clicked()
{
    QFile file(filePath);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
       QMessageBox::warning(this,"..","File Not Open");
       return;
    }
    QTextStream out(&file);
    QString text =ui->textEditDetails->toPlainText();
    out<< text;
    file.flush();
    file.close();
}

void Ward::on_btnSaveAs_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(fileName);
    filePath=fileName;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
       QMessageBox::warning(this,"..","File Not Open");
       return;
    }
    QTextStream out(&file);
    QString text =ui->textEditDetails->toPlainText();
    out<< text;
    file.flush();
    file.close();
}

void Ward::on_btnNClear_clicked()
{
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->textEditDetails->setText("");
}
