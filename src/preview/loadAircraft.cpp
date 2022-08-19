#include "PreviewManager.hpp"
#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

namespace preview
{

void PreviewManager::loadAircraft(const definitions::AircraftDefinition &aircraft)
{

    d_miscElement.setParameters(aircraft.hasApu,
                                aircraft.hasSecondaryTempGauge,
                                aircraft.hasFlaps,
                                aircraft.hasSpoilers,
                                aircraft.hasElevatorTrim,
                                aircraft.hasRudderTrim,
                                aircraft.hasAileronTrim);

    switch (aircraft.numGauges())
    {
        case 2:
        {
            switch (aircraft.numEngines)
            {
                case 1:
                {
                    d_layoutPath = "SingleEngine/DoubleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 195, 345);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 195, 345);
                    break;
                }
                case 2:
                {
                    d_layoutPath = "DoubleEngine/DoubleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 225, 315);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 225, 315);
                    break;
                }
                case 4:
                {
                    d_layoutPath = "QuadEngine/DoubleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 120);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 120);
                    break;
                }
            }
            break;
        }
        case 3:
        {
            switch (aircraft.numEngines)
            {
                case 1:
                {
                    d_layoutPath = "SingleEngine/TripleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 195, 345);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 225, 315);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 225, 315);
                    break;
                }
                case 2:
                {
                    d_layoutPath = "DoubleEngine/TripleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 225, 315);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 225, 315);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 225, 315);
                    break;
                }
                case 4:
                {
                    d_layoutPath = "QuadEngine/TripleGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 120);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 120);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 120);
                    break;
                }
            }
            break;
        }
        case 4:
        {
            switch (aircraft.numEngines)
            {
                case 1:
                {
                    d_layoutPath = "SingleEngine/QuadGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 225, 315);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 225, 315);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 225, 315);
                    d_gauge4.setGaugeParameters(aircraft.fourthGauge, 225, 315);
                    break;
                }
                case 2:
                {
                    d_layoutPath = "DoubleEngine/QuadGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 225, 315);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 225, 315);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 120);
                    d_gauge4.setGaugeParameters(aircraft.fourthGauge, 120);
                    break;
                }
                case 4:
                {
                    d_layoutPath = "QuadEngine/QuadGauge";
                    d_gauge1.setGaugeParameters(aircraft.firstGauge, 120);
                    d_gauge2.setGaugeParameters(aircraft.secondGauge, 120);
                    d_gauge3.setGaugeParameters(aircraft.thirdGauge, 120);
                    d_gauge4.setGaugeParameters(aircraft.fourthGauge, 120);
                    break;
                }
            }
            break;
        }
    }

    d_fuelQtyGauge.setGaugeParameters(aircraft.fuelQtyGauge, 120);
    d_fuelFlowGauge.setGaugeParameters(aircraft.fuelFlowGauge, 120);
    d_oilTempGauge.setGaugeParameters(aircraft.oilTempGauge, 120);
    d_secondaryTempGauge.setGaugeParameters(aircraft.secondaryTempGauge, 120);
    d_oilPressGauge.setGaugeParameters(aircraft.oilPressGauge, 120);

    emit layoutPathChanged();
}

}  // namespace preview
