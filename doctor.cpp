#include "doctor.h"
#include "ui_doctor.h"
#include<QtSql>
#include"ward.h"
#include"login.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QImage>
#include<QIntValidator>//The QIntValidator class provides a validator that ensures a string contains a valid integer within a specified range
#include<QPixmap>
//#include <QPrintDialog>
#include<QColorDialog>
#include<QColor>
#include<QFontDialog>
#include<QFont>

Doctor::Doctor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
    ui->lineEditPID->setPlaceholderText("Enter Patient ID Number ");
    ui->textEditDetails->setPlaceholderText("This basic text-editing program enables users to create a document, save a document and upload a document to the database. ");

    ui->lineEditPID->setValidator(new QIntValidator);
    Login conn;
    if(!conn.connOpen())
                ui->labelDoctorDb->setText("Failed to open Database");
            else
                ui->labelDoctorDb->setText("Database Connected....");
}

Doctor::~Doctor()
{
    delete ui;
}

void Doctor::on_pushButton_clicked()
{

}

void Doctor::on_btnDoctorUpdate_clicked()
{
    Login conn;

    QString pID,pDescription,pScan,scanStates,investigationResults;
    pID=ui->lineEditPID->text();
    pDescription=ui->textEditDetails->toPlainText();
    pScan=ui->lineEditScan->text();
    scanStates=ui->comboBoxScanStates->currentText();
    investigationResults=ui->comboBoxinvestigationResults->currentText();

    if(pDescription.isEmpty() && pScan.isEmpty()){
         QMessageBox::critical(this,tr("Error"),tr("Complete all fields "));
            return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("update patient set description='"+pDescription+"',scan='"+pScan+"',scanStates='"+scanStates+"',investigationResults='"+investigationResults+"'where patientID='"+pID+"'");


  if(qry.exec())
  {
    QMessageBox::information(this,tr("Updated "),tr("Updated successfully"));
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->lineEditNurseNote->setText("");
    ui->textEditDetails->setText("");
    ui->lineEditScan->setText("");
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());

  }
}

void Doctor::on_pushButton_2_clicked()
{

}

void Doctor::on_btnWard_clicked()
{
    Ward ward;
    ward.setModal(true);
    this->hide();
    ward.exec();
}

void Doctor::on_btnAbnormal_clicked()
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

void Doctor::on_btnCritical_clicked()
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

void Doctor::on_btnNormal_clicked()
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

void Doctor::on_btnLoadTable_clicked()
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

void Doctor::on_btnSearch_clicked()
{
    Login conn;
    QString pID=ui->lineEditPID->text();

    if(pID.isEmpty()){
         QMessageBox::critical(this,tr("Error"),tr("ID Field is Empty"));
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
          ui->lineEditNurseNote->setText(qry.value(7).toString());

      }
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
  }
}

void Doctor::on_btnInvestigationAbnormal_clicked()
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

void Doctor::on_btnInvestigationCritical_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE investigationResults ='Critical'");
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

void Doctor::on_btnInvestigationNormal_clicked()
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

void Doctor::on_btnView_clicked()
{
    Login conn;

    QString pID=ui->lineEditPatientDetails->text();
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient where patientID='"+pID+"'" );
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

void Doctor::on_btnNewFile_clicked()
{
    filePath = "";
    ui->textEditDetails->setText("");// resetting the text edit and globle variable file path
}

void Doctor::on_btnOpenFile_clicked()
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

void Doctor::on_btnSaveFile_clicked()
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

void Doctor::on_btnSaveAs_clicked()
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

void Doctor::on_btnFont_clicked()
{
    // any text selected or not
    bool ok;
    QFont font= QFontDialog::getFont(&ok,this);
    if (ok){
        // adding text
        ui->textEditDetails->setFont(font);

    }else return;
}

void Doctor::on_btnColor_clicked()
{
    QColor color= QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()){
      ui->textEditDetails->setTextColor(color);
    }
}

void Doctor::on_btnBackColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()){
      ui->textEditDetails->setTextBackgroundColor(color);
    }
}

void Doctor::on_btnRedo_clicked()
{
    ui->textEditDetails->redo();
}

void Doctor::on_btnUndo_clicked()
{
    ui->textEditDetails->undo();
}

void Doctor::on_btnPaste_clicked()
{
    ui->textEditDetails->paste();
}

void Doctor::on_btnCopy_clicked()
{
    ui->textEditDetails->copy();
}

void Doctor::on_btnClear_clicked()
{
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->lineEditNurseNote->setText("");
    ui->textEditDetails->setText("");
    ui->lineEditScan->setText("");


}
