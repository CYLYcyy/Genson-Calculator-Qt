#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include "Role.h"
#include "KeQing.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool s1;
    bool s2;
    bool s3;
    void newRoleToPointer(Role*& pointer);
    int loopMaxInit(QComboBox* pBox,int& loopMin);

    template <typename F>
    void doLoop(F const &f){
        int currentWeapon;
        int currentR;
        int currentRM;

        int maxWeapon = loopMaxInit(ui->comboBox_2,currentWeapon);
        int maxR = loopMaxInit(ui->comboBox_3,currentR);
        int maxRM = loopMaxInit(ui->comboBox_4,currentRM);

        for (int i=currentWeapon;i<maxWeapon ;i++ )
        {
            for (int j=currentR;j<maxR ;j++ )
            {
                for (int k=currentRM;k<maxRM ;k++ )
                {
                    f(i,j,k);
                }
            }
        }
    }

private slots:
    void on_role_selected();
    void on_select_changed();
    void on_calculate_clicked();
    void on_compare_clicked();
};
#endif // MAINWINDOW_H
