#include "PreviewManager.hpp"

#include <QQmlEngine>


namespace preview
{

PreviewManager::PreviewManager(QObject *parent)
  : QObject(parent)
{
    QQmlEngine::setObjectOwnership(&d_gauge1, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge2, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge3, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_gauge4, QQmlEngine::CppOwnership);

    QQmlEngine::setObjectOwnership(&d_fuelQtyGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_fuelFlowGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_oilTempGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_secondaryTempGauge, QQmlEngine::CppOwnership);
    QQmlEngine::setObjectOwnership(&d_oilPressGauge, QQmlEngine::CppOwnership);

    QQmlEngine::setObjectOwnership(&d_miscElement, QQmlEngine::CppOwnership);

    qRegisterMetaType<GaugeElement *>("GaugeElement*");

    qmlRegisterSingletonInstance("Mfd.Engine", 1, 0, "EngineMisc", &d_miscElement);
    qmlRegisterUncreatableType<GaugeElement>("Mfd.Engine", 1, 0, "GaugeData", "Bad Boy");
    qmlRegisterSingletonInstance("Preview", 1, 0, "PreviewManager", this);
}

}  // namespace preview
