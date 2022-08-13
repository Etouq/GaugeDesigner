#include "UnitModel.hpp"

QVariant UnitModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= d_data.size())
        return QVariant();

    switch (static_cast<UnitRoles>(role))
    {
        case UnitRoles::UnitIdRole:
            return d_data.at(index.row()).unitId;
        case UnitRoles::LongTextRole:
            return d_data.at(index.row()).longText;
        case UnitRoles::ShortTextRole:
            return d_data.at(index.row()).shortText;
        case UnitRoles::SectionRole:
            return d_data.at(index.row()).unitSection;
        default:
            return QVariant();
    }
}