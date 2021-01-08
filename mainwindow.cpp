#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox_5->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newRoleToPointer(Role *&pointer)
{
    if(pointer)
        delete pointer;
    int currentRole = ui->comboBox->currentIndex();
    switch (currentRole) {
    case 1:
        pointer=new KeQing;
        break;
    case 2:
        pointer=new Role;
        break;
    default:
        break;
    }
}

int MainWindow::loopMaxInit(QComboBox* pBox,int& loopMin)
{
    int cur=pBox->currentIndex();

    if(cur!=0)
    {
        loopMin=cur;
        return cur+1;
    }
    else
    {
        loopMin=1;
        return pBox->count();
    }
}

void MainWindow::on_role_selected()
{
    ui->comboBox_5->hide();
    //ui->horizontalLayout->removeWidget(ui->comboBox_5);
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    QStringList mWList;
    QStringList mRList;
    QStringList mRMList;
    int currentRole = ui->comboBox->currentIndex()-1;
    switch (currentRole) {
    case 0:
        mWList<<QStringLiteral("武器")
              <<QStringLiteral("匣里龙吟")
              <<QStringLiteral("天空")
              <<QStringLiteral("风鹰剑");

        mRList<<QStringLiteral("圣遗物")
              <<QStringLiteral("如雷2+角斗2")
              <<QStringLiteral("平雷4");

        mRMList<<QStringLiteral("主属性")
             <<QStringLiteral("雷/暴")
             <<QStringLiteral("雷/暴伤")
             <<QStringLiteral("攻/暴")
             <<QStringLiteral("攻/暴伤");
        break;
    case 1:
        mWList<<QStringLiteral("武器")
             <<QStringLiteral("流浪乐章");

        mRList<<QStringLiteral("圣遗物")
              <<QStringLiteral("魔女4")
              <<QStringLiteral("渡火4");

        mRMList<<QStringLiteral("主属性")
             <<QStringLiteral("火/暴")
             <<QStringLiteral("火/暴伤")
             <<QStringLiteral("攻/暴")
             <<QStringLiteral("攻/暴伤");
        ui->comboBox_5->show();
        ui->horizontalLayout->addWidget(ui->comboBox_5);
        break;
    default:
        break;
    }
    ui->comboBox_2->addItems(mWList);
    ui->comboBox_3->addItems(mRList);
    ui->comboBox_4->addItems(mRMList);
}

void MainWindow::on_select_changed()
{
    int currentWeapon = ui->comboBox_2->currentIndex();
    if(currentWeapon)
        s1=true;
    else
        s1=false;
    int currentR = ui->comboBox_3->currentIndex();
    if(currentR)
        s2=true;
    else
        s2=false;
    int currentRM = ui->comboBox_4->currentIndex();
    if(currentRM)
        s3=true;
    else
        s3=false;

    if(s1&&s2&&s3)
    {
        ui->pushButton->setText("计算副属性");

    }
    else
    {
        ui->pushButton->setText("搭配选择");
    }
}

void MainWindow::on_calculate_clicked()
{
    QTableView *tableView = ui->tableView;
    QStandardItemModel* model = new QStandardItemModel();
    QStringList mList;

    //获取角色设置
    int currentRole = ui->comboBox->currentIndex()-1;
    if(currentRole==-1)
        return;

    //调整表格大小
    int chosen=int(s1)+int(s2)+int(s3);
    switch (chosen) {
    case 0:
        tableView->resize(1500, 400);
        break;
    case 1:
        tableView->resize(1000, 400);
        break;
    case 2:
        tableView->resize(850, 400);
        break;
    case 3:
        tableView->resize(1000, 400);
        break;
    default:
        break;
    }
    //表格标题
    mList<<QStringLiteral("有效词条数");
    if(chosen==3)
    {
        mList<<QStringLiteral("攻击百分比")
             <<QStringLiteral("攻击数值")
             <<QStringLiteral("暴击率")
             <<QStringLiteral("暴击伤害");
    }

    doLoop([=,&mList](int i,int j,int k){
        QString title;
        if(!s1)
            title+=ui->comboBox_2->itemText(i);
        if(!s2)
        {
            if(!s1)
                title+='\n';
            title+=ui->comboBox_3->itemText(j);
        }
        if(!s3)
        {
            if(!(s1&&s2))
                title+='\n';
            title+=ui->comboBox_4->itemText(k);
        }
        if(chosen==3)
            title=QStringLiteral("伤害期望");
        mList<<title;
    });
    mList<<QStringLiteral("面板攻击")
         <<QStringLiteral("暴击率")
         <<QStringLiteral("暴击伤害");
    model->setHorizontalHeaderLabels(mList);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //表格内容
    for (int i = 0; i < 45; i++)
    {
        int currentRow=0;
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(i+1)));

        Role* pFinalRole=nullptr;
        Role* pRole=nullptr;
        newRoleToPointer(pFinalRole);
        int row=currentRow;
        doLoop([=,&pRole,&currentRow](int m,int n,int p){
            newRoleToPointer(pRole);
            pRole->WP(m);
            pRole->R(n);
            pRole->RM(p);
            pRole->Resolve(i+1);
            pFinalRole->compare(pRole);

            if(chosen==3)
            {
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->nabp)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->naba)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ncr)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ncd)));
            }

            model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ExpD())));
            delete pRole;
            pRole=nullptr;
        });
        //设置选中方案字体颜色
        doLoop([=,&row](int m,int n,int p){
            if(chosen==3)
            {
                //to do:颜色指示增减
            }
            else
            {
                QStandardItem* pNew=new QStandardItem(QString("%1").arg(pFinalRole->ExpD()));
                if (model->item(i,row)->text()==pNew->text())
                {
                    model->item(i,row)->setForeground(QBrush(QColor(255, 0, 155)));
                }
            }
            row++;
        });
        //assert(row==currentRow);

        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->allAtk())));
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->CriRate)));
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->CriDamage)));
        delete pFinalRole;
        pFinalRole=nullptr;
    }
    tableView->setModel(model);
}

void MainWindow::on_compare_clicked()
{
    QTableView *tableView = ui->tableView;
    QStandardItemModel* model = new QStandardItemModel();
    QStringList mList;

    //获取角色设置
    int currentRole = ui->comboBox->currentIndex()-1;
    if(currentRole==-1)
        return;

    //调整表格大小
    int chosen=int(s1)+int(s2)+int(s3);
    switch (chosen) {
    case 0:
        tableView->resize(1500, 400);
        break;
    case 1:
        tableView->resize(1000, 400);
        break;
    case 2:
        tableView->resize(850, 400);
        break;
    default:
        break;
    }
    //表格标题
    mList<<QStringLiteral("有效词条数");
    if(chosen==3)
    {
        mList<<QStringLiteral("攻击百分比")
             <<QStringLiteral("攻击数值")
             <<QStringLiteral("暴击率")
             <<QStringLiteral("暴击伤害");
    }

    doLoop([=,&mList](int i,int j,int k){
        QString title;
        if(!s1)
            title+=ui->comboBox_2->itemText(i);
        if(!s2)
        {
            if(!s1)
                title+='\n';
            title+=ui->comboBox_3->itemText(j);
        }
        if(!s3)
        {
            if(!(s1&&s2))
                title+='\n';
            title+=ui->comboBox_4->itemText(k);
        }
        if(chosen==3)
            title=QStringLiteral("伤害期望");
        mList<<title;
    });
    mList<<QStringLiteral("面板攻击")
         <<QStringLiteral("暴击率")
         <<QStringLiteral("暴击伤害");
    model->setHorizontalHeaderLabels(mList);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //表格内容
    for (int i = 0; i < 45; i++)
    {
        int currentRow=0;
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(i+1)));

        Role* pFinalRole=nullptr;
        Role* pRole=nullptr;
        newRoleToPointer(pFinalRole);
        int row=currentRow;
        doLoop([=,&pRole,&currentRow](int m,int n,int p){
            newRoleToPointer(pRole);
            pRole->WP(m);
            pRole->R(n);
            pRole->RM(p);
            pRole->Resolve(i+1);
            pFinalRole->compare(pRole);

            if(chosen==3)
            {
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->nabp)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->naba)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ncr)));
                model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ncd)));
            }

            model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pRole->ExpD())));
            delete pRole;
            pRole=nullptr;
        });
        //设置选中方案字体颜色
        doLoop([=,&row](int m,int n,int p){
            QStandardItem* pNew=new QStandardItem(QString("%1").arg(pFinalRole->ExpD()));
            if (model->item(i,row++)->text()==pNew->text())
            {
                model->item(i,row)->setForeground(QBrush(QColor(255, 0, 155)));
            }
        });

        assert(row==currentRow);

        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->allAtk())));
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->CriRate)));
        model->setItem(i, currentRow++, new QStandardItem(QString("%1").arg(pFinalRole->CriDamage)));
        delete pFinalRole;
        pFinalRole=nullptr;
    }
    tableView->setModel(model);
}


