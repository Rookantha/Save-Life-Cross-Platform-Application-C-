#ifndef LABORATORY_H
#define LABORATORY_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Laboratory;
}

class Laboratory : public QDialog
{
    Q_OBJECT

public:
    explicit Laboratory(QWidget *parent = nullptr);
    ~Laboratory();

private slots:
    void on_btnDoctorUpdate_clicked();

    void on_pushButton_clicked();

    void on_btnNewFile_clicked();

    void on_btnOpenFile_clicked();

    void on_btnSaveFile_clicked();

    void on_btnSaveAs_clicked();

    void on_btnImageOpen_clicked();

    void on_btnScanImmediately_clicked();

    void on_btnScanNormal_clicked();

    void on_btnZoomIn_clicked();

    void on_btnColor_clicked();

    void on_btnBackColor_clicked();

    void on_btnFont_clicked();

    void on_btnUndo_clicked();

    void on_btnRedo_clicked();

    void on_btnCopy_clicked();

    void on_btnPaste_clicked();

    void on_btnCut_clicked();

    void on_pushButton_2_clicked();

private: // private access modifier
    Ui::Laboratory *ui;
    QString filePath; // save the path of the file
   // void scaleImage(double factor);

   // QImage image;
};

#endif // LABORATORY_H
