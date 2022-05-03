#ifndef BINARYCONVERTER_HPP
#define BINARYCONVERTER_HPP

#include "aircraftmanager/definitions/basetypes.hpp"
#include "unitconverter/units.hpp"

#include <QVector>
#include <QString>
#include <QByteArray>
#include <QIODevice>
#include <QColor>
#include <cstdint>


namespace BinaryConverter {
// to binary converters
// fundamental types
inline QByteArray toBinary(int8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(uint8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(int16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(uint16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(int32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(uint32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(int64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
inline QByteArray toBinary(uint64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(bool bl)
{
    return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
}

inline QByteArray toBinary(float flt)
{
    return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
}
inline QByteArray toBinary(double dbl)
{
    return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
}



// basic types
inline QByteArray toBinary(const QString &str)
{
    QByteArray bytes = str.toUtf8();
    uint8_t size = bytes.size();
    bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
    return bytes;
}

inline QByteArray toBinary(const QColor &col)
{
    uint8_t red = col.red();
    uint8_t green = col.green();
    uint8_t blue = col.blue();
    return QByteArray(reinterpret_cast<char *>(&red), sizeof(red))
        + QByteArray(reinterpret_cast<char *>(&green), sizeof(green))
        + QByteArray(reinterpret_cast<char *>(&blue), sizeof(blue));
}

inline QByteArray toBinary(Units unit)
{
    return QByteArray(reinterpret_cast<char *>(&unit), sizeof(unit));
}


// struct types
inline QByteArray toBinary(const ColorZone &zone)
{
    return toBinary(zone.start) + toBinary(zone.end) + toBinary(zone.color);
}

inline QByteArray toBinary(const GradDef &grad)
{
    return toBinary(grad.gradPos) + toBinary(grad.isBig) + toBinary(grad.gradColor);
}

inline QByteArray toBinary(const TextGradDef &textGrad)
{
    return toBinary(textGrad.textGradPos) + toBinary(textGrad.gradText);
}


// vector types
inline QByteArray toBinary(const QVector<ColorZone> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}

inline QByteArray toBinary(const QVector<GradDef> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}

inline QByteArray toBinary(const QVector<TextGradDef> &vec)
{
    uint8_t size = vec.size();
    QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

    for (int idx = 0; idx < size; idx++)
        ret += toBinary(vec[idx]);

    return ret;
}


// from binary converters
// fundamental types
inline int8_t readInt8_t(QIODevice &data)
{
    int8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline uint8_t readUint8_t(QIODevice &data)
{
    uint8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline int16_t readInt16_t(QIODevice &data)
{
    int16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline uint16_t readUint16_t(QIODevice &data)
{
    uint16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline int32_t readInt32_t(QIODevice &data)
{
    int32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline uint32_t readUint32_t(QIODevice &data)
{
    uint32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline int64_t readInt64_t(QIODevice &data)
{
    int64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline uint64_t readUint64_t(QIODevice &data)
{
    uint64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline bool readBool(QIODevice &data)
{
    bool val = false;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline float readFloat(QIODevice &data)
{
    float val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
inline double readDouble(QIODevice &data)
{
    double val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}


// basic types
inline QString readString(QIODevice &data)
{
    uint8_t size = readUint8_t(data);
    return size == 0 ? "" : QString::fromUtf8(data.read(size));
}

inline QColor readColor(QIODevice &data)
{
    uint8_t red = readUint8_t(data);
    uint8_t green = readUint8_t(data);
    uint8_t blue = readUint8_t(data);

    return QColor(red, green, blue);
}

inline Units readUnit(QIODevice &data)
{
    Units val = Units::NONE;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}


// struct types
inline ColorZone readColorZone(QIODevice &data)
{
    return ColorZone{ readDouble(data), readDouble(data), readColor(data) };
}

inline GradDef readGrad(QIODevice &data)
{
    return GradDef{ readDouble(data), readBool(data), readColor(data) };
}

inline TextGradDef readTextGrad(QIODevice &data)
{
    return TextGradDef{ readDouble(data), readString(data) };
}


// vector types
inline void readColorZoneVec(QIODevice &data, QVector<ColorZone> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readColorZone(data));
}

inline void readGradVec(QIODevice &data, QVector<GradDef> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readGrad(data));
}

inline void readTextGradVec(QIODevice &data, QVector<TextGradDef> &vec)
{
    uint8_t size = readUint8_t(data);
    for (int idx = 0; idx < size; idx++)
        vec.append(readTextGrad(data));
}

}   // namespace BinaryUtil

#endif // BINARYCONVERTER_HPP
