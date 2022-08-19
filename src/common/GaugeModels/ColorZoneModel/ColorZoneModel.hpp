#ifndef __COLOR_ZONE_MODEL_HPP__
#define __COLOR_ZONE_MODEL_HPP__

#include <QAbstractListModel>
#include "common/definitions/BaseTypes.hpp"
#include <QDebug>

class ColorZoneModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum ModelRoles
    {
        StartRole = Qt::UserRole + 1,
        EndRole,
        ColorRole
    };

    ColorZoneModel(QObject *parent = nullptr)
      : QAbstractListModel(parent)
    {}

    const QList<definitions::ColorZone> &getData() const
    {
        return d_colorZones;
    }

    void changeData(const QList<definitions::ColorZone> &data)
    {
        beginResetModel();

        d_colorZones = data;

        endResetModel();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (index.row() < 0 || index.row() >= d_colorZones.size())
            return QVariant();

        switch (static_cast<ModelRoles>(role))
        {
            case ModelRoles::StartRole:
                return std::round(d_colorZones.at(index.row()).start * 1e10) * 1e-10;
            case ModelRoles::EndRole:
                return std::round(d_colorZones.at(index.row()).end * 1e10) * 1e-10;
            case ModelRoles::ColorRole:
                return d_colorZones.at(index.row()).color;
            default:
                return QVariant();
        }
    }

    Q_INVOKABLE void appendNewRow()
    {
        beginInsertRows(QModelIndex(), d_colorZones.size(), d_colorZones.size());

        const double start = d_colorZones.empty() ? 0 : d_colorZones.back().end;
        d_colorZones.append({ start, start + 100, Qt::darkGreen });

        endInsertRows();

        emit rowAppended({ start, start + 100, Qt::darkGreen });
    }

    Q_INVOKABLE void insertNewRow(int index)
    {
        if (index < 0 || index > d_colorZones.size())
            return;

        beginInsertRows(QModelIndex(), index, index);

        d_colorZones.insert(index, definitions::ColorZone());

        endInsertRows();

        emit rowInserted(index, definitions::ColorZone());
    }

    Q_INVOKABLE void deleteRow(int index)
    {
        if (index < 0 || index >= d_colorZones.size())
            return;

        beginRemoveRows(QModelIndex(), index, index);

        d_colorZones.removeAt(index);

        endRemoveRows();

        emit rowDeleted(index);
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && index.row() >= 0 && index.row() < d_colorZones.size()) {

            definitions::ColorZone &zone = d_colorZones[index.row()];

            switch (static_cast<ModelRoles>(role))
            {
                case ModelRoles::StartRole:
                {
                    if (!value.canConvert(QMetaType::Double))
                        return false;

                    double val = value.toDouble();

                    if (std::abs(val - zone.start) < 1e-5)
                        return false;

                    qDebug() << "setting start to" << val;
                    zone.start = val;
                    emit dataChanged(index, index, { ModelRoles::StartRole });
                    emit rowModified(index.row(), zone);
                    return true;
                }
                case ModelRoles::EndRole:
                {
                    qDebug() << "setting end";
                    if (!value.canConvert(QMetaType::Double))
                        return false;

                    double val = value.toDouble();

                    if (std::abs(val - zone.end) < 1e-5)
                        return false;

                    zone.end = val;
                    emit dataChanged(index, index, { ModelRoles::EndRole });
                    emit rowModified(index.row(), zone);
                    return true;
                }
                case ModelRoles::ColorRole:
                {
                    qDebug() << "setting color";
                    if (!value.canConvert(QMetaType::QColor))
                        return false;

                    QColor val = value.value<QColor>();

                    if (val == zone.color)
                        return false;

                    zone.color = val;
                    emit dataChanged(index, index, { ModelRoles::ColorRole });
                    emit rowModified(index.row(), zone);
                    return true;
                }
                default:
                    return false;
            }
        }
        return false;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return d_colorZones.size();
    }

signals:

    void rowAppended(const definitions::ColorZone &row);
    void rowInserted(int index, const definitions::ColorZone &row);
    void rowDeleted(int index);
    void rowModified(int index, const definitions::ColorZone &row);

protected:

    QHash<int, QByteArray> roleNames() const
    {
        return { { StartRole, "start" },
                 { EndRole, "end" },
                 { ColorRole, "color" } };
    }

private:

    QList<definitions::ColorZone> d_colorZones;

};

#endif // __COLOR_ZONE_MODEL_HPP__