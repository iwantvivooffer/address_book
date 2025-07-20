#include "contact.h"

contact::contact()
{

}

contact::contact(const QString &name, const QString &number,const QString &group,const QString &emile):name(name),number(number),group(group),email(emile){}

//获取信息
QString contact::getemail(){
    return email;
}

QString contact::getgroup(){
    return group;
}

QString contact::getname(){
    return name;
}

QString contact::getnumber(){
    return number;
}


//设置信息
void contact::setemile(QString &emile){
    this->email=emile;
}

void contact::setgroup(QString &group){
    this->group=group;
}

void contact::setname(QString &name){
    this->name=name;
}

void contact::setnumber(QString &number){
    this->number=number;
}

