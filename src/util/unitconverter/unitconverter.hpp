#ifndef _UNITCONVERTER_H_
#define _UNITCONVERTER_H_

#include <QObject>
#include <QVector>

class UnitConverter : public QObject
{
    Q_OBJECT
public:
    explicit UnitConverter(QObject *parent = nullptr);


    Q_INVOKABLE static QString convertToLongString(int unit);
    Q_INVOKABLE static QString convertToShortString(int unit);
    Q_INVOKABLE static QString getSectionHeader(int type);

    Q_INVOKABLE static QVector<int> getAllowedUnits(int type);
};


#endif   // _UNITCONVERTER_H_
