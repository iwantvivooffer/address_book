
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
    void letterClicked(QChar letter);

private:
    QMap<QChar, QPushButton*> letterButtons;
    QList<QChar> indexLetters = {'#',
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    QChar currentHighlighted = QChar(); // 当前高亮字母
    void setupLayout();
};

#endif // ALPHABETINDEXBAR_H
