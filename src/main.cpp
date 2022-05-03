#include "aircraftmanager/aircraftinterface/aircraftinterface.hpp"
#include "aircraftmanager/aircraftmanager/aircraftmanager.hpp"
#include "filemanager/aircraftfile/aircraftfile.hpp"
#include "gauges/gaugemanager/gaugemanager.hpp"
#include "network/networkmanager/networkmanager.hpp"
#include "network/networkinterface/networkinterface.hpp"
#include "util/unitconverter/unitconverter.hpp"

#include <QApplication>
#include <QColorDialog>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QtQml>
#include <QLocale>


int main(int argc, char *argv[])
{

    QLocale::setDefault(QLocale::c());
    QApplication app(argc, argv);
    app.setOrganizationName("MKootstra");
    app.setApplicationName("gaugeDesigner");
    app.setApplicationDisplayName("Gauge Designer");
    app.setWindowIcon(QIcon("qrc:/DefaultImage.png"));
    QColorDialog::setCustomColor(0, QColor(0, 128, 0));
    QColorDialog::setCustomColor(2, QColor(255, 255, 0));
    QColorDialog::setCustomColor(4, QColor(255, 0, 0));
    QColorDialog::setCustomColor(6, QColor(255, 255, 255));
    QColorDialog::setCustomColor(8, QColor(0, 0, 0));

    AircraftFile::init();


    UnitConverter unitConverter;
    GaugeManager gaugeInterface;
    AircraftInterface planeInterface;
    AircraftManager aircraftManager;
    NetworkManager netManager;
    NetworkInterface netInterface;

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);
    QQmlApplicationEngine engine;

    gaugeInterface.addGaugesToContext(engine.rootContext());
    gaugeInterface.connectGaugeSignals(planeInterface);

    engine.rootContext()->setContextProperty("converter", &unitConverter);
    engine.rootContext()->setContextProperty("aircraftInterface", &planeInterface);
    engine.rootContext()->setContextProperty("aircraftManager", &aircraftManager);
    engine.rootContext()->setContextProperty("gaugeInterface", &gaugeInterface);
    engine.rootContext()->setContextProperty("netInterface", &netInterface);

    engine.load("qrc:/main.qml");

    QObject::connect(&planeInterface,
                     &AircraftInterface::aircraftSaved,
                     &aircraftManager,
                     &AircraftManager::setAircraft);
    QObject::connect(&aircraftManager,
                     &AircraftManager::changeAircraft,
                     &planeInterface,
                     &AircraftInterface::setAircraft);
    QObject::connect(&planeInterface,
                     &AircraftInterface::updateAircraft,
                     &gaugeInterface,
                     &GaugeManager::changeAircraft);
    QObject::connect(&planeInterface,
                     &AircraftInterface::createDefaultGauges,
                     &gaugeInterface,
                     &GaugeManager::createDefaults);
    QObject::connect(&planeInterface,
                     &AircraftInterface::loadAircraftPreview,
                     &gaugeInterface,
                     &GaugeManager::loadAircraftPreview);

    QObject::connect(&netManager,
                     &NetworkManager::connectedChanged,
                     &netInterface,
                     &NetworkInterface::setConnectedState);
    QObject::connect(&netManager,
                     &NetworkManager::versionError,
                     &netInterface,
                     &NetworkInterface::showErrorPopup);
    QObject::connect(&netManager,
                     &NetworkManager::serverInitFinished,
                     &netInterface,
                     &NetworkInterface::setAddressAndPort);
    QObject::connect(&netInterface,
                     &NetworkInterface::removeClientAircraft,
                     &netManager,
                     &NetworkManager::removeClientAircraft);
    QObject::connect(&netInterface,
                     &NetworkInterface::loadClientAircraft,
                     &netManager,
                     &NetworkManager::loadClientAircraft);
    QObject::connect(&aircraftManager,
                     &AircraftManager::sendAircraftToClient,
                     &netManager,
                     &NetworkManager::sendAircraftToClient);
    QObject::connect(&netManager,
                     &NetworkManager::receivedAircraft,
                     &aircraftManager,
                     &AircraftManager::setAircraft);
    QObject::connect(&netManager,
                     &NetworkManager::receivedFileList,
                     &aircraftManager,
                     &AircraftManager::setClientKeys);


    netManager.init();

    planeInterface.newAircraft();


    return app.exec();
}
