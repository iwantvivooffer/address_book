#include "informationpage.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QShowEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

InformationPage::InformationPage(QWidget *parent) : QWidget(parent)
{
    // 设置与主窗口相同尺寸
    setFixedSize(parent->size());
    // 初始位置在右侧（不可见）
    move(parentWidget()->width(), 0);

    // 背景层
    QWidget *backgroundLayer = new QWidget(this);
    backgroundLayer->setGeometry(0, 0, width(), height());
    backgroundLayer->setStyleSheet(R"(background-color: #f5deb3;)");//棕色背景

    // 内容框
    int margin = 20;
    QWidget *contentFrame = new QWidget(backgroundLayer);
    contentFrame->setGeometry(margin, margin,width() - 2*margin,height() - 2*margin);
    contentFrame->setStyleSheet(R"(
        background-color: white;
        border: 1px solid #d0b090;
        border-radius: 8px;
         box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    )");

    // 内容布局
    QVBoxLayout *layout = new QVBoxLayout(contentFrame);//详细人页面
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

    // --- 姓名行 ---
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QLabel *nameIcon = new QLabel(contentFrame);
    nameIcon->setPixmap(QPixmap(":/res/picture/user.png").scaled(50, 50, Qt::KeepAspectRatio));//保证等比例
    nameTitle = new QLabel(contentFrame);
    nameEdit = new QLineEdit(contentFrame);
    nameEdit->setStyleSheet(editStyle);
    nameEdit->setFont(editFont);

    nameLayout->addWidget(nameIcon);
    nameLayout->addWidget(nameTitle);
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);

    // --- 电话行 ---
    QHBoxLayout *numberLayout = new QHBoxLayout();
    QLabel *numberIcon = new QLabel(contentFrame);
    numberIcon->setPixmap(QPixmap(":/res/picture/phone.png").scaled(50, 50, Qt::KeepAspectRatio));
    numberTitle = new QLabel(contentFrame);
    numberEdit = new QLineEdit(contentFrame);
    numberEdit->setStyleSheet(editStyle);
    numberEdit->setFont(editFont);

    numberLayout->addWidget(numberIcon);
    numberLayout->addWidget(numberTitle);
    numberLayout->addWidget(numberEdit);
    layout->addLayout(numberLayout);

    // --- 组别行 ---
    QHBoxLayout *groupLayout = new QHBoxLayout();
    QLabel *groupIcon = new QLabel(contentFrame);
    groupIcon->setPixmap(QPixmap(":/res/picture/friend.png").scaled(50, 50, Qt::KeepAspectRatio));
    groupTitle = new QLabel("组别：", contentFrame);
    groupTitle = new QLabel(contentFrame);
    groupEdit = new QLineEdit(contentFrame);
    groupEdit->setStyleSheet(editStyle);
    groupEdit->setFont(editFont);

    groupLayout->addWidget(groupIcon);
    groupLayout->addWidget(groupTitle);
    groupLayout->addWidget(groupEdit);
    layout->addLayout(groupLayout);

    // --- 邮箱行 ---
    QHBoxLayout *emailLayout = new QHBoxLayout();
    QLabel *emailIcon = new QLabel(contentFrame);
    emailIcon->setPixmap(QPixmap(":/res/picture/emile.png").scaled(50, 50, Qt::KeepAspectRatio));
    emailTitle = new QLabel(contentFrame);
    emailEdit = new QLineEdit(contentFrame);
    emailEdit->setStyleSheet(editStyle);
    emailEdit->setFont(editFont);

    emailLayout->addWidget(emailIcon);
    emailLayout->addWidget(emailTitle);
    emailLayout->addWidget(emailEdit);
    layout->addLayout(emailLayout);


    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    // 保存按钮
    saveButton = new QPushButton("保存", contentFrame);
    saveButton->setStyleSheet(R"(
        background-color: #4CAF50;//背景为绿色
        color: white;//字体为白色
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )");
    saveButton->setFixedHeight(40);
    buttonLayout->addWidget(saveButton);

    // 删除按钮
    deleteButton = new QPushButton(contentFrame);
    deleteButton->setStyleSheet(R"(
        background-color: #f44336;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )");
    deleteButton->setFixedHeight(40);
    buttonLayout->addWidget(deleteButton);

    //最后将两个按键放入界面
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
    backButton->move(margin, margin);//移动至左上角

    // 动画
    animation = new QPropertyAnimation(this, "pos", this);//表示动画效果作用于这个窗口
    animation->setDuration(300);//300毫秒

    // 连接信号
    connect(backButton, &QPushButton::clicked, this, &InformationPage::checkForChanges);
    connect(saveButton, &QPushButton::clicked, this, &InformationPage::onSaveClicked);
    connect(deleteButton, &QPushButton::clicked, this, &InformationPage::onDeleteClicked);
    connect(nameEdit, &QLineEdit::returnPressed, this, &InformationPage::onSaveClicked);
    connect(numberEdit, &QLineEdit::returnPressed, this, &InformationPage::onSaveClicked);
    connect(groupEdit, &QLineEdit::returnPressed, this, &InformationPage::onSaveClicked);
    connect(emailEdit, &QLineEdit::returnPressed, this, &InformationPage::onSaveClicked);

    // 监听编辑框变化
    connect(nameEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(numberEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(groupEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });
    connect(emailEdit, &QLineEdit::textChanged, this, [this](){ hasChanges = true; });

    // 初始化UI语言
    updateUILanguage();
     isChinese = true;
}

void InformationPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    int margin = 20;
    backButton->move(margin, margin);
}

void InformationPage::showContactDetails(const contact &contact)
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
    disconnect(animation, &QPropertyAnimation::finished, this, &QWidget::hide);
    animation->stop();//如果动画正在进行，停止，避免多次点击发生冲突
    animation->setStartValue(QPoint(parentWidget()->width(), 0));//动画开始坐标
    animation->setEndValue(QPoint(0, 0));//动画结束坐标
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

void InformationPage::onSaveClicked()
{
    QString name = nameEdit->text().trimmed();//获取输入栏的内容，并且去除前后的空格
    QString number = numberEdit->text().trimmed();

    if (name.isEmpty() || number.isEmpty()) {
        QMessageBox::warning(this,
                        isChinese ? "保存失败" : "Save Failed",
                        isChinese ? "姓名和电话不能为空！" : "Name and phone cannot be empty!");
        return;
    }

    //创建预备保存对象
    contact modifiedContact(
        nameEdit->text().trimmed(),
        numberEdit->text().trimmed(),
        groupEdit->text().trimmed(),
        emailEdit->text().trimmed()
    );

    emit saveContact(originalContact, modifiedContact);//发送信息
    hasChanges = false;

    originalContact = contact(); // 清空原始联系人
    nameEdit->clear();
    numberEdit->clear();
     groupEdit->clear();
    emailEdit->clear();
    deleteButton->hide(); // 隐藏删除按钮（因为是新建）
    slideOut();
}

void InformationPage::onDeleteClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                            isChinese ? "删除联系人" : "Delete Contact",
                            isChinese ? "确定要删除这个联系人吗？" : "Are you sure to delete this contact?",
                            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit deleteContact(originalContact.getname());
        slideOut();
    }
}

void InformationPage::checkForChanges()
{
    if (hasChanges) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,
                                    isChinese ? "保存修改" : "Save Changes",
                                    isChinese ? "内容已修改，是否保存？" : "Content has been modified. Save changes?",
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (reply == QMessageBox::Save) {
            onSaveClicked();
            slideOut();
        } else if (reply == QMessageBox::Discard) {
            // 如果是新联系人且选择放弃，不创建联系人
            slideOut();
        }
        // 如果选择Cancel，则不做任何操作
    } else {
        slideOut();
    }
}


// 设置暗色模式
void InformationPage::setDarkMode(bool darkMode)
{
    isDarkMode = darkMode;

    QString bgColor, frameColor, editStyle, saveButtonStyle, deleteButtonStyle, backButtonStyle;

    if (darkMode) {
        bgColor = "#2D2D30";  // 与主窗口暗色背景一致
        frameColor = "#252526";  // 与主窗口内容区暗色背景一致
        editStyle = R"(
            background-color: #3C3C3C;
            border: 1px solid #3F3F46;
            color: #FFFFFF;
            border-radius: 6px;
            padding: 8px 12px;
            min-height: 30px;
            font-size: 16px;
        )";
    saveButtonStyle = R"(
        background-color: #4CAF50;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )";
    deleteButtonStyle = R"(
        background-color: #f44336;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )";
    backButtonStyle = R"(
        background-color: #3C3C3C;
        border-radius: 4px;
        border: 1px solid #3F3F46;
    )";
} else {
    bgColor = "#f5deb3";
    frameColor = "white";
    editStyle = R"(
        background-color: #f8f8f8;
        border: 1px solid #e0e0e0;
        color: #333;
        border-radius: 6px;
        padding: 8px 12px;
        min-height: 30px;
        font-size: 16px;
    )";
    saveButtonStyle = R"(
        background-color: #4CAF50;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )";
    deleteButtonStyle = R"(
        background-color: #f44336;
        color: white;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 16px;
    )";
    backButtonStyle = R"(
        background-color: white;
        border-radius: 4px;
        border: 1px solid #d0b090;
    )";
}
    // 背景层
        QWidget* backgroundLayer = this->findChild<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
        if (backgroundLayer) {
            backgroundLayer->setStyleSheet(QString("background-color: %1;").arg(bgColor));
        }

        // 内容框
        QWidget* contentFrame = backgroundLayer ? backgroundLayer->findChild<QWidget*>(QString(), Qt::FindDirectChildrenOnly) : nullptr;
        if (contentFrame) {
            contentFrame->setStyleSheet(QString(
                "background-color: %1;"
                "border: 1px solid %2;"
                "border-radius: 8px;"
                "box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);"
            ).arg(frameColor).arg(darkMode ? "#3F3F46" : "#d0b090"));
        }

        // 应用其他样式
        nameEdit->setStyleSheet(editStyle);
        numberEdit->setStyleSheet(editStyle);
        groupEdit->setStyleSheet(editStyle);
        emailEdit->setStyleSheet(editStyle);

        saveButton->setStyleSheet(saveButtonStyle);
        deleteButton->setStyleSheet(deleteButtonStyle);
        backButton->setStyleSheet(backButtonStyle);
    }

void InformationPage::updateUILanguage()
{
    if(isChinese) {
        nameTitle->setText("姓名：");
        numberTitle->setText("电话：");
        groupTitle->setText("组别：");
        emailTitle->setText("邮箱：");
        saveButton->setText("保存");
        deleteButton->setText("删除联系人");
    } else {
        nameTitle->setText("Name:");
        numberTitle->setText("Phone:");
        groupTitle->setText("Group:");
        emailTitle->setText("Email:");
        saveButton->setText("Save");
        deleteButton->setText("Delete Contact");
    }
}

void InformationPage::setLanguageState(bool chinese)
{
    isChinese = chinese;
    updateUILanguage();
}


InformationPage::~InformationPage()
{
    delete animation;
}
