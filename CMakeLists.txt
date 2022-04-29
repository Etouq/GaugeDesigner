cmake_minimum_required(VERSION 3.23)

project(GaugeDesigner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 Widgets QuickWidgets Svg Network Qml REQUIRED)

set(PROJECT_SOURCES
        AircraftManager/aircraftinterface.cpp
        AircraftManager/aircraftmanager.cpp
        AircraftManager/definitions/aircraftDefinition.cpp
        AircraftManager/definitions/gaugeDefinition.cpp
        AircraftManager/definitions/jetDefinition.cpp
        AircraftManager/definitions/propDefinition.cpp
        AircraftManager/definitions/turbopropDefinition.cpp
        AircraftManager/interfacegetters.cpp
        AircraftManager/interfacesetters.cpp
        AircraftManager/interfaceupdategauges.cpp
        FileManager/aircraftfile.cpp
        GaugeBackend/gaugegetters.cpp
        GaugeBackend/gaugeinterface.cpp
        GaugeBackend/gaugemanager.cpp
        GaugeBackend/gaugesetters.cpp
        Network/NetworkManager/loadclientaircraft.cpp
        Network/NetworkManager/networkmanager.cpp
        Network/NetworkManager/receiveddatafromclient.cpp
        Network/NetworkManager/removeclientaircraft.cpp
        Network/NetworkManager/sendaircrafttoclient.cpp
        Network/networkinterface.cpp
        UnitConverter/converttolongstring.cpp
        UnitConverter/converttoshortstring.cpp
        UnitConverter/unitconverter.cpp
        binaryutil.cpp
        main.cpp
)

set(QML_FILES
        main.qml
        GaugeTab/ColorZoneTable/ColorZoneRow.qml
        GaugeTab/ColorZoneTable/ColorZoneTable.qml
        GaugeTab/GradTable/GradRow.qml
        GaugeTab/GradTable/GradTable.qml
        GaugeTab/TextGradTable/TextGradRow.qml
        GaugeTab/TextGradTable/TextGradTable.qml
        GaugeTab/GaugeTab.qml
        StyledControls/StyledComboBox.qml
        StyledControls/StyledRadioButton.qml
        StyledControls/StyledSwitch.qml
        StyledControls/StyledTabButton.qml
        StyledControls/StyledRadioButtonWithText.qml
        StyledControls/StyledSwitchWithText.qml
        GeneralTab/GeneralTab.qml
        GaugeTabBar.qml
        GaugeToolBar.qml
        StyledControls/StyledToolBarButton.qml
        Dialogs/SingleSelectionDialog.qml
        Dialogs/MultiSelectionDialog.qml
        PreviewPopup/PreviewPopup.qml
        PreviewPopup/gauges/AileronTrimGauge.qml
        PreviewPopup/gauges/CircularGauge.qml
        PreviewPopup/gauges/ElevatorTrimGauge.qml
        PreviewPopup/gauges/FlapsGauge.qml
        PreviewPopup/gauges/FlapsSpoilersGauge.qml
        PreviewPopup/gauges/FuelDoubleTankGauge.qml
        PreviewPopup/gauges/FuelSingleTankGauge.qml
        PreviewPopup/gauges/FuelText.qml
        PreviewPopup/gauges/RudderTrimGauge.qml
        PreviewPopup/gauges/TrimGauges.qml
        PreviewPopup/gauges/VerticalDoubleGauge.qml
        PreviewPopup/gauges/VerticalGauge.qml
        PreviewPopup/JetDouble.qml
        PreviewPopup/JetQuad.qml
        PreviewPopup/JetSingle.qml
        PreviewPopup/PropDouble.qml
        PreviewPopup/PropSingle.qml
        PreviewPopup/TurbopropDouble.qml
        PreviewPopup/TurbopropSingle.qml
        GaugeTab/TopSection.qml
        GeneralTab/AirspeedColors.qml
        GeneralTab/GroupBoxColumn.qml
        GeneralTab/SwitchColumn.qml
)

qt_add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    resources.qrc
)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        ${QML_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Widgets
        Qt6::QuickWidgets
        Qt6::Svg
        Qt6::Network
        Qt6::Qml
)
