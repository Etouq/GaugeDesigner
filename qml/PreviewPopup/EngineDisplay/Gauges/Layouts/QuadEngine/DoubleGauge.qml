import QtQuick 2.15

import Preview 1.0
import Mfd.Engine 1.0

import "../../Elements/Vertical" as Vertical
import "../../Elements/Flaps" as Flaps
import "../../Elements/Trims" as Trims
import "../../Elements/Compound" as Compound

Item {
    id: layoutRoot

    readonly property real bottomGaugesMinWidth: getBottomGaugesMinWidth()

    function getBottomGaugesMinWidth() {
        if (EngineMisc.hasSecondaryTempGauge()) {
            const oilTempGaugeData = PreviewManager.oilTempGauge()
            const secondaryTempGaugeData = PreviewManager.secondaryTempGauge()
            const oilPressGaugeData = PreviewManager.oilPressGauge()

            const oilTempGaugeWidth = 2 * oilTempGaugeData.valueMaxSize(
                                        ) + oilPressGaugeData.unitWidth() - 86
            const oilPressGaugeWidth = 2 * oilPressGaugeData.valueMaxSize(
                                         ) + oilPressGaugeData.unitWidth() - 86
            const secondaryTempGaugeWidth = 2 * secondaryTempGaugeData.valueMaxSize(
                                    ) + secondaryTempGaugeData.unitWidth() - 86

            return Math.max(oilTempGaugeWidth, secondaryTempGaugeWidth,
                            oilPressGaugeWidth)
        }

        return 42 //Math.max(oilTempGaugeWidth, oilPressGaugeWidth)
    }

    Compound.QuadVertGauge {
        id: firstGauge

        yTop: 60
        edgeSpacing: 61.5
        valuePos: 2

        titleSpacing: 20

        gaugeData: PreviewManager.gauge1()
    }

    Compound.QuadVertGauge {
        id: secondGauge

        yTop: 280
        edgeSpacing: 61.5
        valuePos: 2

        titleSpacing: 20

        gaugeData: PreviewManager.gauge2()
    }

    Component {
        id: singleTankComponent
        Vertical.Gauge {
            id: singleTankGauge
            centerX: 105
            yTop: 490

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
            yTop: 490

            title: doubleTankGauge.gaugeData.getTitle()
            unit: doubleTankGauge.gaugeData.getUnitString()

            gaugeData: PreviewManager.fuelQtyGauge()
        }
    }

    Loader {
        asynchronous: true
        sourceComponent: EngineMisc.hasSingleTank() ? singleTankComponent : doubleTankComponent
    }

    Vertical.QuadGauge {
        centerX: 315
        yTop: 490

        title: PreviewManager.fuelFlowGauge().getTitle()
        unit: PreviewManager.fuelFlowGauge().getUnitString()

        gaugeData: PreviewManager.fuelFlowGauge()
    }

    Compound.FuelText {
        id: fuelTextGauge
        topBaseline: 670
    }

    Vertical.QuadGauge {
        id: oilTempGauge
        centerX: 420 / 4 + (layoutRoot.bottomGaugesMinWidth + 96) / 2
                 * (1 - (EngineMisc.hasSecondaryTempGauge() ? 3 : 2) / 2)
        yTop: 760

        title: oilTempGauge.gaugeData.getTitle()
        unit: oilTempGauge.gaugeData.getUnitString()

        minCenterWidth: layoutRoot.bottomGaugesMinWidth

        gaugeData: PreviewManager.oilTempGauge()
    }

    Vertical.QuadGauge {
        id: oilPressGauge
        centerX: 420 - (layoutRoot.bottomGaugesMinWidth + 96) / 2
                 * (1 - (EngineMisc.hasSecondaryTempGauge() ? 3 : 2) / 2) - 420 / 4
        yTop: 760

        title: oilPressGauge.gaugeData.getTitle()
        unit: oilPressGauge.gaugeData.getUnitString()

        minCenterWidth: layoutRoot.bottomGaugesMinWidth

        gaugeData: PreviewManager.oilPressGauge()
    }

    Loader {
        asynchronous: true
        active: EngineMisc.hasSecondaryTempGauge()
        sourceComponent: Vertical.QuadGauge {
            id: secondaryTempGauge
            centerX: 210
            yTop: 760

            title: secondaryTempGauge.gaugeData.getTitle()
            unit: secondaryTempGauge.gaugeData.getUnitString()

            minCenterWidth: layoutRoot.bottomGaugesMinWidth

            gaugeData: PreviewManager.secondaryTempGauge()
        }
    }

    Component {
        id: flapsGauge
        Flaps.Gauge {
            yStart: 950
        }
    }

    Component {
        id: flapsSpoilersGauge
        Flaps.SpoilersGauge {
            yStart: 950
        }
    }

    Loader {
        active: EngineMisc.hasFlaps()
        asynchronous: true
        sourceComponent: EngineMisc.hasSpoilers(
                             ) ? flapsSpoilersGauge : flapsGauge
    }

    Compound.TrimGauge {
        y: 1045
    }
}
