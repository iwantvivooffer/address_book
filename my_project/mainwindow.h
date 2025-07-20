#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QLineEdit>
#include<QListWidget>
#include<QVBoxLayout>
#include<QIcon>
#include<QPainter>
#include<QPixmap>
#include<QMessageBox>

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
    contactManager m_contact;
    QLineEdit*nameEdit;
    QLineEdit*numberEdit;
    QLineEdit*groupEdit;
    QLineEdit*emileEdit;
    QListWidget*contactlist;
    
    // 添加刷新列表函数
    void refreshContactList();

public slots:
    void onAddContact();
    void onDeleteContact();
    void onFilterGroup();
};

#endif // MAINWINDOW_H
