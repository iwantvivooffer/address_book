#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AlphabetIndexBar.h"
#include "PinyinHelper.h"

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include<QScrollBar>
#include <QStyle>
#include <QIcon>
#include <QPixmap>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化UI
    setWindowTitle(isChinese ? "小型通讯录" : "Small Address Book");
    resize(500, 750);
    setWindowIcon(QIcon("://res/picture/icon.png"));

    // 从文件加载联系人数据
    m_contact.loadFromJson(path);

    // 中央部件
    QWidget* central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    QVBoxLayout* layout = new QVBoxLayout();

    // 搜索区域
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->setSpacing(10);

    // 搜索按钮
    QPushButton* searchBtn = new QPushButton;
    searchBtn->setFixedSize(30, 30);
    QIcon searchIcon(":/res/picture/search.png");
    searchBtn->setIcon(searchIcon);
    searchBtn->setIconSize(QSize(30, 30));
    searchBtn->setFlat(true);
    // 搜索下拉框
    searchCombo = new QComboBox;
    searchCombo->setFixedSize(100, 40);
    QString comboStyle = R"(
        QComboBox {
            background-color: rgba(255, 255, 255, 120);
            border-radius: 12px;
            border: 1px solid rgba(255, 255, 255, 80);
            padding: 6px;
            color: black;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox::down-arrow {
            image: url(:/res/picture/down-arrow.png);
            width: 20px;
            height: 20px;
        }
        QComboBox QAbstractItemView {
            background-color: rgba(255, 255, 255, 230);
            border-radius: 6px;
            color: black;
            selection-background-color: rgba(180, 220, 255, 150);
        }
    )";
    searchCombo->setStyleSheet(comboStyle);

    // 搜索输入框
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText(isChinese ? "输入搜索内容..." : "Enter search text...");
    // 添加按钮
    addButton = new QPushButton(this);
    addButton->setFixedSize(30, 30);
    QIcon addIcon(":/res/picture/add.png");
    addButton->setIcon(addIcon);
    addButton->setIconSize(QSize(30, 30));
    addButton->setFlat(true);
    // 语言切换按钮
    langButton = new QPushButton(this);
    langButton->setFixedSize(30, 30);
    QIcon langIcon(":/res/picture/language.png");
    langButton->setIcon(langIcon);
    langButton->setIconSize(QSize(30, 30));
    langButton->setFlat(true);

    // 联系人列表
    contactlist = new QListWidget;
    contactlist->setStyleSheet(R"(
        QListWidget {
            background-color: rgba(255, 255, 255,120 );
            border-radius: 12px;
            border: 1px solid rgba(255, 255, 255, 80);
            padding: 6px;
            color: black;
        }
        QListWidget::item {
            background-color: rgba(255, 255, 255, 120);
            border-radius: 12px;
            border: 1px solid rgba(200, 200, 200, 150);
            padding: 10px;
            margin-bottom: 8px;
            color: black;
        }
        QListWidget::item:selected {
            background-color: rgba(180, 220, 255, 150);
            border: 1px solid rgba(150, 200, 255, 120);
        }
    )");
    // 美化滚动条样式（适用于联系人列表）
    QString scrollbarStyle = R"(
        QScrollBar:vertical {
            background: transparent;
            width: 10px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: rgba(150, 150, 150, 100);  /* 半透明灰色 */
            min-height: 20px;
            border-radius: 5px;
        }

        QScrollBar::handle:vertical:hover {
            background: rgba(100, 100, 100, 160);  /* 鼠标悬停更深 */
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
            background: none;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )";

    // 设置到联系人列表的滚动条上
    contactlist->verticalScrollBar()->setStyleSheet(scrollbarStyle);


    contactlist->setSpacing(8);//设置间距

    // 光暗切换按钮
    modeToggleButton = new QPushButton(this);
    modeToggleButton->setFixedSize(30, 30);
    QIcon modeIcon(":/res/picture/光暗转换.png");
    modeToggleButton->setIcon(modeIcon);
    modeToggleButton->setIconSize(QSize(30, 30));
    modeToggleButton->setFlat(true);
    modeToggleButton->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none;
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0.05);  /* 鼠标悬停轻微高亮 */
            border-radius: 6px;
        }
    )");



    // 构建搜索布局
    searchLayout->addWidget(searchBtn);
    searchLayout->addWidget(searchCombo);
    searchLayout->addWidget(searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(modeToggleButton);
    searchLayout->addWidget(langButton);
    searchLayout->addWidget(addButton);

    // 创建索引提示标签
        indexPopup = new QLabel(this);
        indexPopup->setAlignment(Qt::AlignCenter);
        indexPopup->setFixedSize(60, 60);
        indexPopup->setStyleSheet(R"(
            background-color: rgba(0,0,0,0.7);
            color: white;
            font-size: 24px;
            font-weight: bold;
            border-radius: 10px;
        )");
        indexPopup->hide(); // 初始隐藏
    
    // 主布局
    layout->setContentsMargins(20, 20, 20, 20);//设置边距
    layout->setSpacing(15);
    layout->addLayout(searchLayout);
    layout->addWidget(contactlist);
    indexBar = new AlphabetIndexBar(this);
    mainLayout->addWidget(indexBar);
    mainLayout->addLayout(layout);
    setCentralWidget(central);

    // 毛玻璃效果
    QString blurStyle = R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        padding: 6px;
        color: black;
    )";
    searchEdit->setStyleSheet(blurStyle);


    // 初始化UI语言
    updateUILanguage();



    // 连接信号槽
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(contactlist, &QListWidget::itemClicked, this, &MainWindow::onContactItemClicked);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchContact);
    connect(searchEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchContact);
    connect(langButton, &QPushButton::clicked, this, &MainWindow::toggleLanguage);
    connect(modeToggleButton,&QPushButton::clicked,this,&MainWindow::toggleDarkMode);

    connect(indexBar, &AlphabetIndexBar::letterClicked, this, [=](QChar letter) {
        // 高亮字母
        indexBar->highlightLetter(letter);

        QList<contact> all = m_contact.getcontacts();
        bool found = false;
        int targetIndex = -1;

        // 查找匹配的联系人
        for (int i = 0; i < all.size(); ++i) {
            QChar ch = PinyinHelper::getInitial(all[i].getname()).toUpper();

            // 处理"#"组
            if (letter == '#') {
                if (!ch.isLetter()) {
                    targetIndex = i;
                    found = true;
                    break;
                }
            }
            // 处理字母组 - 修复：直接比较字符
            else if (ch == letter) {
                targetIndex = i;
                found = true;
                break;
            }
        }

        // 如果没有找到匹配项，找下一个字母
        if (!found && letter != '#') {
            QList<QChar> indexLetters = indexBar->getIndexLetters();
            int letterIndex = indexLetters.indexOf(letter);
            if (letterIndex >= 0 && letterIndex < indexLetters.size() - 1) {
                for (int i = letterIndex + 1; i < indexLetters.size(); i++) {
                    QChar nextLetter = indexLetters[i];
                    for (int j = 0; j < all.size(); j++) {
                        QChar ch = PinyinHelper::getInitial(all[j].getname()).toUpper();
                        if (ch == nextLetter) {
                            targetIndex = j;
                            letter = nextLetter; // 更新显示的字母
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
            }
        }

        if (targetIndex >= 0) {
            // 获取目标联系人对应的首字母
            QChar currentInitial = PinyinHelper::getInitial(all[targetIndex].getname()).toUpper();
            if (!currentInitial.isLetter()) {
                currentInitial = '#';
            }

            // 遍历 QListWidget，找到匹配的 section 分组标题项
            for (int i = 0; i < contactlist->count(); i++) {
                QListWidgetItem* item = contactlist->item(i);
                if (item->data(Qt::UserRole).toString() == "section") {
                    QString sectionText = item->text().trimmed();
                    if (sectionText.startsWith(currentInitial)) {
                        contactlist->setCurrentItem(item);
                        contactlist->scrollToItem(item, QAbstractItemView::PositionAtTop);

                        // 显示提示框
                        indexPopup->setText(QString(currentInitial));
                        indexPopup->move(width() - 100, 50);
                        indexPopup->show();
                        indexPopup->raise();

                        QTimer::singleShot(2000, this, [this]() {
                            indexPopup->hide();
                        });
                        break;
                    }
                }
            }
        }

    });
    
    // 加载联系人到列表
    refreshContactList();

    // 创建信息页面
    infoPage = new InformationPage(this);
    connect(infoPage, &InformationPage::backClicked, this, &MainWindow::onInfoPageBackClicked);
    connect(infoPage, &InformationPage::saveContact, this, &MainWindow::onSaveContact);
    connect(infoPage, &InformationPage::deleteContact, this, &MainWindow::onDeleteContact);
    // 应用初始样式（亮色模式）
    applyLightMode();

}

void MainWindow::refreshContactList() {
    contactlist->clear();
    m_contact.sortContactsByName();

    QFont itemFont("方正舒体", 20);
    QList<contact> all = m_contact.getcontacts();
     QChar lastInitial = '\0';
    
    for(auto &c : all) {
         QString name = c.getname().trimmed();
        if (name.isEmpty()) continue;

        // 获取拼音首字母
        QChar currentInitial = PinyinHelper::getInitial(name).toUpper();

        // 非字母开头的归为"#"组
        if (!currentInitial.isLetter()) {
            currentInitial = '#';
        }

        // 添加分组标题
        if (currentInitial != lastInitial) {
            lastInitial = currentInitial;

            QString sectionTitle;
            if (currentInitial == '#') {
                sectionTitle = "# 其他";
            } else {
                sectionTitle = currentInitial;
            }

            QListWidgetItem* sectionItem = new QListWidgetItem(sectionTitle);
            sectionItem->setFont(sectionFont);
            sectionItem->setBackground(QColor(200, 200, 200, 150));
            sectionItem->setFlags(Qt::NoItemFlags);
            sectionItem->setData(Qt::UserRole, "section"); // 标识为分组
            contactlist->addItem(sectionItem);
        }
        
        //用\n来实现换行显示
        QString text = isChinese ? QString("姓名：%1\n电话：%2").arg(c.getname()).arg(c.getnumber())
                                : QString("Name: %1\nPhone: %2").arg(c.getname()).arg(c.getnumber());
        QListWidgetItem* item = new QListWidgetItem(text);
        item->setFont(itemFont);
        //设置显示栏的高度保证两行显示
        int lineHeight = QFontMetrics(QFont("方正舒体", 20)).lineSpacing();
        item->setSizeHint(QSize(0, lineHeight * 2 + 40));
        contactlist->addItem(item);
    }
}

void MainWindow::refreshContactListFiltered(const QString &filter, const QString &field) {
    contactlist->clear();
    QList<contact> all = m_contact.getcontacts();
     QChar lastInitial = '\0';
    
    for (const contact &c : all) {
        bool match = false;
        QString name = c.getname().trimmed();
        
        if (filter.isEmpty()) {
            match = true;
        } else if (field == "姓名"||field== "Name") {
            match = c.getname().contains(filter, Qt::CaseInsensitive);
        } else if (field == "电话" ||field== "Phone") {
            match = c.getnumber().contains(filter, Qt::CaseInsensitive);
        } else if (field == "组别" ||field== "Group") {
            match = c.getgroup().contains(filter, Qt::CaseInsensitive);
        } else if (field == "邮箱" ||field=="Email") {
            match = c.getemail().contains(filter, Qt::CaseInsensitive);
        }

        if (match) {
            // 获取拼音首字母
            QChar currentInitial = PinyinHelper::getInitial(name).toUpper();
            if (!currentInitial.isLetter()) {
                currentInitial = '#';
            }

            // 添加分组标题
            if (currentInitial != lastInitial) {
                lastInitial = currentInitial;

                QString sectionTitle;
                if (currentInitial == '#') {
                    sectionTitle = "# 其他";
                } else {
                    sectionTitle = currentInitial;
                }

                QListWidgetItem* sectionItem = new QListWidgetItem(sectionTitle);
                sectionItem->setFont(QFont("Microsoft YaHei", 10, QFont::Bold));
                sectionItem->setBackground(QColor(200, 200, 200, 150));
                sectionItem->setFlags(Qt::NoItemFlags);
                contactlist->addItem(sectionItem);
            }
            //添加联系人项
            QFont itemFont("方正舒体", 20);
            QString text = isChinese ? QString("姓名：%1\n电话：%2").arg(c.getname()).arg(c.getnumber())
                                    : QString("Name: %1\nPhone: %2").arg(c.getname()).arg(c.getnumber());
            QListWidgetItem* item = new QListWidgetItem(text);
            item->setFont(itemFont);
            int lineHeight = QFontMetrics(QFont("方正舒体", 20)).lineSpacing();
            item->setSizeHint(QSize(0, lineHeight * 2 + 40));
            contactlist->addItem(item);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path=QString(":/res/picture/bk3.jpg");
    QPixmap bg(path);
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg);//背景
    }
}

void MainWindow::onSaveContact(const contact original, const contact modified) {
    if(original.getname().isEmpty()) {
        if(modified.getname().isEmpty() || modified.getnumber().isEmpty()) {
            QMessageBox::warning(this,
                               isChinese ? "保存失败" : "Save Failed",
                               isChinese ? "姓名和电话不能为空！" : "Name and phone cannot be empty!");
            return;
        }

        QList<contact> allContacts = m_contact.getcontacts();
        for(const contact &c : allContacts){
            if(c.getname().compare(modified.getname(), Qt::CaseInsensitive) == 0){
                QMessageBox::warning(this,
                                   isChinese ? "添加失败" : "Add Failed",
                                   isChinese ? "该联系人已存在！" : "Contact already exists!");
                return;
            }
        }

        m_contact.addcontact(modified);
    } else {
        //修改
        m_contact.deletecontact(original.getname());
        m_contact.addcontact(modified);
    }

    m_contact.saveToJson(path);
    refreshContactList();
    QMessageBox::information(this,
                            isChinese ? "保存成功" : "Save Success",
                            isChinese ? "联系人信息已更新" : "Contact information updated");
}

void MainWindow::onDeleteContact(QString name)
{
    if (m_contact.deletecontact(name)) {
        m_contact.saveToJson(path);
        refreshContactList();
        infoPage->slideOut();
    } else {
        QMessageBox::warning(this,
                           isChinese ? "删除失败" : "Delete Failed",
                           isChinese ? "未找到该联系人" : "Contact not found");
    }
}

void MainWindow::onSearchContact() {
    QString filter = searchEdit->text();
    QString field = searchCombo->currentText();
    refreshContactListFiltered(filter, field);//调用刷新界面的函数来实现“搜索”
}

void MainWindow::onContactItemClicked(QListWidgetItem *item)
{
    QString clickedItemText = item->text().split('\n').first().trimmed();
    QString clickedName;

    if (isChinese) {
        if (clickedItemText.startsWith("姓名：")) {
            clickedName = clickedItemText.mid(QString("姓名：").length());
        } else {
            clickedName = clickedItemText;
        }
    } else {
        if (clickedItemText.startsWith("Name: ")) {
            clickedName = clickedItemText.mid(QString("Name: ").length());
        } else {
            clickedName = clickedItemText;
        }
    }

    clickedName = clickedName.trimmed();

    QList<contact> all = m_contact.getcontacts();
    for (const contact &c : all) {
        if (c.getname().trimmed() == clickedName) {
            infoPage->setLanguageState(isChinese);
            infoPage->showContactDetails(c);
            infoPage->slideIn();
            return;
        }
    }

    QMessageBox::warning(this,
                       isChinese ? "查找失败" : "Search Failed",
                       isChinese ? "未找到该联系人信息！请检查姓名是否完全一致。"
                                : "Contact not found! Please check if the name is exactly the same.");
}

void MainWindow::onAddButtonClicked()
{
    contact newContact;
    infoPage->setLanguageState(isChinese);
    infoPage->showContactDetails(newContact);
    infoPage->slideIn();
}

void MainWindow::onInfoPageBackClicked()
{
    infoPage->slideOut();
}

// 光暗模式切换
void MainWindow::toggleDarkMode()
{
    isDarkMode = !isDarkMode;

    if (isDarkMode) {
        applyDarkMode();
    } else {
        applyLightMode();
    }

    // 刷新界面
    update();
}

// 应用暗色模式
void MainWindow::applyDarkMode()
{
    // 设置主窗口样式
    setStyleSheet(R"(
        QWidget {
            background-color: #2D2D30;
            color: #FFFFFF;
        }
        QListWidget {
            background-color: #252526;
            color: #FFFFFF;
            border: 1px solid #3F3F46;
        }
        QListWidget::item {
            color: #FFFFFF;
            border-bottom: 1px solid #3F3F46;
        }
        QListWidget::item:selected {
            background-color: #094771;
        }
        QLineEdit {
            background-color: #3C3C3C;
            color: #FFFFFF;
            border: 1px solid #3F3F46;
            border-radius: 6px;
        }
        QComboBox {
            background-color: #3C3C3C;
            color: #FFFFFF;
            border: 1px solid #3F3F46;
            border-radius: 6px;
        }
        QComboBox QAbstractItemView {
            background-color: #3C3C3C;
            color: #FFFFFF;
            border: 1px solid #3F3F46;
        }
        QPushButton {
            background-color: #3C3C3C;
            color: #FFFFFF;
            border: none;
            border-radius: 6px;
        }
    )");

    // 更新信息页面样式
    if (infoPage) {
        infoPage->setDarkMode(true);
    }
}

// 应用亮色模式
void MainWindow::applyLightMode()
{
    // 恢复默认样式
    setStyleSheet("");

    // 重新应用搜索框样式
    QString blurStyle = R"(
        background-color: rgba(255, 255, 255, 120);
        border-radius: 12px;
        border: 1px solid rgba(255, 255, 255, 80);
        padding: 6px;
        color: black;
    )";
    searchEdit->setStyleSheet(blurStyle);

    // 更新信息页面样式
    if (infoPage) {
        infoPage->setDarkMode(false);
    }
}

void MainWindow::toggleLanguage()
{
    isChinese = !isChinese;
    updateUILanguage();
}

void MainWindow::updateUILanguage()
{
    setWindowTitle(isChinese ? "小型通讯录" : "Small Address Book");
    addButton->setToolTip(isChinese ? "添加新联系人" : "Add new contact");
    searchEdit->setPlaceholderText(isChinese ? "输入搜索内容..." : "Enter search text...");

    // 更新搜索下拉框
    searchCombo->clear();
    if(isChinese) {
        searchCombo->addItem("姓名");
        searchCombo->addItem("电话");
        searchCombo->addItem("邮箱");
        searchCombo->addItem("组别");
    } else {
        searchCombo->addItem("Name");
        searchCombo->addItem("Phone");
        searchCombo->addItem("Email");
        searchCombo->addItem("Group");
    }

    langButton->setToolTip(isChinese ? "切换语言" : "Switch language");

    // 刷新列表显示
    refreshContactList();
}

MainWindow::~MainWindow()
{
    delete ui;
}
