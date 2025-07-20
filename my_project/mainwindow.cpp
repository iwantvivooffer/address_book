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

    //设置图标
    QPixmap namePixmap(":/res/picture/user.jpg");
    QPixmap numberPixmap(":/res/picture/phone.png");
    QPixmap groupPixmap(":/res/picture/common.webp");
    QPixmap emilePixmap(":/res/picture/emile.png");

    // 统一设置每行布局
    auto createInputRow = [](const QPixmap &icon, const QString &labelText, QLineEdit *edit) {
        QLabel *iconLabel = new QLabel;
        iconLabel->setPixmap(icon.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        iconLabel->setFixedSize(24, 24);

        QLabel *textLabel = new QLabel(labelText);
        textLabel->setFixedWidth(50); // 固定宽度使对齐更美观

        QHBoxLayout *row = new QHBoxLayout;
        row->setSpacing(8);
        row->addWidget(iconLabel, 0, Qt::AlignVCenter);
        row->addWidget(textLabel, 0, Qt::AlignVCenter);
        row->addWidget(edit);

        QWidget *rowWidget = new QWidget;
        rowWidget->setLayout(row);
        return rowWidget;
    };
    

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

    // 创建各行
    nameWidget = createInputRow(namePixmap, "姓名：", nameEdit);
    numberWidget = createInputRow(numberPixmap, "电话：", numberEdit);
    groupWidget = createInputRow(groupPixmap, "组别：", groupEdit);
    emileWidget = createInputRow(emilePixmap, "邮箱：", emileEdit);

    
    //输入展示
    layout->addWidget(nameWidget);
    layout->addWidget(numberWidget);
    layout->addWidget(groupWidget);
    layout->addWidget(emileWidget);
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
    contactlist->addItem(QString("%1          %2               %3").arg(name,number,group));

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
        contactlist->addItem(QString("%1       %2      %3").arg(c.getname(),c.getnumber(),c.getgroup()));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
