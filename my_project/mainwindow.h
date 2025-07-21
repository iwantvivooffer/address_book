#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QLineEdit>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QWidget>
#include<QIcon>
#include<QPainter>
#include<QPixmap>
#include<QStackedWidget>
#include<QCoreApplication>
#include<QMessageBox>
#include<QComboBox>

#include"contactmanager.h"
#include"contact.h"
#include"informationpage.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);


private:
    Ui::MainWindow *ui;

    //文件路径名
    QString path = QCoreApplication::applicationDirPath() + "/contacts.json";

    //定义对象
    contactManager m_contact;

    //编辑输入
    QLineEdit*nameEdit;
    QLineEdit*numberEdit;
    QLineEdit*groupEdit;
    QLineEdit*emailEdit;
    QLineEdit*searchEdit;

    //部件定义
    QWidget*nameWidget;
    QWidget*numberWidget;
    QWidget*groupWidget;
    QWidget*emailWidget;

    //下拉菜单
    QComboBox*searchCombo;

    //展示框
    QListWidget*contactlist;

    // 添加信息页面指针
    InformationPage *infoPage; 

    // 添加刷新列表函数
    void refreshContactList();
    void refreshContactListFiltered(const QString &filter,const QString&field);


public slots:
    void onAddContact();
    void onDeleteContact();
    void onFilterGroup();
    void onSearchContact();
    void onContactItemClicked(QListWidgetItem *item); 
    void onInfoPageBackClicked(); // 添加返回按钮点击槽函数
};

#endif // MAINWINDOW_H
