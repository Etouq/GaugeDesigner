#include "binaryutil.h"

#include <QByteArray>
#include <QColor>
#include <QIODevice>
#include <QString>

// to binary converters
// fundamental types
QByteArray BinaryUtil::toBinary(int8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

QByteArray BinaryUtil::toBinary(bool bl)
{
    return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
}

QByteArray BinaryUtil::toBinary(float flt)
{
    return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
}
QByteArray BinaryUtil::toBinary(double dbl)
{
    return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
}


// basic types
QByteArray BinaryUtil::toBinary(const QString &str)
{
    QByteArray bytes = str.toUtf8();
    uint8_t size = bytes.size();
    bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
    return bytes;
}

QByteArray BinaryUtil::toBinary(const QColor &col)
{
    uint8_t red = col.red();
    uint8_t green = col.green();
    uint8_t blue = col.blue();
    return QByteArray(reinterpret_cast<char *>(&red), sizeof(red)) + QByteArray(reinterpret_cast<char *>(&green), sizeof(green))
           + QByteArray(reinterpret_cast<char *>(&blue), sizeof(blue));
}

QByteArray BinaryUtil::toBinary(Units unit)
{
    return QByteArray(reinterpret_cast<char *>(&unit), sizeof(unit));
}


// struct types
QByteArray BinaryUtil::toBinary(const ColorZone &zone)
{
    return toBinary(zone.start) + toBinary(zone.end) + toBinary(zone.color);
}

QByteArray BinaryUtil::toBinary(const GradDef &grad)
{
    return toBinary(grad.gradPos) + toBinary(grad.isBig) + toBinary(grad.gradColor);
}

QByteArray BinaryUtil::toBinary(const TextGradDef &textGrad)
{
    return toBinary(textGrad.textGradPos) + toBinary(textGrad.gradText);
}


// vector types
QByteArray BinaryUtil::toBinary(const QVector<ColorZone> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}

QByteArray BinaryUtil::toBinary(const QVector<GradDef> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}

QByteArray BinaryUtil::toBinary(const QVector<TextGradDef> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}



// read functions
// fundamental types
int8_t BinaryUtil::readInt8_t(QIODevice &data)
{
    int8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint8_t BinaryUtil::readUint8_t(QIODevice &data)
{
    uint8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int16_t BinaryUtil::readInt16_t(QIODevice &data)
{
    int16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint16_t BinaryUtil::readUint16_t(QIODevice &data)
{
    uint16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int32_t BinaryUtil::readInt32_t(QIODevice &data)
{
    int32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint32_t BinaryUtil::readUint32_t(QIODevice &data)
{
    uint32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int64_t BinaryUtil::readInt64_t(QIODevice &data)
{
    int64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint64_t BinaryUtil::readUint64_t(QIODevice &data)
{
    uint64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

bool BinaryUtil::readBool(QIODevice &data)
{
    bool val = false;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

float BinaryUtil::readFloat(QIODevice &data)
{
    float val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
double BinaryUtil::readDouble(QIODevice &data)
{
    double val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}


// basic types
QString BinaryUtil::readString(QIODevice &data)
{
    uint8_t size = readUint8_t(data);
    return size == 0 ? "" : QString::fromUtf8(data.read(size));
}

QColor BinaryUtil::readColor(QIODevice &data)
{
    uint8_t red = readUint8_t(data);
    uint8_t green = readUint8_t(data);
    uint8_t blue = readUint8_t(data);

    return QColor(red, green, blue);
}

Units BinaryUtil::readUnit(QIODevice &data)
{
    Units val = Units::NONE;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}


// struct types
ColorZone BinaryUtil::readColorZone(QIODevice &data)
{
    return ColorZone { readDouble(data), readDouble(data), readColor(data) };
}

GradDef BinaryUtil::readGrad(QIODevice &data)
{
    return GradDef { readDouble(data), readBool(data), readColor(data) };
}

TextGradDef BinaryUtil::readTextGrad(QIODevice &data)
{
    return TextGradDef { readDouble(data), readString(data) };
}


// vector types
void BinaryUtil::readColorZoneVec(QIODevice &data, QVector<ColorZone> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readColorZone(data));
}

void BinaryUtil::readGradVec(QIODevice &data, QVector<GradDef> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readGrad(data));
}

void BinaryUtil::readTextGradVec(QIODevice &data, QVector<TextGradDef> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readTextGrad(data));
}
