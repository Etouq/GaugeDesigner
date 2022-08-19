import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15

ComboBox {
    id: control

    Component {
        id: sectionHeading

        Label {
            id: sectionText

            width: control.width
            height: Material.menuItemHeight

            topPadding: Material.menuItemVerticalPadding
            bottomPadding: Material.menuItemVerticalPadding
            leftPadding: 16
            rightPadding: 16

            font.family: "Roboto"
            font.bold: true
            font.pixelSize: 14

            color: Material.foreground
            text: section
            elide: Text.ElideRight

            background: Rectangle {
                color: Material.primary
            }

            MouseArea {
                id: hoverArea
                hoverEnabled: true
                anchors.fill: parent
            }

            ToolTip {
                parent: sectionText
                visible: sectionText.truncated && hoverArea.containsMouse
                text: sectionText.text
                x: sectionText.width + 10
                y: (sectionText.height - height) / 2
                delay: 250
                font.pixelSize: 14
            }

        }

    }

    delegate: MenuItem {
        id: boxDelegate
        width: ListView.view.width
        text: longText
        Material.foreground: control.currentIndex === index ? ListView.view.contentItem.Material.accent : ListView.view.contentItem.Material.foreground
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
        font.pixelSize: 14

        ToolTip {
            parent: boxDelegate
            visible: boxDelegate.hovered
            text: boxDelegate.text
            x: boxDelegate.width + 10
            y: (boxDelegate.height - height) / 2
            delay: 250
            font.pixelSize: 14
        }
    }

    popup: Popup {
        y: control.height - 5
        width: control.width

        height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
        transformOrigin: Item.Top

        topMargin: 12
        bottomMargin: 12

        enter: Transition {
            // grow_fade_in
            NumberAnimation { property: "scale"; from: 0.9; to: 1.0; easing.type: Easing.OutQuint; duration: 220 }
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        exit: Transition {
            // shrink_fade_out
            NumberAnimation { property: "scale"; from: 1.0; to: 0.9; easing.type: Easing.OutQuint; duration: 220 }
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        padding: 0

        contentItem: ListView {
            id: popupContent
            clip: true
            implicitHeight: contentHeight

            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0

            section.property: "unitSection"
            section.criteria: ViewSection.FullString
            section.delegate: sectionHeading

            ScrollBar.vertical: ScrollBar { }
        }

        background: Rectangle {
            radius: 2
            color: Material.dialogColor

            Material.elevation: 8
        }
    }
}
