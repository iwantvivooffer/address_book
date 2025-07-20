#include "contactmanager.h"

contactManager::contactManager()
{

    loadContacts();  // 构造函数中加载联系人
}


//增删联系人
void contactManager::addcontact(contact &contact){
    contacts.append(contact);
    saveContacts();  // 添加后保存
}

bool contactManager::deletecontact(QString &name){
    for(int i=0;i<contacts.size();++i){
        contacts.removeAt(i);
        return true;
    }
    return false;
}

//获取联系人
QList<contact> contactManager::getcontacts(){
    return contacts;
}
QList<contact> contactManager::getcontactsByGroup(QString &group){
    QList<contact> result;
    for (auto &c : contacts) {
            if (c.getgroup() == group) {
                result.append(c);
            }
        }
        return result;
    
}
// 实现保存联系人
void contactManager::saveContacts() {
    QSettings settings("ContactApp", "ContactManager");
    settings.beginWriteArray("contacts");
    for (int i = 0; i < contacts.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("name", contacts[i].getname());
        settings.setValue("number", contacts[i].getnumber());
        settings.setValue("group", contacts[i].getgroup());
        settings.setValue("email", contacts[i].getemail());
    }
    settings.endArray();
}

// 实现加载联系人
void contactManager::loadContacts() {
    contacts.clear();
    QSettings settings("ContactApp", "ContactManager");
    int size = settings.beginReadArray("contacts");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString name = settings.value("name").toString();
        QString number = settings.value("number").toString();
        QString group = settings.value("group").toString();
        QString email = settings.value("email").toString();
        contacts.append(contact(name, number, group, email));
    }
    settings.endArray();
}
