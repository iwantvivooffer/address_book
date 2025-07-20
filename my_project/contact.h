#ifndef CONTACT_H
#define CONTACT_H

#include<QString>


class contact
{
private:
    QString name;
    QString number;
    QString group;
    QString emile;
    
    
public:
    //构造函数
    contact();
    contact(const QString&name,const QString&number,const QString&group="",const QString&emile="");
    //修改信息
    void setname(QString&name);
    void setnumber(QString&number);
    void setgroup(QString&group);
    void setemile(QString&emile);
    //获取信息
    QString getname();
    QString getnumber();
    QString getgroup();
    QString getemile();
    
};

#endif // CONTACT_H
