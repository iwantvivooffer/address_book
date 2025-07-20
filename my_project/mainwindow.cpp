#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWidget>
#include<QLabel>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(500,950);
    
    // 设置窗口图标
    setWindowIcon(QIcon("://res/picture/icon.jpg"));
    
    // 创建中心部件和布局
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    
    // 输入栏
    nameEdit = new QLineEdit;
    numberEdit = new QLineEdit;
    groupEdit = new QLineEdit;
    emileEdit = new QLineEdit;
    
    // 按钮
    QPushButton* addbtn = new QPushButton("添加联系人");
    QPushButton* delbth = new QPushButton("删除联系人");
    QPushButton* filterbtn = new QPushButton("按组查看");
    
    // 毛玻璃效果样式
    QString blurStyle = R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        padding: 6px;
        color: black;
    )";
    
    // 应用样式
    nameEdit->setStyleSheet(blurStyle);
    numberEdit->setStyleSheet(blurStyle);
    groupEdit->setStyleSheet(blurStyle);
    emileEdit->setStyleSheet(blurStyle);
    addbtn->setStyleSheet(blurStyle);
    delbth->setStyleSheet(blurStyle);
    filterbtn->setStyleSheet(blurStyle);
    
    // 设置布局边距和间距
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);
    
    // 联系人列表
    contactlist = new QListWidget;
    contactlist->setStyleSheet(R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        color: black;
    )");
    
    // 添加控件到布局
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
    
    // 连接信号和槽
    connect(addbtn, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(delbth, &QPushButton::clicked, this, &MainWindow::onDeleteContact);
    connect(filterbtn, &QPushButton::clicked, this, &MainWindow::onFilterGroup);
    
    // 加载联系人到列表
    refreshContactList();
}

// 刷新联系人列表
void MainWindow::refreshContactList() {
    contactlist->clear();
    QList<contact> all = m_contact.getcontacts();
    for(auto &c : all) {
        contactlist->addItem(QString("%1                         %2").arg(c.getname(), c.getgroup()));
    }
}

// 背景绘制
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bg(":/res/picture/bk3.webp");
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg); // 自动缩放图片填满整个窗口
    }
}

// 添加联系人
void MainWindow::onAddContact() {
    QString name = nameEdit->text().trimmed();
    QString number = numberEdit->text().trimmed();
    QString group = groupEdit->text().trimmed();
    QString emile = emileEdit->text().trimmed();
    
    if(name.isEmpty() || number.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名和电话不能为空");
        return;
    }
    
    contact temp(name, number, group, emile);
    m_contact.addcontact(temp);
    refreshContactList();  // 刷新列表
    
    // 清空输入框（保留组别）
    nameEdit->clear();
    numberEdit->clear();
    emileEdit->clear();
}

// 删除联系人
void MainWindow::onDeleteContact() {
    QListWidgetItem* item = contactlist->currentItem();
    if(!item) {
        QMessageBox::warning(this, "删除错误", "请先选择一个联系人");
        return;
    }
    
    QString name = item->text().split(" ").first();
    if(m_contact.deletecontact(name)) {
        delete item;
    }
}

// 按组过滤
void MainWindow::onFilterGroup() {
    QString group = groupEdit->text().trimmed();
    if(group.isEmpty()) {
        refreshContactList();  // 如果组名为空，显示所有联系人
        return;
    }
    
    contactlist->clear();
    QList<contact> target = m_contact.getcontactsByGroup(group);
    for(auto &c : target) {
        contactlist->addItem(QString("%1        %2").arg(c.getname(), c.getgroup()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
