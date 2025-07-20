#include "contactmanager.h"

contactManager::contactManager()
{

}


//增删联系人
void contactManager::addcontact(contact &contact){
    contacts.append(contact);
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
