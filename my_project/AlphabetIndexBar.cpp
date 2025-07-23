
#include "AlphabetIndexBar.h"
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
AlphabetIndexBar::AlphabetIndexBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(36);
    setupLayout();
}

void AlphabetIndexBar::highlightLetter(QChar letter)
{
    // 清除之前的高亮
    if (currentHighlighted != QChar() && letterButtons.contains(currentHighlighted)) {
        letterButtons[currentHighlighted]->setStyleSheet(R"(
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
    }

    // 设置新的高亮（点击时）
    if (letterButtons.contains(letter)) {
        currentHighlighted = letter;
        letterButtons[letter]->setStyleSheet(R"(
            QPushButton {
                background-color: rgba(0,0,0,0.3); /* 点击时深灰色背景 */
                border: none;
                font-size: 18px;
                font-weight: bold;
                color: black;
                border-radius: 18px;
            }
        )");

        // 2秒后自动恢复
        QTimer::singleShot(2000, this, [this, letter]() {
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
                currentHighlighted = QChar();
            }
        });
    }
}

void AlphabetIndexBar::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(1);
    layout->setContentsMargins(5, 10, 5, 10);
    layout->setAlignment(Qt::AlignCenter);

    // 添加顶部弹性空间
    layout->addStretch(1);

    for (QChar ch : indexLetters) {
        QPushButton *btn = new QPushButton(QString(ch), this);
        btn->setFixedSize(36, 36); // 进一步增大尺寸
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: transparent;
                border: none;             /* 无边框 */
                font-size: 18px;          /* 更大字体 */
                font-weight: bold;        /* 加粗 */
                color: black;             /* 黑色字体 */
            }
            QPushButton:hover {
                background-color: rgba(0,0,0,0.1); /* 悬停时轻微灰色 */
                border-radius: 18px;      /* 圆形效果 */
            }
            QPushButton:pressed {
                background-color: rgba(0,0,0,0.3); /* 点击时深灰色 */
                border-radius: 18px;
            }
        )");
        connect(btn, &QPushButton::clicked, this, [this, ch]() {
            emit letterClicked(ch);
        });
        layout->addWidget(btn);
        letterButtons[ch] = btn;
    }

    // 添加底部弹性空间
    layout->addStretch(1);
}
