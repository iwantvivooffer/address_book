#include "informationpage.h"
#include <QPainter>
#include <QPixmap>
#include <QShowEvent>
#include <QVBoxLayout>
#include <QDebug>
#include <QHBoxLayout>

InformationPage::InformationPage(QWidget *parent) : QWidget(parent)
{
    // 设置与主窗口相同尺寸
    setFixedSize(parent->size());
    // 初始位置在右侧（不可见）
    move(parentWidget()->width(), 0);

    // 背景层
    QWidget *backgroundLayer = new QWidget(this);
    backgroundLayer->setGeometry(0, 0, width(), height());
    backgroundLayer->setStyleSheet(R"(
        background-color: #f5deb3;
    )");

    // 内容框
    int margin = 20;
    QWidget *contentFrame = new QWidget(backgroundLayer);
    contentFrame->setGeometry(
        margin, margin,
        width() - 2*margin,
        height() - 2*margin
    );
    contentFrame->setStyleSheet(R"(
        background-color: white;
        border: 1px solid #d0b090;
        border-radius: 8px;
        box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    )");

    // 内容布局
    QVBoxLayout *layout = new QVBoxLayout(contentFrame);
    layout->setContentsMargins(40, 80, 40, 80);
    layout->setSpacing(30);

    // 编辑框样式
    QString editStyle = R"(
        background-color: #f8f8f8;
        border: 1px solid #e0e0e0;
        border-radius: 6px;
        padding: 8px 12px;
        color: #333;
        min-height: 30px;
        font-size: 16px;
    )";

    QFont editFont("Microsoft YaHei", 10, QFont::Normal);

    // 姓名编辑框
    QLabel *nameTitle = new QLabel("姓名：", contentFrame);
    nameTitle->setFont(editFont);
    layout->addWidget(nameTitle);
    nameEdit = new QLineEdit(contentFrame);
    nameEdit->setStyleSheet(editStyle);
    nameEdit->setFont(editFont);
    layout->addWidget(nameEdit);

    // 电话编辑框
    QLabel *numberTitle = new QLabel("电话：", contentFrame);
    numberTitle->setFont(editFont);
    layout->addWidget(numberTitle);
    numberEdit = new QLineEdit(contentFrame);
    numberEdit->setStyleSheet(editStyle);
    numberEdit->setFont(editFont);
    layout->addWidget(numberEdit);

    // 组别编辑框
    QLabel *groupTitle = new QLabel("组别：", contentFrame);
    groupTitle->setFont(editFont);
    layout->addWidget(groupTitle);
    groupEdit = new QLineEdit(contentFrame);
    groupEdit->setStyleSheet(editStyle);
    groupEdit->setFont(editFont);
    layout->addWidget(groupEdit);

    // 邮箱编辑框
    QLabel *emailTitle = new QLabel("邮箱：", contentFrame);
    emailTitle->setFont(editFont);
    layout->addWidget(emailTitle);
    emailEdit = new QLineEdit(contentFrame);
    emailEdit->setStyleSheet(editStyle);
    emailEdit->setFont(editFont);
    layout->addWidget(emailEdit);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    
    // 保存按钮
    saveButton = new QPushButton("保存", contentFrame);
    saveButton->setStyleSheet(R"(
        background-color: #4CAF50;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )");
    saveButton->setFixedHeight(40);
    buttonLayout->addWidget(saveButton);
    
    // 删除按钮
    deleteButton = new QPushButton("删除联系人", contentFrame);
    deleteButton->setStyleSheet(R"(
        background-color: #f44336;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )");
    deleteButton->setFixedHeight(40);
    buttonLayout->addWidget(deleteButton);
    
    layout->addLayout(buttonLayout);

    // 返回按钮
    backButton = new QPushButton(backgroundLayer);
    backButton->setStyleSheet(R"(
        background-color: white;
        border-radius: 4px;
        border: 1px solid #d0b090;
    )");
    backButton->setIcon(QIcon(":/res/picture/返回.png"));
    backButton->setIconSize(QSize(30, 30));
    backButton->setFixedSize(50, 50);
    backButton->move(margin, margin);

    // 动画
    animation = new QPropertyAnimation(this, "pos", this);
    animation->setDuration(300);

    // 连接信号
    connect(backButton, &QPushButton::clicked, this, &InformationPage::checkForChanges);
    connect(saveButton, &QPushButton::clicked, this, &InformationPage::onSaveClicked);
    connect(deleteButton, &QPushButton::clicked, this, &InformationPage::onDeleteClicked);
    
    // 监听编辑框变化
    connect(nameEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(numberEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(groupEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(emailEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
}

void InformationPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    int margin = 20;
    backButton->move(margin, margin);
}

void InformationPage::showContactDetails(contact &contact)
{
    originalContact = contact;
    nameEdit->setText(contact.getname());
    numberEdit->setText(contact.getnumber());
    groupEdit->setText(contact.getgroup());
    emailEdit->setText(contact.getemail());
    hasChanges = false;

    // 如果是新联系人，隐藏删除按钮
        if(contact.getname().isEmpty()) {
            deleteButton->hide();
        } else {
            deleteButton->show();
        }
}

void InformationPage::slideIn()
{
    disconnect(animation, &QPropertyAnimation:
