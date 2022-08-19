import QtQuick 2.15

import Preview 1.0
import Mfd.Engine 1.0

import "../../Elements/Circular" as Circular
import "../../Elements/Vertical" as Vertical
import "../../Elements/Flaps" as Flaps
import "../../Elements/Trims" as Trims
import "../../Elements/Compound" as Compound

Item {

    Circular.Gauge {
        id: firstGauge

        radius: 120
        centerX: 210
        centerY: 135

        titleSize: 30
        unitSize: 30

        valueTextSize: 38

        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        title: PreviewManager.gauge1().getTitle()
        unit: PreviewManager.gauge1().getUnitString()

        gaugeData: PreviewManager.gauge1()
    }

    Circular.Gauge {
        id: secondGauge

        radius: 120
        centerX: 210
        centerY: 322.5

        titleSize: 30
        unitSize: 30

        valueTextSize: 38

        arcWidth: 4
        colorZoneWidth: 8
        gradScaleFactor: 1.3

        title: PreviewManager.gauge2().getTitle()
        unit: PreviewManager.gauge2().getUnitString()

        gaugeData: PreviewManager.gauge2()
    }

    Component {
        id: singleTankComponent
        Vertical.Gauge {
            id: singleTankGauge
            centerX: 105
            yTop: 445.5

            valuePos: 0

            title: singleTankGauge.gaugeData.getTitle()
            unit: singleTankGauge.gaugeData.getUnitString()

            gaugeData: PreviewManager.fuelQtyGauge()
        }
    }

    Component {
        id: doubleTankComponent

        Vertical.DoubleGauge {
            id: doubleTankGauge
            centerX: 105
            yTop: 445.5

            title: doubleTankGauge.gaugeData.getTitle()
            unit: doubleTankGauge.gaugeData.getUnitString()

            gaugeData: PreviewManager.fuelQtyGauge()
        }
    }

    Loader {
        asynchronous: true
        sourceComponent: EngineMisc.hasSingleTank(
                             ) ? singleTankComponent : doubleTankComponent
    }

    Vertical.Gauge {
        id: fuelFlowGauge
        centerX: 315
        yTop: 445.5

        valuePos: 1

        title: fuelFlowGauge.gaugeData.getTitle()
        unit: fuelFlowGauge.gaugeData.getUnitString()

        gaugeData: PreviewManager.fuelFlowGauge()
    }

    Compound.FuelText {
        id: fuelTextGauge
        topBaseline: 622.5
    }

    Vertical.Gauge {
        id: oilTempGauge
        centerX: EngineMisc.hasSecondaryTempGauge() ? 82.5 : 120
        yTop: 730.5

        valuePos: 1

        title: oilTempGauge.gaugeData.getTitle()
        unit: oilTempGauge.gaugeData.getUnitString()

        gaugeData: PreviewManager.oilTempGauge()
    }

    Vertical.Gauge {
        id: oilPressGauge
        centerX: EngineMisc.hasSecondaryTempGauge() ? 337.5 : 300
        yTop: 730.5

        valuePos: 1

        title: oilPressGauge.gaugeData.getTitle()
        unit: oilPressGauge.gaugeData.getUnitString()

        gaugeData: PreviewManager.oilPressGauge()
    }

    Loader {
        asynchronous: true
        active: EngineMisc.hasSecondaryTempGauge()
        sourceComponent: Vertical.Gauge {
            id: secondaryTempGauge
            centerX: 210
            yTop: 730.5

            valuePos: 1

            title: secondaryTempGauge.gaugeData.getTitle()
            unit: secondaryTempGauge.gaugeData.getUnitString()

            gaugeData: PreviewManager.secondaryTempGauge()
        }
    }

    Component {
        id: flapsGauge
        Flaps.Gauge {
            yStart: 909.6
        }
    }

    Component {
        id: flapsSpoilersGauge
        Flaps.SpoilersGauge {
            yStart: 909.6
        }
    }

    Loader {
        active: EngineMisc.hasFlaps()
        asynchronous: true
        sourceComponent: EngineMisc.hasSpoilers(
                             ) ? flapsSpoilersGauge : flapsGauge
    }

    Compound.TrimGauge {
        y: 1020
    }
}
