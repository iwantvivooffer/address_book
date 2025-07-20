#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "contact.h"

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(const contact &contact, QWidget *parent = nullptr);
    ~ContactDialog();

protected:
    void paintEvent(QPaintEvent *event);

private:
    contact m_contact;
};

#endif // CONTACTDIALOG_H
