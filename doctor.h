#ifndef DOCTOR_H
#define DOCTOR_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Doctor;
}

class Doctor : public QDialog
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    ~Doctor();

private slots:
    void on_pushButton_clicked();

    void on_btnDoctorUpdate_clicked();

    void on_pushButton_2_clicked();

    void on_btnWard_clicked();

    void on_btnAbnormal_clicked();

    void on_btnCritical_clicked();

    void on_btnNormal_clicked();

    void on_btnLoadTable_clicked();

    void on_btnSearch_clicked();

    void on_btnInvestigationAbnormal_clicked();

    void on_btnInvestigationCritical_clicked();

    void on_btnInvestigationNormal_clicked();

   // void on_pushButton_4_clicked();

    void on_btnView_clicked();

    void on_btnNewFile_clicked();

    void on_btnOpenFile_clicked();

    void on_btnSaveFile_clicked();

    void on_btnSaveAs_clicked();

    void on_btnFont_clicked();

    void on_btnColor_clicked();

    void on_btnBackColor_clicked();

    void on_btnRedo_clicked();

    void on_btnUndo_clicked();

    void on_btnPaste_clicked();

    void on_btnCopy_clicked();

    void on_btnClear_clicked();

private:
    Ui::Doctor *ui;
    QString filePath; // save the path of the file


};

#endif // DOCTOR_H
