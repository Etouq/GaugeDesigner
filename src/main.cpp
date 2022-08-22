#include "AircraftManager/AircraftManager.hpp"
#include "preview/PreviewManager.hpp"

#include "main.hpp"

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
    app.setWindowIcon(QIcon(":/gaugeDesignerIcon.ico"));

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QColorDialog::setCustomColor(0, QColor(0, 128, 0));
    QColorDialog::setCustomColor(2, QColor(255, 255, 0));
    QColorDialog::setCustomColor(4, QColor(255, 0, 0));
    QColorDialog::setCustomColor(6, QColor(255, 255, 255));
    QColorDialog::setCustomColor(8, QColor(0, 0, 0));


    AircraftManager aircraftManager;
    preview::PreviewManager previewManager;

    QObject::connect(&aircraftManager, &AircraftManager::previewAircraft, &previewManager, &preview::PreviewManager::loadAircraft);

    previewManager.loadAircraft(aircraftManager.getCurrentDefinition());

    setupQml();

    QQmlApplicationEngine engine;

    engine.load("qrc:/main.qml");


    return app.exec();
}
