QT += quick quickcontrols2 widgets quickwidgets svg network qml

CONFIG += c++latest
CONFIG -= console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AircraftManager/aircraftinterface.cpp \
        AircraftManager/aircraftmanager.cpp \
        AircraftManager/definitions/aircraftDefinition.cpp \
        AircraftManager/definitions/gaugeDefinition.cpp \
        AircraftManager/definitions/jetDefinition.cpp \
        AircraftManager/definitions/propDefinition.cpp \
        AircraftManager/definitions/turbopropDefinition.cpp \
        FileManager/aircraftfile.cpp \
        GaugeBackend/gaugeinterface.cpp \
        GaugeBackend/gaugemanager.cpp \
        Network/NetworkManager/loadclientaircraft.cpp \
        Network/NetworkManager/networkmanager.cpp \
        Network/NetworkManager/receiveddatafromclient.cpp \
        Network/NetworkManager/removeclientaircraft.cpp \
        Network/NetworkManager/sendaircrafttoclient.cpp \
        UnitConverter/converttolongstring.cpp \
        UnitConverter/converttoshortstring.cpp \
        UnitConverter/unitconverter.cpp \
        binaryutil.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AircraftManager/aircraftinterface.h \
    AircraftManager/aircraftmanager.h \
    AircraftManager/definitions/aircraftDefinition.h \
    AircraftManager/definitions/basetypes.h \
    AircraftManager/definitions/gaugeDefinition.h \
    AircraftManager/definitions/jetDefinition.h \
    AircraftManager/definitions/propDefinition.h \
    AircraftManager/definitions/turbopropDefinition.h \
    FileManager/aircraftfile.h \
    GaugeBackend/gaugeinterface.h \
    GaugeBackend/gaugemanager.h \
    Network/NetworkInterface.h \
    Network/NetworkManager/dataIdentifiers.h \
    Network/NetworkManager/networkmanager.h \
    Network/NetworkManager/networkmanager.ih \
    UnitConverter/unitconverter.h \
    UnitConverter/units.h \
    binaryutil.h
