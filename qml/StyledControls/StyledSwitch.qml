import QtQuick 2.15
import QtQuick.Controls 2.15

Switch {
    id: control
    width: 42
    height: 21

    indicator: Item {
        width: 42
        height: 21
        Rectangle {
            width: 42
            height: 12
            x: 0
            y: 4.5
            radius: 6
            color: control.checked ? "#0085cb" : "#aeaeae"
            Behavior on color {
                ColorAnimation { duration: 100  }
            }

            Rectangle {
                x: control.checked ? parent.width - width : 0
                y: -4.5
                width: 21
                height: 21
                radius: 10.5
                color: control.checked ? "#00b4ff" : "#ffffff"
                Behavior on color {
                    ColorAnimation { duration: 100  }
                }
                Behavior on x {
                    NumberAnimation { duration: 100 }
                }
            }

        }
    }

}
