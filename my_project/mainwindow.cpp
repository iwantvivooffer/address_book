#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWidget>
#include<QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(500,950);


    //图标
    setWindowIcon(QIcon("://res/picture/icon.jpg"));

    //部件
    QWidget*central=new QWidget(this);
    QVBoxLayout*layout=new QVBoxLayout(central);



    //输入栏
    nameEdit=new QLineEdit;
    numberEdit=new QLineEdit;
    groupEdit=new QLineEdit;
    emileEdit=new QLineEdit;


    //按键
    QPushButton*addbtn=new QPushButton("添加联系人");
    QPushButton*delbth=new QPushButton("删除联系人");
    QPushButton*filterbtn=new QPushButton("按组查看");

    //毛玻璃效果
    QString blurStyle = R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        padding: 6px;
        color: black;
    )";
    nameEdit->setStyleSheet(blurStyle);
    numberEdit->setStyleSheet(blurStyle);
    groupEdit->setStyleSheet(blurStyle);
    emileEdit->setStyleSheet(blurStyle);

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    addbtn->setStyleSheet(blurStyle);
    delbth->setStyleSheet(blurStyle);
    filterbtn->setStyleSheet(blurStyle);

    //list
    contactlist=new QListWidget;
    contactlist->setStyleSheet(R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        color: black;
    )");

    //输入展示
    layout->addWidget(new QLabel("姓名："));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("电话："));
    layout->addWidget(numberEdit);
    layout->addWidget(new QLabel("组别："));
    layout->addWidget(groupEdit);
    layout->addWidget(new QLabel("邮箱："));
    layout->addWidget(emileEdit);
    layout->addWidget(addbtn);
    layout->addWidget(delbth);
    layout->addWidget(filterbtn);
    layout->addWidget(contactlist);

    setCentralWidget(central);

    connect(addbtn,&QPushButton::clicked,this,&MainWindow::onAddContact);
    connect(delbth,&QPushButton::clicked,this,&MainWindow::onDeleteContact);
    connect(filterbtn,&QPushButton::clicked,this,&MainWindow::onFilterGroup);

}


//背景(出现显示不完全的情况）
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bg(":/res/picture/bk3.webp");
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg); // 自动缩放图片填满整个窗口
    }
}

//槽函数实现
void MainWindow::onAddContact(){
    QString name=nameEdit->text();
    QString number=numberEdit->text();
    QString group=groupEdit->text();
    QString emile=emileEdit->text();

    if(name.isEmpty()||number.isEmpty())
        return;
    contact temp(name,number,group,emile);
    m_contact.addcontact(temp);
    contactlist->addItem(QString("%1                         %2").arg(name,group));

}

void MainWindow::onDeleteContact(){
    QListWidgetItem*item=contactlist->currentItem();
    if(!item)return;

    QString name=item->text().split(" ").first();
    if(m_contact.deletecontact(name)){
        delete item;
    }
}

void MainWindow::onFilterGroup(){
    QString group=groupEdit->text();
    contactlist->clear();

    //目标数组
    QList<contact> target=m_contact.getcontactsByGroup(group);
    for(auto &c:target){
        contactlist->addItem(QString("%1        %2").arg(c.getname(),c.getgroup()));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
