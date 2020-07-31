#include "laboratory.h"
#include "ui_laboratory.h"
#include<QMessageBox>
#include<QIntValidator>//The QIntValidator class provides a validator that ensures a string contains a valid integer within a specified range
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QImage>
#include<QPixmap>
//#include <QPrintDialog>
#include<QColorDialog>
#include<QColor>
#include<QFontDialog>
#include<QFont>

Laboratory::Laboratory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Laboratory)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/saveLife.png");
  //  int w=ui->labelImage->width();
  //  int h=ui->labelImage->height();
    // ui->labelImage->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->lineEditPID->setValidator(new QIntValidator);  //The QIntValidator class provides a validator that ensures a string contains a valid integer
    ui->labelImage->setPixmap(pix);
    ui->labelImage->setScaledContents( true );

    ui->labelImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->lineEditPID->setPlaceholderText("Enter Patient ID Number ");
    ui->textEditDetails->setPlaceholderText("This basic text-editing program enables users to create a document, save a document and upload a document to the database. ");



}

Laboratory::~Laboratory()
{
    delete ui;
}

void Laboratory::on_btnDoctorUpdate_clicked()
{
    Login conn;

    QString pID,scanDescription,scanResults;
    pID=ui->lineEditPID->text();
    scanDescription=ui->textEditDetails->toPlainText();
    scanResults=ui->comboBoxTotalResult->currentText();


    if(scanDescription.isEmpty() && scanResults.isEmpty()&&scanDescription.isEmpty()) {
         QMessageBox::critical(this,tr("Error"),tr("Complete all fields "));
            return;
    }
    if(!conn.connOpen()){
      qDebug()<<"failed";
      return;

    }
  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("update patient set scanDescription='"+scanDescription+"',scanResults='"+scanResults+"' where patientID='"+pID+"'");


  if(qry.exec())
  {
    QMessageBox::information(this,tr("Updated"),tr("Updated successfully"));
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->lineEditDescription->setText("");
    ui->lineEditScan->setText("");
    ui->lineEditResponse->setText("");
    ui->textEditDetails->setText("");


    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
      // QMessageBox::information(this,"not connect","DB not connect");
  }
}

void Laboratory::on_pushButton_clicked()
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
          ui->lineEditDescription->setText(qry.value(8).toString());
          ui->lineEditScan->setText(qry.value(9).toString());
          ui->lineEditResponse->setText(qry.value(10).toString());

      }
    conn.connClose();
    }

  else {
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
  }
}

void Laboratory::on_btnNewFile_clicked()
{
    filePath = "";
    ui->textEditDetails->setText("");// resetting the text edit and globle variable file path
}

void Laboratory::on_btnOpenFile_clicked()
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

void Laboratory::on_btnSaveFile_clicked()
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

void Laboratory::on_btnSaveAs_clicked()
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

void Laboratory::on_btnImageOpen_clicked()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setNameFilter(tr("(*.png *.jpg *.xpm)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString image = QFileDialog::getOpenFileName(this,tr("Open Image"));
   if(!image.isEmpty()){
        QImage imagee(image);
        ui->labelImage->setPixmap(QPixmap::fromImage(imagee));


    }


}

void Laboratory::on_btnScanImmediately_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE scanStates ='Immediately'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Laboratory::on_btnScanNormal_clicked()
{
    Login conn;
    QSqlQueryModel *model= new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry= new QSqlQuery(conn.healthdb);
    qry->prepare("SELECT * FROM patient WHERE scanStates ='Normal'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,tr("Patient ID"));
    model->setHeaderData(8,Qt::Horizontal,tr("Description"));
    model->setHeaderData(9,Qt::Horizontal,tr("Requested Scan"));
    model->setHeaderData(10,Qt::Horizontal,tr("Respond"));
    model->setHeaderData(11,Qt::Horizontal,tr("Scan Reading"));
    model->setHeaderData(12,Qt::Horizontal,tr("Report Summary"));
    model->setHeaderData(13,Qt::Horizontal,tr("Investigation Summary"));
    conn.connClose();

    qDebug()<<(model->rowCount());
}

void Laboratory::on_btnZoomIn_clicked()
{
   // scaled
   // ui->labelImage->scroll(1.25);
}

void Laboratory::on_btnColor_clicked()
{
    QColor color= QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()){
      ui->textEditDetails->setTextColor(color);
    }
}

void Laboratory::on_btnBackColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()){
      ui->textEditDetails->setTextBackgroundColor(color);
    }
}

void Laboratory::on_btnFont_clicked()
{
    // any text selected or not
    bool ok;
    QFont font= QFontDialog::getFont(&ok,this);
    if (ok){
        // adding text
        ui->textEditDetails->setFont(font);

    }else return;
}

void Laboratory::on_btnUndo_clicked()
{
    ui->textEditDetails->undo();
}

void Laboratory::on_btnRedo_clicked()
{
    ui->textEditDetails->redo();
}

void Laboratory::on_btnCopy_clicked()
{
    ui->textEditDetails->copy();
}

void Laboratory::on_btnPaste_clicked()
{
    ui->textEditDetails->paste();
}

void Laboratory::on_btnCut_clicked()
{

}

void Laboratory::on_pushButton_2_clicked()
{
    ui->lineEditPID->setText("");
    ui->lineEditPName->setText("");
    ui->lineEditPAge->setText("");
    ui->lineEditAddress->setText("");
    ui->lineEditWard->setText("");
    ui->lineEditlineEditbedNumber->setText("");
    ui->lineEditGuardian->setText("");
    ui->lineEditDescription->setText("");
    ui->lineEditScan->setText("");
    ui->lineEditResponse->setText("");
    ui->textEditDetails->setText("");
}
