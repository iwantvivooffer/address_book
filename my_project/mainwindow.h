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
#include "AlphabetIndexBar.h"
#include "PinyinHelper.h"

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
    bool getLanguageState() const{return isChinese;};
    bool isDarkMode = false;//光暗标志
    bool isChinese=true;//语言标志

private:
    Ui::MainWindow *ui;

    //文件路径名
    QString path = QCoreApplication::applicationDirPath() + "/contacts.json";

    //定义对象
    contactManager m_contact;

    //编辑输入
    QLineEdit*searchEdit;

    //下拉菜单
    QComboBox*searchCombo;

    //展示框
    QListWidget*contactlist;

    //按键
    QPushButton*addButton;
    QPushButton*langButton;
    QPushButton *modeToggleButton;// 光暗切换按钮

    // 添加信息页面指针
    InformationPage *infoPage;

    AlphabetIndexBar* indexBar;  // 字母索引条
    QLabel *indexPopup = nullptr; // 添加提示标签
    
    // 刷新列表函数
    void refreshContactList();
    void refreshContactListFiltered(const QString &filter,const QString&field);
    //语言转换函数   
    void updateUILanguage();
    // 样式切换函数
    void applyDarkMode();
    void applyLightMode();


public slots:
    void onDeleteContact(QString name);
    void onSearchContact();//搜索按钮槽函数
    void onContactItemClicked(QListWidgetItem *item);//信息栏点击
    void onInfoPageBackClicked(); // 返回按钮点击槽函数
    void onSaveContact(const contact original,const contact modified);//保存槽函数
    void onAddButtonClicked();//添加槽函数
    void toggleLanguage();//语言转换槽函数
    void toggleDarkMode();// 光暗模式切换槽函数

};

#endif // MAINWINDOW_H
