#ifndef CONTACT_H
#define CONTACT_H

#include<QString>
#include<QJsonObject>

class contact
{
private:
    //基本信息
    QString name;
    QString number;
    QString group;
    QString email;

public:
    //构造函数
    contact();
    contact(const QString& name, const QString& number, const QString& group = "", const QString& email = "");

    //修改信息
    void setname(const QString& name);
    void setnumber(const QString& number);
    void setgroup(const QString& group);
    void setemail(const QString& email);

    //获取信息
    QString getname() const ;
    QString getnumber()const ;
    QString getgroup() const ;
    QString getemail() const ;

    // 序列化成 QJsonObject
    QJsonObject toJson() const;

    // 从 QJsonObject 创建 contact
    static contact fromJson(const QJsonObject &obj);
};

#endif // CONTACT_H
