#include "aircraftinterface.h"
#include <QFileDialog>
#include <QSettings>

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


