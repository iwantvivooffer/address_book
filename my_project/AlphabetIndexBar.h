#ifndef ALPHABETINDEXBAR_H
#define ALPHABETINDEXBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>

class AlphabetIndexBar : public QWidget
{
    Q_OBJECT

public:
    explicit AlphabetIndexBar(QWidget *parent = nullptr);
    void highlightLetter(QChar letter); // 添加高亮方法
     QList<QChar> getIndexLetters() const { return indexLetters; }

signals:
    void letterClicked(QChar letter);//返回当前被点击的字母

private:
    QMap<QChar, QPushButton*> letterButtons;//利用map将按键和字母相对应
    QList<QChar> indexLetters = {'#',
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};//存储字母

    QChar currentHighlighted = QChar(); // 当前高亮字母
    void setupLayout();//垂直布局
};

#endif // ALPHABETINDEXBAR_H
