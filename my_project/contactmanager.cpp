#include "contactmanager.h"
#include "PinyinHelper.h"
#include <QFile>
#include <QJsonDocument>
#include<algorithm>
#include<QCollator>
#include <QDebug>

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
    return false;  //没找到对应联系人
}

//排序实现
void contactManager::sortContactsByName()
{
    std::sort(contacts.begin(), contacts.end(), [](const contact &a, const contact &b) {
        QString nameA = a.getname().trimmed();
        QString nameB = b.getname().trimmed();

        // 处理空名字
        if (nameA.isEmpty()) return true;
        if (nameB.isEmpty()) return false;

        // 获取拼音首字母
        QChar initA = PinyinHelper::getInitial(nameA);
        QChar initB = PinyinHelper::getInitial(nameB);

        // 特殊字符排在前面
        if (initA == '#' && initB != '#') return true;
        if (initA != '#' && initB == '#') return false;
        if (initA == '#' && initB == '#') {
            // 都是特殊字符，按原始字符串排序
            return nameA < nameB;
        }

        // 获取拼音全拼
        QString pinyinA = PinyinHelper::getFullPinyin(nameA);
        QString pinyinB = PinyinHelper::getFullPinyin(nameB);

        // 直接比较拼音字符串
        return pinyinA.compare(pinyinB, Qt::CaseInsensitive) < 0;
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
    QJsonArray jsonArray;//封装成一个数组便于存储
    for (const contact &c : contacts) {
        jsonArray.append(c.toJson());
    }
    QJsonDocument doc(jsonArray);//便于写入文件
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {//如果没有就创建一个文件
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
        return; //确保是一个JSON数组
    }
    contacts.clear();
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &val : jsonArray) {
        QJsonObject obj = val.toObject();
        contacts.append(contact::fromJson(obj));
    }

    sortContactsByName();

}

