#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QLineEdit>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QIcon>
#include<QPainter>
#include<QPixmap>


#include"contactmanager.h"
#include"contact.h"

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


    //定义对象
    contactManager m_contact;

    //输入栏
    QLineEdit*nameEdit;
    QLineEdit*numberEdit;
    QLineEdit*groupEdit;
    QLineEdit*emileEdit;

    //List清单
    QListWidget*contactlist;


public slots:
    void onAddContact();
    void onDeleteContact();
    void onFilterGroup();
};

#endif // MAINWINDOW_H
