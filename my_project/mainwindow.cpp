#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWidget>
#include<QLabel>
#include<QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("小型通讯录");
    resize(500,750);

    // 从文件加载联系人数据
    m_contact.loadFromJson(path);

    //图标
    setWindowIcon(QIcon("://res/picture/icon.jpg"));

    //部件
    QWidget*central=new QWidget(this);
    QVBoxLayout*layout=new QVBoxLayout(central);

    QPushButton*searchbtn=new QPushButton;
    searchEdit=new QLineEdit;


    //搜索菜单
    searchCombo=new QComboBox;
    searchCombo->addItem("姓名");
    searchCombo->addItem("电话");
    searchCombo->addItem("邮箱");
    searchCombo->addItem("组别");
    searchCombo->setFixedSize(70,40);

    //搜索按键
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchbtn->setFixedSize(30,30);
    QIcon searchIcon(":/res/picture/search.jpg");
    searchbtn->setIcon(searchIcon);
    searchbtn->setIconSize(QSize(30,30));

    //添加按键
    QPushButton *addButton=new QPushButton(this);
    addButton->setFixedSize(30,30);
    QIcon addIcon(":/res/picture/add.webp");
    addButton->setIcon(addIcon);
    addButton->setIconSize(QSize(30,30));
    addButton->setFlat(true);
    addButton->setToolTip("添加新联系人");

    searchbtn->setFlat(true);
    searchLayout->addWidget(searchbtn);
    searchLayout->addWidget(searchCombo);
    searchLayout->addWidget(searchEdit);
    searchLayout->addStretch(); // 添加弹性空间
    searchLayout->addWidget(addButton); //按钮加到布局里


    //毛玻璃效果
    QString blurStyle = R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        padding: 6px;
        color: black;
    )";

    searchEdit->setStyleSheet(blurStyle);

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);


    //list
    contactlist=new QListWidget;
    contactlist->setStyleSheet(R"(
        QListWidget::item {
            border-bottom: 1px solid gray;
            padding: 5px;
        }
    )");

    //输入展示
    layout->addLayout(searchLayout);
    layout->addWidget(contactlist);


    setCentralWidget(central);

    //connect
    connect(addButton,&QPushButton::clicked,this,&MainWindow::onAddButtonClicked);
    connect(contactlist, &QListWidget::itemClicked, this, &MainWindow::onContactItemClicked); // 连接联系人列表点击信号
    connect(searchbtn, &QPushButton::clicked, this, &MainWindow::onSearchContact);
    connect(searchEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchContact);


    // 加载联系人到列表
    refreshContactList();

    // 创建信息页面
    infoPage = new InformationPage(this);
        connect(infoPage, &InformationPage::backClicked, this, &MainWindow::onInfoPageBackClicked);
        connect(infoPage, &InformationPage::saveContact, this, &MainWindow::onSaveContact);
        connect(infoPage, &InformationPage::deleteContact, this, &MainWindow::onDeleteContact);
}

// 刷新联系人列表
void MainWindow::refreshContactList() {

    contactlist->clear();

    // 排序
    m_contact.sortContactsByName();

    QFont itemFont("方正舒体", 20);
    
    QList<contact> all = m_contact.getcontacts();
    for(auto &c : all) {
        QString text = QString("%1\n%2").arg(c.getname()).arg(c.getnumber());
        QListWidgetItem* item = new QListWidgetItem(text);

        item->setFont(itemFont);
        item->setSizeHint(QSize(0, 100));

        contactlist->addItem(item);
    }
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


// 保存联系人修改
void MainWindow::onSaveContact(const contact original,const contact modified) {
    // 如果是新联系人（原名为空）
    if(original.getname().isEmpty()) {
        // 检查必填字段
        if(modified.getname().isEmpty() || modified.getnumber().isEmpty()) {
            QMessageBox::warning(this, "保存失败", "姓名和电话不能为空！");
            return;
        }

        // 检查是否重复
        QList<contact> allContacts = m_contact.getcontacts();
        for(const contact &c : allContacts){
            if(c.getname().compare(modified.getname(), Qt::CaseInsensitive) == 0){
                QMessageBox::warning(this, "添加失败", "该联系人已存在！");
                return;  // 重复，直接返回
            }
        }

        // 添加新联系人
        m_contact.addcontact(modified);
    } else {
        // 修改现有联系人
        m_contact.deletecontact(original.getname());
        m_contact.addcontact(modified);
    }

    // 保存到文件
    m_contact.saveToJson(path);
    // 刷新列表
    refreshContactList();
    QMessageBox::information(this, "保存成功", "联系人信息已更新");
}


// 删除联系人
void MainWindow::onDeleteContact(QString name)
{
    if (m_contact.deletecontact(name)) {
        // 保存到文件
        m_contact.saveToJson(path);

        // 刷新列表
        refreshContactList();

        // 如果信息页面显示的是被删除的联系人，关闭它
        infoPage->slideOut();
    } else {
        QMessageBox::warning(this, "删除失败", "未找到该联系人");
    }
}



//搜索
void MainWindow::onSearchContact() {
    QString filter = searchEdit->text();
    QString field = searchCombo->currentText();

    refreshContactListFiltered(filter, field);
}
void MainWindow::refreshContactListFiltered(const QString &filter, const QString &field) {
    contactlist->clear();
    QList<contact> all = m_contact.getcontacts();

    for (const contact &c : all) {
        bool match = false;

        if (filter.isEmpty()) {
            match = true;  // 空过滤显示全部
        } else if (field == "姓名") {
            match = c.getname().contains(filter, Qt::CaseInsensitive);
        } else if (field == "电话") {
            match = c.getnumber().contains(filter, Qt::CaseInsensitive);
        } else if (field == "组别") {
            match = c.getgroup().contains(filter, Qt::CaseInsensitive);
        } else if (field == "邮箱") {
            match = c.getemail().contains(filter, Qt::CaseInsensitive);
        }

        if (match) {
            QFont itemFont("方正舒体", 20);
            QString text = QString("%1").arg(c.getname());
            QListWidgetItem* item = new QListWidgetItem(text);
            item->setFont(itemFont);
            item->setSizeHint(QSize(0, 60));  // 适当调整高度
            contactlist->addItem(item);
        }
    }
}



// 处理联系人列表项点击事件
void MainWindow::onContactItemClicked(QListWidgetItem *item)
{
    QString name = item->text().split('\n').first();
    QList<contact> all = m_contact.getcontacts();
    for (auto &c : all) {
        if (c.getname() == name) {
            infoPage->showContactDetails(c);
            infoPage->slideIn();
            break;
        }
    }
}

// 处理添加按钮点击
void MainWindow::onAddButtonClicked()
{
    // 创建空联系人
    contact newContact;
    infoPage->showContactDetails(newContact);
    infoPage->slideIn();
}

// 处理信息页面返回按钮点击事件
void MainWindow::onInfoPageBackClicked()
{
    infoPage->slideOut();
}

MainWindow::~MainWindow()
{
    delete ui;
}
