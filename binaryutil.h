#ifndef BINARYUTIL_H
#define BINARYUTIL_H

#include <QString>
#include <QByteArray>
#include <QIODevice>
#include <QColor>
#include <QVector>
#include "AircraftManager/definitions/basetypes.h"
#include "UnitConverter/units.h"
#include <cstdint>

class BinaryUtil
{
public:
    BinaryUtil() = default;

    //fundamental types
    static QByteArray toBinary(int8_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint8_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int16_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint16_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int32_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint32_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int64_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint64_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }

    static QByteArray toBinary(bool bl)
    {
        return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
    }

    static QByteArray toBinary(float flt)
    {
        return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
    }
    static QByteArray toBinary(double dbl)
    {
        return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
    }


    //basic types
    static QByteArray toBinary(const QString &str)
    {
        QByteArray bytes = str.toUtf8();
        uint8_t size = bytes.size();
        bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
        return bytes;
    }

    static QByteArray toBinary(const QColor &col)
    {
        uint8_t red = col.red();
        uint8_t green = col.green();
        uint8_t blue = col.blue();
        return QByteArray(reinterpret_cast<char *>(&red), sizeof(red)) +
               QByteArray(reinterpret_cast<char *>(&green), sizeof(green)) +
               QByteArray(reinterpret_cast<char *>(&blue), sizeof(blue));
    }

    static QByteArray toBinary(Units unit)
    {
        return QByteArray(reinterpret_cast<char *>(&unit), sizeof(unit));
    }


    //struct types
    static QByteArray toBinary(const ColorZone &zone)
    {
        return toBinary(zone.start) + toBinary(zone.end) + toBinary(zone.color);
    }

    static QByteArray toBinary(const GradDef &grad)
    {
        return toBinary(grad.gradPos) + toBinary(grad.isBig) + toBinary(grad.gradColor);
    }

    static QByteArray toBinary(const TextGradDef &textGrad)
    {
        return toBinary(textGrad.textGradPos) + toBinary(textGrad.gradText);
    }


    //vector types
    static QByteArray toBinary(const QVector<ColorZone> &vec)
    {
        uint8_t size = vec.size();
        QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

        for (int idx = 0; idx < size; idx++)
            ret += toBinary(vec[idx]);

        return ret;
    }

    static QByteArray toBinary(const QVector<GradDef> &vec)
    {
        uint8_t size = vec.size();
        QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

        for (int idx = 0; idx < size; idx++)
            ret += toBinary(vec[idx]);

        return ret;
    }

    static QByteArray toBinary(const QVector<TextGradDef> &vec)
    {
        uint8_t size = vec.size();
        QByteArray ret(reinterpret_cast<char *>(&size), sizeof(size));

        for (int idx = 0; idx < size; idx++)
            ret += toBinary(vec[idx]);

        return ret;
    }




    //read functions
    //fundamental types
    static int8_t readInt8_t(QIODevice &data)
    {
        int8_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint8_t readUint8_t(QIODevice &data)
    {
        uint8_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int16_t readInt16_t(QIODevice &data)
    {
        int16_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint16_t readUint16_t(QIODevice &data)
    {
        uint16_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int32_t readInt32_t(QIODevice &data)
    {
        int32_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint32_t readUint32_t(QIODevice &data)
    {
        uint32_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int64_t readInt64_t(QIODevice &data)
    {
        int64_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint64_t readUint64_t(QIODevice &data)
    {
        uint64_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }

    static bool readBool(QIODevice &data)
    {
        bool val = false;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }

    static float readFloat(QIODevice &data)
    {
        float val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static double readDouble(QIODevice &data)
    {
        double val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }


    //basic types
    static QString readString(QIODevice &data)
    {
        uint8_t size = readUint8_t(data);
        return size == 0 ? "" : QString::fromUtf8(data.read(size));
    }

    static QColor readColor(QIODevice &data)
    {
        uint8_t red = readUint8_t(data);
        uint8_t green = readUint8_t(data);
        uint8_t blue = readUint8_t(data);

        return QColor(red, green, blue);
    }

    static Units readUnit(QIODevice &data)
    {
        Units val = Units::NONE;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }

    //struct types
    static ColorZone readColorZone(QIODevice &data)
    {
        return ColorZone{ readDouble(data), readDouble(data), readColor(data) };
    }

    static GradDef readGrad(QIODevice &data)
    {
        return GradDef{ readDouble(data), readBool(data), readColor(data) };
    }

    static TextGradDef readTextGrad(QIODevice &data)
    {
        return TextGradDef{ readDouble(data), readString(data) };
    }

    //vector types
    static void readColorZoneVec(QIODevice &data, QVector<ColorZone> &vec)
    {
        uint8_t size = readUint8_t(data);
        for (int idx = 0; idx < size; idx++)
            vec.append(readColorZone(data));
    }

    static void readGradVec(QIODevice &data, QVector<GradDef> &vec)
    {
        uint8_t size = readUint8_t(data);
        for (int idx = 0; idx < size; idx++)
            vec.append(readGrad(data));
    }

    static void readTextGradVec(QIODevice &data, QVector<TextGradDef> &vec)
    {
        uint8_t size = readUint8_t(data);
        for (int idx = 0; idx < size; idx++)
            vec.append(readTextGrad(data));
    }






};

#endif // BINARYUTIL_H
