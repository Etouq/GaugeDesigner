#include "AircraftManager.hpp"

#include <algorithm>


void AircraftManager::updateKeys()
{
    d_jetKeys.clear();
    d_propKeys.clear();
    d_turbopropKeys.clear();

    for (const auto &entry : d_definitions)
    {
        switch (entry.second.type)
        {
            case AircraftType::JET:
                d_jetKeys.append(entry.first);
                break;
            case AircraftType::PROP:
                d_propKeys.append(entry.first);
                break;
            case AircraftType::TURBOPROP:
                d_turbopropKeys.append(entry.first);
                break;
            default:
                break;
        }
    }

    std::sort(
      d_jetKeys.begin(),
      d_jetKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });
    std::sort(
      d_propKeys.begin(),
      d_propKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });
    std::sort(
      d_turbopropKeys.begin(),
      d_turbopropKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });
}