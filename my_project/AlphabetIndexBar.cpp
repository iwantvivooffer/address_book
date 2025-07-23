#include "AlphabetIndexBar.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

AlphabetIndexBar::AlphabetIndexBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(36);//设置索引条宽度
    setupLayout();
}

//高亮显示指定字母的按钮
void AlphabetIndexBar::highlightLetter(QChar letter)
{
    // 清除之前的高亮
    if (currentHighlighted != QChar() && letterButtons.contains(currentHighlighted)) {
        letterButtons[currentHighlighted]->setStyleSheet(R"(
            QPushButton {
                background-color: transparent; // 默认背景透明
                border: none;                  // 无边框
                font-size: 18px;               // 字体大小
                font-weight: bold;             // 字体加粗
                color: black;                  // 字体颜色黑色
            }
            QPushButton:hover {//鼠标悬停时
                background-color: rgba(0,0,0,0.1);
                border-radius: 18px;
            }
            QPushButton:pressed {//鼠标按下时
                background-color: rgba(0,0,0,0.3);
                border-radius: 18px;
            }
        )");
    }

    // 设置新的高亮（点击时）
    if (letterButtons.contains(letter)) {
        currentHighlighted = letter;
        letterButtons[letter]->setStyleSheet(R"(
            QPushButton {
                background-color: rgba(0,0,0,0.3); //点击时深灰色背景
                border: none;
                font-size: 18px;
                font-weight: bold;
                color: black;
                border-radius: 18px;
            }
        )");

        // 2秒后自动恢复
        QTimer::singleShot(1000, this, [this, letter]() {//一个lambda函数，当定时器超时时执行
            if (currentHighlighted == letter) {
                letterButtons[letter]->setStyleSheet(R"(
                    QPushButton {
                        background-color: transparent;
                        border: none;
                        font-size: 18px;
                        font-weight: bold;
                        color: black;
                    }
                    QPushButton:hover {
                        background-color: rgba(0,0,0,0.1);
                        border-radius: 18px;
                    }
                    QPushButton:pressed {
                        background-color: rgba(0,0,0,0.3);
                        border-radius: 18px;
                    }
                )");
                currentHighlighted = QChar();//清除当前高亮字母
            }
        });
    }
}

//垂直布局
void AlphabetIndexBar::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);//创建一个垂直布局的管理器
    layout->setSpacing(1);//设置间隔
    layout->setContentsMargins(5, 10, 5, 10);//设置内边距
    layout->setAlignment(Qt::AlignCenter);

    // 添加顶部弹性空间
    layout->addStretch(1);

    for (QChar ch : indexLetters) {
        QPushButton *btn = new QPushButton(QString(ch), this);
        btn->setFixedSize(36, 36); // 进一步增大尺寸
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: transparent;
                border: none;
                font-size: 18px;
                font-weight: bold;
                color: black;
            }
            QPushButton:hover {
                background-color: rgba(0,0,0,0.1); /* 悬停时轻微灰色 */
                border-radius: 18px;
            }
            QPushButton:pressed {
                background-color: rgba(0,0,0,0.3); /* 点击时深灰色 */
                border-radius: 18px;
            }
        )");

        //连接按钮和槽函数，发送信息
        connect(btn, &QPushButton::clicked, this, [this, ch]() {
            emit letterClicked(ch);
        });
        layout->addWidget(btn);
        letterButtons[ch] = btn;
    }

    // 添加底部弹性空间
    layout->addStretch(1);
}
