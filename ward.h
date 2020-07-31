#ifndef WARD_H
#define WARD_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Ward;
}

class Ward : public QDialog
{
    Q_OBJECT

public:
    explicit Ward(QWidget *parent = nullptr);
    ~Ward();

private slots:
    void on_btnLoadTable_clicked();

    void on_btnPatientAdd_clicked();

    void on_btnAbnormal_clicked();

    void on_btnCritical_clicked();

    void on_btnNormal_clicked();

    void on_btnInvestigationAbnormal_clicked();

    void on_btnInvestigationCritical_clicked();

   // void on_pushButton_4_clicked();

    void on_btnInvestigationNormal_clicked();

    void on_btnPatientUpdate_clicked();

    void on_btnDischarge_clicked();

    void on_btnSearch_clicked();

    void on_btnNewFile_clicked();

    void on_btnOpenFile_clicked();

    void on_btnSaveFile_clicked();

    void on_btnSaveAs_clicked();

    void on_btnNClear_clicked();

private:
    Ui::Ward *ui;
    QString filePath; // save the path of the file
};

#endif // WARD_H
