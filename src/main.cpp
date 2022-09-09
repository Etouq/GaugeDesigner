#include "AircraftManager/AircraftManager.hpp"
#include "preview/PreviewManager.hpp"

#include "main.hpp"

#include <QApplication>
#include <QColorDialog>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
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

    // make sure necessary directories exist
    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Definitions");
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Thumbnails");

    // copy definitions for first time setup
    QDir dir(QDir::currentPath() + "/Definitions Temp");
    if (dir.exists())
    {
        QString dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Flight Display Companion";
        dir.cd("Definitions");

        QFileInfoList files = dir.entryInfoList({"*.fdc"}, QDir::Files | QDir::Readable);

        for (const QFileInfo &fileInfo : files)
        {
            QFile::copy(fileInfo.canonicalFilePath(), dataRoot + "/Definitions/" + fileInfo.fileName());
        }

        dir.cdUp();
        dir.cd("Thumbnails");

        files = dir.entryInfoList({"*.png"}, QDir::Files | QDir::Readable);

        for (const QFileInfo &fileInfo : files)
        {
            QFile::copy(fileInfo.canonicalFilePath(), dataRoot + "/Thumbnails/" + fileInfo.fileName());
        }

        dir.cdUp();

        dir.removeRecursively();

    }


    AircraftManager aircraftManager;
    preview::PreviewManager previewManager;

    QObject::connect(&aircraftManager, &AircraftManager::previewAircraft, &previewManager, &preview::PreviewManager::loadAircraft);

    previewManager.loadAircraft(aircraftManager.getCurrentDefinition());

    setupQml();

    QQmlApplicationEngine engine;

    engine.load("qrc:/main.qml");


    return app.exec();
}
