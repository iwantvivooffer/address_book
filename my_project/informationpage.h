#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include "contact.h"

class InformationPage : public QWidget
{
    Q_OBJECT
public:
    explicit InformationPage(QWidget *parent = nullptr);
    ~InformationPage();

    void showContactDetails(contact &contact);
    void slideIn();
    void slideOut();
    void showEvent(QShowEvent *event) override;
signals:
    void backClicked();
    void moreClicked();

private:
    QLabel *nameLabel;
    QLabel *numberLabel;
    QLabel *groupLabel;
    QLabel *emailLabel;
    QPushButton *backButton;
    QPushButton *moreButton;
    QPropertyAnimation *animation;
};

#endif // INFORMATIONPAGE_H
