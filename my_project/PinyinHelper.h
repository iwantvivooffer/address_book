#ifndef PINYINHELPER_H
#define PINYINHELPER_H

#include <QString>
#include <QChar>
#include <QMap>

class PinyinHelper {
public:
    static QChar getInitial(const QString &text);             // 获取首拼字母
    static QString getFullPinyin(const QString &text);        // 获取完整拼音

private:
    static QMap<QChar, QString> createPinyinMap();            // 构建字典
    static const QMap<QChar, QString> pinyinMap;              // 静态字典
};

#endif // PINYINHELPER_H
