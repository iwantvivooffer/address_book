#include "contactdialog.h"
#include <QPainter>
#include <QPixmap>

ContactDialog::ContactDialog(const contact &contact, QWidget *parent)
    : QDialog(parent), m_contact(contact)
{
    // 设置对话框标题
        setWindowTitle("详细信息");

        // 设置对话框大小（宽度:400 高度:300）
        resize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *nameLabel = new QLabel("姓名: " + m_contact.getname());
    QLabel *numberLabel = new QLabel("电话: " + m_contact.getnumber());
    QLabel *groupLabel = new QLabel("组别: " + m_contact.getgroup());
    QLabel *emailLabel = new QLabel("邮箱: " + m_contact.getemile());

    // 设置标签的样式，增加间距和字体大小
        nameLabel->setStyleSheet("font-size: 14px; margin: 5px;");
        numberLabel->setStyleSheet("font-size: 14px; margin: 5px;");
        groupLabel->setStyleSheet("font-size: 14px; margin: 5px;");
        emailLabel->setStyleSheet("font-size: 14px; margin: 5px;");

    layout->addWidget(nameLabel);
    layout->addWidget(numberLabel);
    layout->addWidget(groupLabel);
    layout->addWidget(emailLabel);

    setLayout(layout);
}

ContactDialog::~ContactDialog()
{
}

void ContactDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bg(":/res/picture/对话框背景图片.jpg");
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg); // 自动缩放图片填满整个窗口
    }
}
