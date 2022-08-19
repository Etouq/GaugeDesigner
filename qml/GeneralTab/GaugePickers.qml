import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Definition 1.0
import TypeEnums 1.0

RowLayout {

    spacing: 10

    property var allJetTypes: [{ text: "N1", value: SwitchingGaugeType.N1 }, { text: "N2", value: SwitchingGaugeType.N2 }, { text: "Engine Temp", value: SwitchingGaugeType.ENGINE_TEMP }, { text: "Torque", value: SwitchingGaugeType.TORQUE }]

    property var allTurbopropTypes: [{ text: "N1", value: SwitchingGaugeType.N1 }, { text: "N2", value: SwitchingGaugeType.N2 }, { text: "Engine Temp", value: SwitchingGaugeType.ENGINE_TEMP }, { text: "Prop RPM", value: SwitchingGaugeType.PROP_RPM }, { text: "Torque", value: SwitchingGaugeType.TORQUE }]

    property var allPropTypes: [{ text: "RPM", value: SwitchingGaugeType.RPM }, { text: "Prop RPM", value: SwitchingGaugeType.PROP_RPM }, { text: "Manifold Pressure", value: SwitchingGaugeType.MANIFOLD_PRESSURE }, { text: "Power/Load", value: SwitchingGaugeType.POWER }, { text: "Engine Temp", value: SwitchingGaugeType.ENGINE_TEMP }, { text: "Torque", value: SwitchingGaugeType.TORQUE }]

    function updateModels()
    {
        const completeModel = AircraftDefinition.type === AircraftType.JET ? allJetTypes : AircraftDefinition.type === AircraftType.TURBOPROP ? allTurbopropTypes : AircraftDefinition.type === AircraftType.PROP ?  allPropTypes : [{ text: "None", value: SwitchingGaugeType.NONE }];

        const gauge1Model = completeModel.filter((item) => { return item.value !== AircraftDefinition.gauge2Type && item.value !== AircraftDefinition.gauge3Type && item.value !== AircraftDefinition.gauge4Type })
        const gauge2Model = completeModel.filter((item) => { return item.value !== AircraftDefinition.gauge1Type && item.value !== AircraftDefinition.gauge3Type && item.value !== AircraftDefinition.gauge4Type })
        const gauge3Model = completeModel.filter((item) => { return item.value !== AircraftDefinition.gauge1Type && item.value !== AircraftDefinition.gauge2Type && item.value !== AircraftDefinition.gauge4Type }).concat([{ text: "None", value: SwitchingGaugeType.NONE }])
        const gauge4Model = completeModel.filter((item) => { return item.value !== AircraftDefinition.gauge1Type && item.value !== AircraftDefinition.gauge2Type && item.value !== AircraftDefinition.gauge3Type }).concat([{ text: "None", value: SwitchingGaugeType.NONE }])

        gauge1Box.model = gauge1Model;
        gauge2Box.model = gauge2Model;
        gauge3Box.model = gauge3Model;
        gauge4Box.model = gauge4Model;

        gauge1Box.currentIndex = gauge1Model.findIndex((item) => item.value === AircraftDefinition.gauge1Type);
        gauge2Box.currentIndex = gauge2Model.findIndex((item) => item.value === AircraftDefinition.gauge2Type);
        gauge3Box.currentIndex = gauge3Model.findIndex((item) => item.value === AircraftDefinition.gauge3Type);
        gauge4Box.currentIndex = gauge4Model.findIndex((item) => item.value === AircraftDefinition.gauge4Type);
    }

    Component.onCompleted: function() {
        updateModels();
    }

    Text {

        font.family: "Roboto"
        font.pointSize: 11

        color: Material.foreground
        text: "Main Gauges"
    }

    ComboBox {
        id: gauge1Box
        Layout.preferredWidth: 100
        Layout.fillWidth: true

        textRole: "text"
        valueRole: "value"

        model: allAllowedTypes

        onActivated: function(index) {
            AircraftDefinition.gauge1Type = currentValue;
        }
    }

    ComboBox {
        id: gauge2Box
        Layout.preferredWidth: 100
        Layout.fillWidth: true

        textRole: "text"
        valueRole: "value"

        model: allAllowedTypes

        onActivated: function(index) {
            AircraftDefinition.gauge2Type = currentValue;
        }
    }

    ComboBox {
        id: gauge3Box
        Layout.preferredWidth: 100
        Layout.fillWidth: true

        textRole: "text"
        valueRole: "value"

        model: allAllowedTypes

        onActivated: function(index) {
            AircraftDefinition.gauge3Type = currentValue;
        }
    }

    ComboBox {
        id: gauge4Box
        Layout.preferredWidth: 100
        Layout.fillWidth: true

        textRole: "text"
        valueRole: "value"

        model: allAllowedTypes

        enabled: gauge3Box.currentValue !== SwitchingGaugeType.NONE

        onActivated: function(index) {
            AircraftDefinition.gauge4Type = currentValue;
        }
    }

    Connections {
        target: AircraftDefinition
        function onGauge1TypeChanged() {
            updateModels();
        }
        function onGauge2TypeChanged() {
            updateModels();
        }
        function onGauge3TypeChanged() {
            updateModels();
        }
        function onGauge4TypeChanged() {
            updateModels();
        }
        function onTypeChanged() {
            updateModels();
        }
    }
}