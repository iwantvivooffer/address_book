#include "informationpage.h"
#include <QPainter>
#include <QPixmap>
#include <QShowEvent>
#include <QVBoxLayout>
#include <QDebug>

InformationPage::InformationPage(QWidget *parent) : QWidget(parent)
{
    // 设置与主窗口相同尺寸
    setFixedSize(parent->size());
    // 初始位置在右侧（不可见）
    move(parentWidget()->width(), 0);

    // -------------------------- 1. 最底层：浅棕色背景（全屏） --------------------------
    // 创建背景层，作为InformationPage的直接子部件
    QWidget *backgroundLayer = new QWidget(this);
    backgroundLayer->setGeometry(0, 0, width(), height());

    // 使用浅棕色背景 (#f5deb3 是一种常见的浅棕色)
    backgroundLayer->setStyleSheet(R"(
        background-color: #f5deb3;
    )");

    // -------------------------- 2. 中间层：白色内容框（带边框效果） --------------------------
    int margin = 20; // 内容框与窗口边缘的距离
    QWidget *contentFrame = new QWidget(backgroundLayer);
    contentFrame->setGeometry(
        margin, margin,
        width() - 2*margin,
        height() - 2*margin
    );
    contentFrame->setStyleSheet(R"(
        background-color: white;
        border: 1px solid #d0b090; /* 棕色边框 */
        border-radius: 8px;
        box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加轻微阴影增强立体感 */
    )");

    // -------------------------- 3. 内容区布局（放在白色内容框内） --------------------------
    QVBoxLayout *layout = new QVBoxLayout(contentFrame);
    layout->setContentsMargins(40, 80, 40, 80);
    layout->setSpacing(30);

    // 信息标签样式
    QString labelStyle = R"(
        background-color: #f8f8f8; /* 浅灰色背景 */
        border: 1px solid #e0e0e0;
        border-radius: 6px;
        padding: 8px 12px;
        color: #333; /* 深灰色文字 */
        min-height: 30px;
        font-size: 16px;
    )";

    // 创建信息标签
    QFont labelFont("Microsoft YaHei", 10, QFont::Normal);

    // 姓名
    QLabel *nameTitle = new QLabel("姓名：", contentFrame);
    nameTitle->setFont(labelFont);
    layout->addWidget(nameTitle);
    nameLabel = new QLabel(contentFrame);
    nameLabel->setStyleSheet(labelStyle);
    nameLabel->setFont(labelFont);
    layout->addWidget(nameLabel);

    // 电话
    QLabel *numberTitle = new QLabel("电话：", contentFrame);
    numberTitle->setFont(labelFont);
    layout->addWidget(numberTitle);
    numberLabel = new QLabel(contentFrame);
    numberLabel->setStyleSheet(labelStyle);
    numberLabel->setFont(labelFont);
    layout->addWidget(numberLabel);

    // 组别
    QLabel *groupTitle = new QLabel("组别：", contentFrame);
    groupTitle->setFont(labelFont);
    layout->addWidget(groupTitle);
    groupLabel = new QLabel(contentFrame);
    groupLabel->setStyleSheet(labelStyle);
    groupLabel->setFont(labelFont);
    layout->addWidget(groupLabel);

    // 邮箱
    QLabel *emailTitle = new QLabel("邮箱：", contentFrame);
    emailTitle->setFont(labelFont);
    layout->addWidget(emailTitle);
    emailLabel = new QLabel(contentFrame);
    emailLabel->setStyleSheet(labelStyle);
    emailLabel->setFont(labelFont);
    layout->addWidget(emailLabel);

    // -------------------------- 4. 按钮（放在背景层上） --------------------------
    // 左上角返回按钮
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

    // 右上角更多按钮
    moreButton = new QPushButton(backgroundLayer);
    moreButton->setStyleSheet(R"(
        background-color: white;
        border-radius: 4px;
        border: 1px solid #d0b090;
    )");
    moreButton->setIcon(QIcon(":/res/picture/更多.png"));
    moreButton->setIconSize(QSize(24, 36));
    moreButton->setFixedSize(40, 60);
    moreButton->move(width() - moreButton->width() - margin, margin);

    // -------------------------- 5. 动画设置 --------------------------
    animation = new QPropertyAnimation(this, "pos", this);
    animation->setDuration(300);

    connect(backButton, &QPushButton::clicked, this, &InformationPage::backClicked);
    connect(moreButton, &QPushButton::clicked, this, &InformationPage::moreClicked);
}

void InformationPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    int margin = 20;
    moreButton->move(width() - moreButton->width() - margin, margin);
}

void InformationPage::showContactDetails(contact &contact)
{
    nameLabel->setText(contact.getname());
    numberLabel->setText(contact.getnumber());
    groupLabel->setText(contact.getgroup());
    emailLabel->setText(contact.getemail());
}

void InformationPage::slideIn()
{
    disconnect(animation, &QPropertyAnimation::finished, this, &QWidget::hide);
    animation->stop();
    animation->setStartValue(QPoint(parentWidget()->width(), 0));
    animation->setEndValue(QPoint(0, 0));
    animation->start();
    show();
}

void InformationPage::slideOut()
{
    disconnect(animation, &QPropertyAnimation::finished, this, &QWidget::hide);
    animation->stop();
    animation->setStartValue(QPoint(0, 0));
    animation->setEndValue(QPoint(parentWidget()->width(), 0));
    connect(animation, &QPropertyAnimation::finished, this, [=](){
        hide();
        disconnect(animation, &QPropertyAnimation::finished, this, nullptr);
    }, Qt::UniqueConnection);
    animation->start();
}

InformationPage::~InformationPage()
{
    delete animation;
}
