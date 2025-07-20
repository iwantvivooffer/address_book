#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include<QList>
#include<QString>
#include<QSettings>
#include"contact.h"

class contactManager
{
private:
    QList<contact>contacts;
    
public:
    contactManager();
    //增删联系人
    void addcontact(contact&contact);
    bool deletecontact(QString&name);
    //获取联系人们
    QList<contact> getcontacts();
    QList<contact> getcontactsByGroup(QString&group);
    // 添加保存和加载函数
    void saveContacts();
    void loadContacts();
    
    
};

#endif // CONTACTMANAGER_H
