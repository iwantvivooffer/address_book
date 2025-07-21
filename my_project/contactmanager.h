#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include<QList>
#include<QString>
#include<QSettings>
#include<QJsonArray>

#include"contact.h"

class contactManager
{
private:
    QList<contact> contacts;
    
public:
    contactManager();
    //增删联系人
    void addcontact(contact&contact);
    bool deletecontact(const QString&name);

    //排序
    void sortContactsByName();

    //获取联系人们
    QList<contact> getcontacts();
    QList<contact> getcontactsByGroup(QString&group);

    //保存联系人到 JSON 文件
    void saveToJson(const QString &filename);
    //从 JSON 文件加载联系人
    void loadFromJson(const QString &filename);

};

#endif // CONTACTMANAGER_H
