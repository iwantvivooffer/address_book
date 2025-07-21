#include "contactmanager.h"
#include <QFile>
#include <QJsonDocument>
#include<algorithm>
#include<QCollator>

contactManager::contactManager()
{
}

//增删联系人
void contactManager::addcontact(const contact &contact){

    contacts.append(contact);
    sortContactsByName();//添加信息后马上就排序

}
bool contactManager::deletecontact(const QString &name){
    for(int i = 0; i < contacts.size(); ++i){
        if (contacts[i].getname() == name) {
            contacts.removeAt(i);
            return true;
        }
    }
    return false;  // 没找到对应联系人
}

//排序实现
void contactManager::sortContactsByName()
{
    QCollator collator;
    collator.setLocale(QLocale::Chinese); // 支持中文拼音排序
    collator.setNumericMode(true);

    std::sort(contacts.begin(), contacts.end(), [&](const contact &a, const contact &b) {
        return collator.compare(a.getname(), b.getname()) < 0;
    });
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

//保存和读取
void contactManager::saveToJson(const QString &filename) {
    QJsonArray jsonArray;
    for (const contact &c : contacts) {
        jsonArray.append(c.toJson());
    }
    QJsonDocument doc(jsonArray);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}
void contactManager::loadFromJson(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return; //文件打开失败，直接返回
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return; //格式不正确
    }
    contacts.clear();
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &val : jsonArray) {
        QJsonObject obj = val.toObject();
        contacts.append(contact::fromJson(obj));
    }

    sortContactsByName();

}

