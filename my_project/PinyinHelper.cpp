#include "PinyinHelper.h"
#include <QDebug> // 添加调试输出支持

// 静态成员初始化
const QMap<QChar, QString> PinyinHelper::pinyinMap = PinyinHelper::createPinyinMap();

QMap<QChar, QString> PinyinHelper::createPinyinMap()
{
    QMap<QChar, QString> map;

    // 使用 QString 和 at(0) 获取正确的 QChar
    map.insert(QString("啊").at(0), "a");//at(0)表示获取键值，也就是字符串首字母
    map.insert(QString("阿").at(0), "a");
    map.insert(QString("八").at(0), "ba");
    map.insert(QString("吧").at(0), "ba");
    map.insert(QString("爸").at(0), "ba");
    map.insert(QString("白").at(0), "bai");
    map.insert(QString("百").at(0), "bai");
    map.insert(QString("班").at(0), "ban");
    map.insert(QString("办").at(0), "ban");
    map.insert(QString("包").at(0), "bao");
    map.insert(QString("宝").at(0), "bao");
    map.insert(QString("北").at(0), "bei");
    map.insert(QString("本").at(0), "ben");
    map.insert(QString("比").at(0), "bi");
    map.insert(QString("边").at(0), "bian");
    map.insert(QString("表").at(0), "biao");
    map.insert(QString("别").at(0), "bie");
    map.insert(QString("宾").at(0), "bin");
    map.insert(QString("病").at(0), "bing");
    map.insert(QString("不").at(0), "bu");
    map.insert(QString("长").at(0), "chang");
    map.insert(QString("成").at(0), "cheng");
    map.insert(QString("程").at(0), "cheng");
    map.insert(QString("吃").at(0), "chi");
    map.insert(QString("出").at(0), "chu");
    map.insert(QString("大").at(0), "da");
    map.insert(QString("的").at(0), "de");
    map.insert(QString("东").at(0), "dong");
    map.insert(QString("都").at(0), "dou");
    map.insert(QString("多").at(0), "duo");
    map.insert(QString("发").at(0), "fa");
    map.insert(QString("法").at(0), "fa");
    map.insert(QString("反").at(0), "fan");
    map.insert(QString("放").at(0), "fang");
    map.insert(QString("飞").at(0), "fei");
    map.insert(QString("分").at(0), "fen");
    map.insert(QString("风").at(0), "feng");
    map.insert(QString("高").at(0), "gao");
    map.insert(QString("个").at(0), "ge");
    map.insert(QString("给").at(0), "gei");
    map.insert(QString("公").at(0), "gong");
    map.insert(QString("工").at(0), "gong");
    map.insert(QString("关").at(0), "guan");
    map.insert(QString("光").at(0), "guang");
    map.insert(QString("国").at(0), "guo");
    map.insert(QString("过").at(0), "guo");
    map.insert(QString("好").at(0), "hao");
    map.insert(QString("和").at(0), "he");
    map.insert(QString("黑").at(0), "hei");
    map.insert(QString("很").at(0), "hen");
    map.insert(QString("红").at(0), "hong");
    map.insert(QString("花").at(0), "hua");
    map.insert(QString("话").at(0), "hua");
    map.insert(QString("欢").at(0), "huan");
    map.insert(QString("黄").at(0), "huang");
    map.insert(QString("回").at(0), "hui");
    map.insert(QString("会").at(0), "hui");
    map.insert(QString("家").at(0), "jia");
    map.insert(QString("见").at(0), "jian");
    map.insert(QString("江").at(0), "jiang");
    map.insert(QString("叫").at(0), "jiao");
    map.insert(QString("今").at(0), "jin");
    map.insert(QString("京").at(0), "jing");
    map.insert(QString("九").at(0), "jiu");
    map.insert(QString("开").at(0), "kai");
    map.insert(QString("看").at(0), "kan");
    map.insert(QString("口").at(0), "kou");
    map.insert(QString("来").at(0), "lai");
    map.insert(QString("老").at(0), "lao");
    map.insert(QString("了").at(0), "le");
    map.insert(QString("李").at(0), "li");
    map.insert(QString("林").at(0), "lin");
    map.insert(QString("刘").at(0), "liu");
    map.insert(QString("马").at(0), "ma");
    map.insert(QString("毛").at(0), "mao");
    map.insert(QString("每").at(0), "mei");
    map.insert(QString("门").at(0), "men");
    map.insert(QString("明").at(0), "ming");
    map.insert(QString("你").at(0), "ni");
    map.insert(QString("年").at(0), "nian");
    map.insert(QString("牛").at(0), "niu");
    map.insert(QString("女").at(0), "nv");
    map.insert(QString("朋").at(0), "peng");
    map.insert(QString("七").at(0), "qi");
    map.insert(QString("前").at(0), "qian");
    map.insert(QString("钱").at(0), "qian");
    map.insert(QString("青").at(0), "qing");
    map.insert(QString("秋").at(0), "qiu");
    map.insert(QString("人").at(0), "ren");
    map.insert(QString("日").at(0), "ri");
    map.insert(QString("三").at(0), "san");
    map.insert(QString("山").at(0), "shan");
    map.insert(QString("上").at(0), "shang");
    map.insert(QString("谁").at(0), "shei");
    map.insert(QString("十").at(0), "shi");
    map.insert(QString("时").at(0), "shi");
    map.insert(QString("是").at(0), "shi");
    map.insert(QString("书").at(0), "shu");
    map.insert(QString("水").at(0), "shui");
    map.insert(QString("孙").at(0), "sun");
    map.insert(QString("他").at(0), "ta");
    map.insert(QString("天").at(0), "tian");
    map.insert(QString("听").at(0), "ting");
    map.insert(QString("王").at(0), "wang");
    map.insert(QString("我").at(0), "wo");
    map.insert(QString("无").at(0), "wu");
    map.insert(QString("五").at(0), "wu");
    map.insert(QString("西").at(0), "xi");
    map.insert(QString("下").at(0), "xia");
    map.insert(QString("先").at(0), "xian");
    map.insert(QString("想").at(0), "xiang");
    map.insert(QString("小").at(0), "xiao");
    map.insert(QString("谢").at(0), "xie");
    map.insert(QString("新").at(0), "xin");
    map.insert(QString("学").at(0), "xue");
    map.insert(QString("一").at(0), "yi");
    map.insert(QString("已").at(0), "yi");
    map.insert(QString("有").at(0), "you");
    map.insert(QString("月").at(0), "yue");
    map.insert(QString("张").at(0), "zhang");
    map.insert(QString("赵").at(0), "zhao");
    map.insert(QString("中").at(0), "zhong");
    map.insert(QString("周").at(0), "zhou");
    map.insert(QString("朱").at(0), "zhu");
    map.insert(QString("去").at(0), "qu");
    map.insert(QString("电").at(0), "dian");
    map.insert(QString("话").at(0), "hua");
    map.insert(QString("姓").at(0), "xing");
    map.insert(QString("名").at(0), "ming");
    map.insert(QString("陈").at(0), "chen");
    map.insert(QString("杨").at(0), "yang");

    // 特殊字符处理
    map.insert(QChar('&'), "");
    map.insert(QChar('@'), "");
    map.insert(QChar('#'), "");
    map.insert(QChar('$'), "");
    map.insert(QChar('%'), "");

    // 添加英文处理
    for (char c = 'A'; c <= 'Z'; ++c) {
        map.insert(QChar(c), QString(QChar(c)).toLower());
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        map.insert(QChar(c), QString(QChar(c)));
    }

    return map;
}

QString PinyinHelper::getFullPinyin(const QString &text)
{
    QString result;
    for (const QChar &ch : text) {
        if (pinyinMap.contains(ch)) {
            QString pinyin = pinyinMap.value(ch);
            result += pinyin;
        } else if (ch.isLetterOrNumber()) {
            result += ch.toLower();
        } else {
            result += " ";
        }
    }
    return result;
}

QChar PinyinHelper::getInitial(const QString &text)
{
    if (text.isEmpty()) return '#';

    QChar firstChar = text.at(0);

    // 处理汉字 - 确保只返回首字母
    if (pinyinMap.contains(firstChar)) {
        QString pinyin = pinyinMap.value(firstChar);
        if (!pinyin.isEmpty()) {
            // 只返回第一个字母的大写形式
            return pinyin[0].toUpper();
        }
    }

    // 处理英文字母
    if (firstChar.isLetter()) {
        return firstChar.toUpper();
    }

    // 其他所有情况都归为"#"组
    return '#';
}
