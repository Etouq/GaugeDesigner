import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

ComboBox {
    id: control
    width: 90
    height: 25
    currentIndex: 0
    property string contentString: ""

    Component {
        id: sectionHeading
        Rectangle {
            width: control.width - 2
            height: 20
            color: "lightsteelblue"

            MouseArea {
                id: hoverArea
                hoverEnabled: true
                anchors.fill: parent
            }

            required property string section

            Text {
                id: sectionText
                x: 5
                width: parent.width - 10
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.family: "Roboto"
                font.bold: true
                text: parent.section
                font.pixelSize: 12
                elide: Text.ElideRight

                ToolTip {
                    parent: sectionText
                    visible: sectionText.truncated && hoverArea.containsMouse
                    text: sectionText.text
                    x: sectionText.width + 10
                    y: (sectionText.height - height) / 2
                    delay: 250
                }
            }
        }

    }


    delegate: ItemDelegate {
        width: control.width - 2
        height: 20
        topPadding: 0
        bottomPadding: 0
        leftPadding: 5
        rightPadding: 5

        contentItem: Text {
            id: delegateText
            width: parent.width - 10
            height: parent.height
            text: longString
            color: "black"
            font.bold: parent.highlighted
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            font.pixelSize: 12

            ToolTip {
                parent: delegateText
                visible: delegateText.truncated && delegateText.parent.hovered
                text: delegateText.text
                x: delegateText.width + 10
                y: (delegateText.height - height) / 2
                delay: 250
            }
        }

        highlighted: control.highlightedIndex == index
    }

    contentItem: Text {
        id: contentText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignVCenter
        text: contentString
        font.pixelSize: 11
        elide: Text.ElideRight

        MouseArea {
            id: contentHoverArea
            hoverEnabled: true
            anchors.fill: parent
        }

        ToolTip {
            parent: contentText
            visible: contentText.truncated && contentHoverArea.containsMouse
            text: contentText.text
            x: contentText.width + 10
            y: (contentText.height - height) / 2
            delay: 250
        }
    }

    background: Rectangle {
            width: 90
            height: 25
            border.color: "#00b4ff"
            border.width: 2
        }


    indicator: Item {
        height: 25
        width: 25
        anchors.right: parent.right
        Rectangle {
            anchors.fill: parent
            color: "#00b4ff"
        }
        Shape {
            transform: Rotation {
                angle: ((control.popup.implicitHeight - 2) / Math.min(control.count * 20, 300)) * 180
                origin.x: 12.5
                origin.y: 12.5
            }

            ShapePath {
                fillColor: "white"
                strokeColor: "transparent"

                PathMove {
                    x: 12.5
                    y: 12.5
                }
                PathLine {
                    relativeX: 5
                    relativeY: -5
                }
                PathLine {
                    relativeX: 5
                    relativeY: 0
                }
                PathLine {
                    relativeX: -10
                    relativeY: 10
                }
                PathLine {
                    relativeX: -10
                    relativeY: -10
                }
                PathLine {
                    relativeX: 5
                    relativeY: 0
                }

            }
        }
    }

    popup: Popup {
        y: control.height
        width: control.width
        implicitHeight: contentItem.implicitHeight + 2

        enter: Transition {
                NumberAnimation { property: "implicitHeight"; from: 0; to: popupContent.implicitHeight + 2; duration: 250 }
            }

        exit: Transition {
            NumberAnimation { property: "implicitHeight"; from: popupContent.implicitHeight + 2; to: 0; duration: 250 }
        }

        padding: 1

        contentItem: ListView {
            id: popupContent
            clip: true
            implicitHeight: Math.min(contentHeight, 300)

            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            section.property: "sect"
            section.criteria: ViewSection.FullString
            section.delegate: sectionHeading

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: "white"
            border.color: "#00b4ff"
        }
    }
}
