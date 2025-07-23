#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QMessageBox>

#include "contact.h"

class InformationPage : public QWidget
{
    Q_OBJECT
public:
    explicit InformationPage(QWidget *parent = nullptr);
    ~InformationPage();

    void showContactDetails(const contact &contact);//显示信息到详细页面
    void slideIn();
    void slideOut();
    void showEvent(QShowEvent *event) override;
    void setLanguageState(bool chinese);//语言
    void setDarkMode(bool darkMode);//暗色
signals:
    void backClicked();
    void saveContact(contact original, contact modified);//便于对比前后联系人详细变化
    void deleteContact(QString name);

private slots:
    void onSaveClicked();
    void onDeleteClicked();
    void checkForChanges();


private:
    contact originalContact;
    QLineEdit *nameEdit;
    QLineEdit *numberEdit;
    QLineEdit *groupEdit;
    QLineEdit *emailEdit;

    QLabel *nameTitle;
    QLabel *numberTitle;
    QLabel *groupTitle;
    QLabel *emailTitle;

    QPushButton *backButton;
    QPushButton *saveButton;
    QPushButton *deleteButton;
    QPropertyAnimation *animation;

    bool hasChanges = false;
    bool isChinese = true;  // 添加语言状态变量
    bool isDarkMode = false;  // 添加暗色模式状态

    void updateUILanguage();
};

#endif // INFORMATIONPAGE_H
