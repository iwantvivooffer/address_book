#include "contact.h"

contact::contact()
{
}

contact::contact(const QString &name, const QString &number, const QString &group, const QString &email)
    : name(name), number(number), group(group), email(email){}

//获取信息
QString contact::getemail() const {
    return email;
}
QString contact::getgroup() const {
    return group;
}
QString contact::getname() const {
    return name;
}
QString contact::getnumber() const {
    return number;
}

//设置信息
void contact::setemail(const QString &email) {
    this->email = email;
}
void contact::setgroup(const QString &group) {
    this->group = group;
}
void contact::setname(const QString &name) {
    this->name = name;
}
void contact::setnumber(const QString &number) {
    this->number = number;
}

//保存到JSON文件里面
QJsonObject contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["number"] = number;
    obj["group"] = group;
    obj["email"] = email;
    return obj;
}
//从JSON文件里面读取
contact contact::fromJson(const QJsonObject &obj) {
    contact c;
    c.setname(obj["name"].toString());
    c.setnumber(obj["number"].toString());
    c.setgroup(obj["group"].toString());
    c.setemail(obj["email"].toString());
    return c;
}


