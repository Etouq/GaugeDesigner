#ifndef __GRAD_MODEL_HPP__
#define __GRAD_MODEL_HPP__

#include "common/definitions/BaseTypes.hpp"

#include <QAbstractListModel>


class GradModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum ModelRoles
    {
        ValueRole = Qt::UserRole + 1,
        BigRole,
        ColorRole
    };

    GradModel(QObject *parent = nullptr)
      : QAbstractListModel(parent)
    {}

    const QList<definitions::GradDef> &getData() const
    {
        return d_grads;
    }

    Q_INVOKABLE void generate(double start, double end, double step)
    {
        if (step < 1e-10 || end - start < 1e-10)
            return;

        beginResetModel();

        d_grads.clear();
        for (; end - start > -1e-10; start += step)
        {
            d_grads.push_back({ start, false, Qt::white });
        }

        endResetModel();

        emit dataGenerated(d_grads);
    }

    void changeData(const QList<definitions::GradDef> &data)
    {
        beginResetModel();

        d_grads = data;

        endResetModel();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (index.row() < 0 || index.row() >= d_grads.size())
            return QVariant();

        switch (static_cast<ModelRoles>(role))
        {
            case ModelRoles::ValueRole:
                return std::round(d_grads.at(index.row()).gradPos * 1e10) * 1e-10;
            case ModelRoles::BigRole:
                return d_grads.at(index.row()).isBig;
            case ModelRoles::ColorRole:
                return d_grads.at(index.row()).gradColor;
            default:
                return QVariant();
        }
    }

    Q_INVOKABLE void appendNewRow()
    {
        beginInsertRows(QModelIndex(), d_grads.size(), d_grads.size());

        const double pos = d_grads.empty() ? 0
                     : d_grads.size() == 1 ? d_grads.last().gradPos
                                           : 2 * d_grads.last().gradPos - d_grads.at(d_grads.size() - 2).gradPos;
        d_grads.append({ pos, false, Qt::white });

        endInsertRows();

        emit rowAppended({ pos, false, Qt::white });
    }

    Q_INVOKABLE void insertNewRow(int index)
    {
        if (index < 0 || index > d_grads.size())
            return;

        beginInsertRows(QModelIndex(), index, index);


        double pos = 0;

        if (d_grads.size() == 1)
            pos = d_grads.front().gradPos;
        else if (d_grads.size() > 1)
        {
            if (index == 0)
                pos = 2 * d_grads.front().gradPos - d_grads.at(1).gradPos;
            else if (index == d_grads.size())
                pos = 2 * d_grads.last().gradPos - d_grads.at(d_grads.size() - 2).gradPos;
            else
                pos = (d_grads.at(index - 1).gradPos + d_grads.at(index).gradPos) / 2;
        }

        d_grads.insert(index, { pos, false, Qt::white });

        endInsertRows();

        emit rowInserted(index, { pos, false, Qt::white });
    }

    Q_INVOKABLE void deleteRow(int index)
    {
        if (index < 0 || index >= d_grads.size())
            return;

        beginRemoveRows(QModelIndex(), index, index);

        d_grads.removeAt(index);

        endRemoveRows();

        emit rowDeleted(index);
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && index.row() >= 0 && index.row() < d_grads.size())
        {

            definitions::GradDef &grad = d_grads[index.row()];

            switch (static_cast<ModelRoles>(role))
            {
                case ModelRoles::ValueRole:
                {
                    if (!value.canConvert(QMetaType::Double))
                        return false;

                    double val = value.toDouble();

                    if (std::abs(val - grad.gradPos) < 1e-5)
                        return false;

                    grad.gradPos = val;
                    emit dataChanged(index, index, { ModelRoles::ValueRole });
                    emit rowModified(index.row(), grad);
                    return true;
                }
                case ModelRoles::BigRole:
                {
                    if (!value.canConvert(QMetaType::Bool))
                        return false;

                    bool val = value.toBool();

                    if (val == grad.isBig)
                        return false;

                    grad.isBig = val;
                    emit dataChanged(index, index, { ModelRoles::BigRole });
                    emit rowModified(index.row(), grad);
                    return true;
                }
                case ModelRoles::ColorRole:
                {
                    if (!value.canConvert(QMetaType::QColor))
                        return false;

                    QColor val = value.value<QColor>();

                    if (val == grad.gradColor)
                        return false;

                    grad.gradColor = val;
                    emit dataChanged(index, index, { ModelRoles::ColorRole });
                    emit rowModified(index.row(), grad);
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
        return d_grads.size();
    }

signals:

    void rowAppended(const definitions::GradDef &row);
    void rowInserted(int index, const definitions::GradDef &row);
    void rowDeleted(int index);
    void rowModified(int index, const definitions::GradDef &row);
    void dataGenerated(const QList<definitions::GradDef> &newData);

protected:

    QHash<int, QByteArray> roleNames() const
    {
        return { { ValueRole, "value" }, { BigRole, "big" }, { ColorRole, "color" } };
    }

private:

    QList<definitions::GradDef> d_grads;
};

#endif  // __GRAD_MODEL_HPP__