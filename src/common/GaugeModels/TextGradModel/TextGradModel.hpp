#ifndef __TEXT_GRAD_MODEL_HPP__
#define __TEXT_GRAD_MODEL_HPP__

#include "common/definitions/BaseTypes.hpp"

#include <QAbstractListModel>


class TextGradModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum ModelRoles
    {
        ValueRole = Qt::UserRole + 1,
        TextRole
    };

    TextGradModel(QObject *parent = nullptr)
      : QAbstractListModel(parent)
    {}

    const QList<definitions::TextGradDef> &getData() const
    {
        return d_textGrads;
    }

    Q_INVOKABLE void generate(double start, double end, double step)
    {
        if (step < 1e-10 || end - start < 1e-10)
            return;

        beginResetModel();

        d_textGrads.clear();
        for (; end - start > -1e-10; start += step)
        {
            d_textGrads.push_back({ start, QString::number(start, 'G', 10) });
        }

        endResetModel();

        emit dataGenerated(d_textGrads);
    }

    void changeData(const QList<definitions::TextGradDef> &data)
    {
        beginResetModel();

        d_textGrads = data;

        endResetModel();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (index.row() < 0 || index.row() >= d_textGrads.size())
            return QVariant();

        switch (static_cast<ModelRoles>(role))
        {
            case ModelRoles::ValueRole:
                return std::round(d_textGrads.at(index.row()).textGradPos * 1e10) * 1e-10;
            case ModelRoles::TextRole:
                return d_textGrads.at(index.row()).gradText;
            default:
                return QVariant();
        }
    }

    Q_INVOKABLE void appendNewRow()
    {
        beginInsertRows(QModelIndex(), d_textGrads.size(), d_textGrads.size());

        const double pos = d_textGrads.empty() ? 0
                     : d_textGrads.size() == 1 ? d_textGrads.last().textGradPos
                                           : 2 * d_textGrads.last().textGradPos - d_textGrads.at(d_textGrads.size() - 2).textGradPos;
        d_textGrads.append({ pos, QString::number(pos) });

        endInsertRows();

        emit rowAppended({ pos, QString::number(pos) });
    }

    Q_INVOKABLE void insertNewRow(int index)
    {
        if (index < 0 || index > d_textGrads.size())
            return;

        beginInsertRows(QModelIndex(), index, index);


        double pos = 0;

        if (d_textGrads.size() == 1)
            pos = d_textGrads.front().textGradPos;
        else if (d_textGrads.size() > 1)
        {
            if (index == 0)
                pos = 2 * d_textGrads.front().textGradPos - d_textGrads.at(1).textGradPos;
            else if (index == d_textGrads.size())
                pos = 2 * d_textGrads.last().textGradPos - d_textGrads.at(d_textGrads.size() - 2).textGradPos;
            else
                pos = (d_textGrads.at(index - 1).textGradPos + d_textGrads.at(index).textGradPos) / 2;
        }

        d_textGrads.insert(index, { pos, QString::number(pos) });

        endInsertRows();

        emit rowInserted(index, { pos, QString::number(pos) });
    }

    Q_INVOKABLE void deleteRow(int index)
    {
        if (index < 0 || index >= d_textGrads.size())
            return;

        beginRemoveRows(QModelIndex(), index, index);

        d_textGrads.removeAt(index);

        endRemoveRows();

        emit rowDeleted(index);
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && index.row() >= 0 && index.row() < d_textGrads.size())
        {

            definitions::TextGradDef &grad = d_textGrads[index.row()];

            switch (static_cast<ModelRoles>(role))
            {
                case ModelRoles::ValueRole:
                {
                    if (!value.canConvert(QMetaType::Double))
                        return false;

                    double val = value.toDouble();

                    if (std::abs(val - grad.textGradPos) < 1e-5)
                        return false;

                    grad.textGradPos = val;
                    emit dataChanged(index, index, { ModelRoles::ValueRole });
                    emit rowModified(index.row(), grad);
                    return true;
                }
                case ModelRoles::TextRole:
                {
                    if (!value.canConvert(QMetaType::QString))
                        return false;

                    QString val = value.toString();

                    if (val == grad.gradText)
                        return false;

                    grad.gradText = val;
                    emit dataChanged(index, index, { ModelRoles::TextRole });
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
        return d_textGrads.size();
    }

signals:

    void rowAppended(const definitions::TextGradDef &row);
    void rowInserted(int index, const definitions::TextGradDef &row);
    void rowDeleted(int index);
    void rowModified(int index, const definitions::TextGradDef &row);
    void dataGenerated(const QList<definitions::TextGradDef> &newData);

protected:

    QHash<int, QByteArray> roleNames() const
    {
        return { { ValueRole, "value" }, { TextRole, "text" } };
    }

private:

    QList<definitions::TextGradDef> d_textGrads;
};

#endif  // __TEXT_GRAD_MODEL_HPP__