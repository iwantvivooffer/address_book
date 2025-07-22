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

    void showContactDetails(const contact &contact);
    void slideIn();
    void slideOut();
    void showEvent(QShowEvent *event) override;
    // 添加暗色模式设置
    void setDarkMode(bool darkMode);
signals:
    void backClicked();
    void saveContact(contact original, contact modified);
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

    QPushButton *backButton;
    QPushButton *saveButton;
    QPushButton *deleteButton;
    QPropertyAnimation *animation;

    bool hasChanges = false;
    bool isDarkMode = false;  // 添加暗色模式状态
};

#endif // INFORMATIONPAGE_H
