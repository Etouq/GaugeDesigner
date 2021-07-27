#include "aircraftinterface.h"

#include <QFileDialog>
#include <QFile>
#include <QSettings>
#include "FileManager/aircraftfile.h"

AircraftInterface::AircraftInterface(QObject *parent) : QObject(parent)
{
}

void AircraftInterface::selectImage()
{
    QString lastUsedPath = QSettings().value("lastUsedImagePath", "C:/").toString();
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", lastUsedPath, "Images (*.png *.jpeg *.jpg)");
    if (!fileName.isEmpty())
    {
        QSettings().setValue("lastUsedImagePath", fileName);
        imagePath = fileName;
        emit updateImage();
        emit imageChanged();
    }
}

void AircraftInterface::setAircraft(const AircraftDefinition &aircraft)
{
    def = aircraft;
    imagePath = AircraftFile::getImagePath(def.name);
    if (!QFile(imagePath).exists())
        imagePath = ":/DefaultImage.png";

    emit updateQml();
    emit updateAircraft(aircraft);
    emit updateComplete();
}

void AircraftInterface::saveAircraft()
{
    QImage temp(imagePath);
    AircraftFile::saveAircraftWithImage(def, temp);
    emit aircraftSaved(def);
}

void AircraftInterface::createPreview()
{
    emit loadAircraftPreview(def);
}

void AircraftInterface::newAircraft()
{
    def = AircraftDefinition();
    def.type = AircraftDefinition::AircraftType::PROP;
    PropDefinition propDef;
    propDef.hasEgt = true;
    propDef.usePropRpm = true;
    propDef.maxHp = 100;
    def.currentType.setValue(propDef);
    imagePath = ":/DefaultImage.png";
    emit updateImage();
    emit updateQml();
    emit createDefaultGauges();
    emit updateComplete();
}
