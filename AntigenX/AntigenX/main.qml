import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import QtQuick.Controls.Styles 1.4
//import com.company.maincontroller 1.0
Window{
    width: 1280
    height: 720
    visible: true
    color: "#000000"
    property alias updates: updates
    property alias main_logo1: main_logo1
    property alias main_backtground: main_backtground
    property alias text2: text2
    property alias themes_mouse_area: themes_mouse_area
    property alias themes_image: themes_image
    property alias updates_mouse_area: updates_mouse_area
    property alias updates_image: updates_image
    property alias main_logo: main_logo
    property alias tools: tools
    property alias progressBarText: progressBarText
    property alias progressBar: progressBar
    property alias last_update_value: last_update_value
    property alias current_threats_value: current_threats_value
    property alias threats_found_value: threats_found_value
    property alias last_scan_value: last_scan_value
    property alias last_update_text: last_update_text
    property alias current_threats_text: current_threats_text
    property alias threats_found_text: threats_found_text
    property alias last_scan_text: last_scan_text
    property alias status_text: status_text
    property alias status_value: status_value
    property alias current_report_text: current_report_text
    property alias scan: scan
    property alias rectangle1: rectangle1
    property alias single_scan_button: single_scan_button
    property alias mouse_area_single_scan: mouse_area_single_scan
    property alias scan_directory_button: scan_directory_button
    property alias mouse_area_scan_directory: mouse_area_scan_directory
    property alias smart_scan_button: smart_scan_button
    property alias mouse_area_smart_scan: mouse_area_smart_scan
    property alias mouse_area_abort_scan: mouse_area_abort_scan
    property alias abort_scan_button: abort_scan_button
    property alias mouse_area_remove_all: mouse_area_remove_all
    property alias remove_all_button: remove_all_button
    property alias mouse_area_remove_selected: mouse_area_remove_selected
    property alias remove_selected_button: remove_selected_button
    property alias listView: listView
    property alias sidepanel: sidepanel
    property alias rectangle: rectangle
    property alias image: image
    property alias image4: image4
    property alias home: home
    property alias mouseArea3: mouseArea3
    property alias image3: image3
    property alias mouseArea2: mouseArea2
    property alias image2: image2
    property alias image1: image1
    property alias mouseArea1: mouseArea1
    //title: qsTr("AntigenX")

    Image {
        id: main_backtground
        x: 1
        y: 0
        width: 1280
        height: 720
        visible: true
        source: "images/mx-bg-new.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: home
        x: 100
        y: 0
        width: 1180
        height: 720
        color: "#00000000"


        Rectangle {
            id: rectangle1
            x: 331
            y: 198
            width: 520
            height: 320
            visible: false
            color: "#e5000000"
            border.color: "#ffffff"
        }

        Image {
            id: image
            x: 403
            y: 17
            width: 375
            height: 64
            source: "images/AntigenX_Logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: current_report_text
            x: 481
            y: 135
            width: 219
            height: 33
            color: "#ffffff"
            text: qsTr("Current Report")
            font.pixelSize: 30
            font.bold: true
        }

        Text {
            id: status_value
            x: 584
            y: 187
            width: 123
            height: 29
            color: "#64f336"
            text: qsTr("Protected")
            font.pixelSize: 23
        }

        Text {
            id: status_text
            x: 494
            y: 183
            width: 76
            height: 33
            color: "#ffffff"
            text: qsTr("Status:")
            font.pixelSize: 23
        }

        Text {
            id: last_scan_text
            x: 464
            y: 215
            width: 105
            height: 33
            color: "#ffffff"
            text: qsTr("Last Scan:")
            font.pixelSize: 23
        }

        Text {
            id: last_scan_value
            x: 584
            y: 215
            width: 122
            height: 33
            color: "#ffffff"
            text: qsTr("01/01/2021")
            font.pixelSize: 23
        }

        Text {
            id: threats_found_text
            x: 411
            y: 289
            width: 159
            height: 33
            color: "#ffffff"
            text: qsTr("Threats Found:")
            font.pixelSize: 23
        }

        Text {
            id: threats_found_value
            x: 585
            y: 289
            width: 122
            height: 28
            color: "#ffffff"
            text: qsTr("102")
            font.pixelSize: 23
        }

        Text {
            id: current_threats_text
            x: 395
            y: 322
            width: 175
            height: 32
            color: "#ffffff"
            text: qsTr("Current Threats:")
            font.pixelSize: 23
        }

        Text {
            id: current_threats_value
            x: 584
            y: 323
            width: 122
            height: 31
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 23
        }

        Text {
            id: last_update_text
            x: 435
            y: 250
            width: 135
            height: 33
            color: "#ffffff"
            text: qsTr("Last Update:")
            font.pixelSize: 23
        }

        Text {
            id: last_update_value
            x: 585
            y: 251
            width: 122
            height: 27
            color: "#ffffff"
            text: qsTr("01/01/2021")
            font.pixelSize: 23
        }
    }

    Rectangle {
        id: sidepanel
        x: 0
        y: 0
        width: 100
        height: 720
        color: "#14ffffff"

        Image {
            id: image1
            x: 18
            y: 26
            width: 65
            height: 75
            source: "images/home_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea1
                x: 0
                y: 0
                width: 66
                height: 75
                visible: true
                hoverEnabled: true
                onEntered: {
                    image1.width = 68
                    image1.height = 78
                }
                onExited: {
                    image1.width = 65
                    image1.height = 75
                }
                onClicked: {
                    if(!scan.visible == false){
                        scan.visible = false
                    }
                    if(!tools.visible == false){
                        tools.visible = false
                    }
                    if(!updates.visible == false){
                        updates.visible = false
                    }
                    home.visible = true
                }
            }
        }

        Image {
            id: image2
            x: 18
            y: 123
            width: 65
            height: 75
            source: "images/scan_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea2
                x: 0
                y: 0
                width: 65
                height: 75
                hoverEnabled: true
                onEntered: {
                    image2.width = 68
                    image2.height = 78
                }
                onExited: {
                    image2.width = 65
                    image2.height = 75
                }
                onClicked: {
                    if(!home.visible == false){
                        home.visible = false
                    }
                    if(!tools.visible == false){
                        tools.visible = false
                    }
                    if(!updates.visible == false){
                        updates.visible = false
                    }
                    scan.visible = true
                    //maincontroller.test2("Hello world")
                }
            }
        }

        Image {
            id: image3
            x: 18
            y: 221
            width: 65
            height: 75
            source: "images/tools_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouseArea3
                x: 0
                y: 0
                width: 65
                height: 75
                hoverEnabled: true
                onEntered: {
                    image3.width = 68
                    image3.height = 78
                }
                onExited: {
                    image3.width = 65
                    image3.height = 75
                }
                onClicked: {
                    if(!home.visible == false){
                        home.visible = false
                    }
                    if(!scan.visible == false){
                        scan.visible = false
                    }
                    if(!updates.visible == false){
                        updates.visible = false
                    }
                    tools.visible = true
                    //maincontroller.test2("Hello world")

                }
            }
        }
    }

    Rectangle {
        id: scan
        x: 100
        y: 0
        width: 1180
        height: 720
        visible: false
        color: "#00000000"

        Image {
            id: image4
            x: 403
            y: 17
            width: 375
            height: 64
            source: "images/AntigenX_Logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: rectangle
            x: 82
            y: 277
            width: 580
            height: 280
            visible: true
            color: "#cc000000"
            border.color: "#ffffff"

            ObjectModel {
                id: itemModel
                //Rectangle { height: 30; width: 80; color: "red"; text:maincontroller.infectFile}
                //Rectangle { height: 30; width: 80; color: "green" }
                //Rectangle { height: 30; width: 80; color: "blue" }
                Text {
                    text: maincontroller.infectFile
                    font.family: "Helvetica"
                    font.pointSize: 12
                    color: "white"
                }

            }

            ListView {
                id: listView
                x: 8
                y: 8
                width: 564
                height: 264
                visible: true
                clip: true
                model: itemModel

            }

        }

        Image {
            id: remove_selected_button
            x: 82
            y: 581
            width: 133
            height: 38
            source: "images/remove_selected_button.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouse_area_remove_selected
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    remove_selected_button.width = 136
                    remove_selected_button.height = 41
                }
                onExited: {
                    remove_selected_button.width = 133
                    remove_selected_button.height = 38
                }
            }
        }

        Image {
            id: remove_all_button
            x: 306
            y: 581
            width: 133
            height: 38
            visible: true
            source: "images/remove_all_button.png"
            MouseArea {
                id: mouse_area_remove_all
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    remove_all_button.width = 136
                    remove_all_button.height = 41
                }
                onExited: {
                    remove_all_button.width = 133
                    remove_all_button.height = 38
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: abort_scan_button
            x: 529
            y: 581
            width: 133
            height: 38
            source: "images/abort_scan_button.png"
            MouseArea {
                id: mouse_area_abort_scan
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    abort_scan_button.width = 136
                    abort_scan_button.height = 41
                }
                onExited: {
                    abort_scan_button.width = 133
                    abort_scan_button.height = 38
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: single_scan_button
            x: 725
            y: 277
            width: 133
            height: 38
            source: "images/scan_button.png"
            MouseArea {
                id: mouse_area_single_scan
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    single_scan_button.width = 136
                    single_scan_button.height = 41
                }
                onExited: {
                    single_scan_button.width = 133
                    single_scan_button.height = 38
                }
                onClicked: {
                    maincontroller.singleFileScan()
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: scan_directory_button
            x: 725
            y: 398
            width: 133
            height: 38
            source: "images/scan_dir_button.png"
            MouseArea {
                id: mouse_area_scan_directory
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    scan_directory_button.width = 136
                    scan_directory_button.height = 41
                }
                onExited: {
                    scan_directory_button.width = 133
                    scan_directory_button.height = 38
                }
                onClicked: {
                    maincontroller.scanDirectory()
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: smart_scan_button
            x: 725
            y: 519
            width: 133
            height: 38
            source: "images/smart_scan_button.png"
            MouseArea {
                id: mouse_area_smart_scan
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                onEntered: {
                    smart_scan_button.width = 136
                    smart_scan_button.height = 41
                }
                onExited: {
                    smart_scan_button.width = 133
                    smart_scan_button.height = 38
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: text2
            x: 324
            y: 239
            width: 97
            height: 32
            color: "#ffffff"
            text: qsTr("Threats")
            font.pixelSize: 27
        }
    }

    Rectangle {
        id: tools
        x: 100
        y: 0
        width: 1180
        height: 720
        visible: false
        color: "#00000000"

        Image {
            id: main_logo
            x: 403
            y: 17
            width: 375
            height: 64
            source: "images/AntigenX_Logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: updates_image
            x: 419
            y: 291
            width: 125
            height: 125
            source: "images/updates_icon.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: updates_mouse_area
                x: 0
                y: 0
                width: 125
                height: 125
                hoverEnabled: true
                onEntered: {
                    updates_image.height = 128
                    updates_image.width= 128
                }
                onExited: {
                    updates_image.height = 125
                    updates_image.width= 125
                }
                onClicked: {
                    if(!tools.visible == false){
                        tools.visible = false
                    }
                    updates.visible = true
                }
            }
        }

        Image {
            id: themes_image
            x: 607
            y: 291
            width: 125
            height: 125
            source: "images/themes_icon.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: themes_mouse_area
                width: 125
                height: 125
                hoverEnabled: true
                onEntered: {
                    themes_image.height = 128
                    themes_image.width= 128
                }
                onExited: {
                    themes_image.height = 125
                    themes_image.width= 125
                }
            }
        }
    }

    Rectangle {
        id: updates
        x: 104
        y: 2
        width: 1180
        height: 720
        visible: false
        color: "#00000000"
        Image {
            id: main_logo1
            x: 403
            y: 17
            width: 375
            height: 64
            source: "images/AntigenX_Logo.png"
            fillMode: Image.PreserveAspectFit
        }

        ProgressBar {
            background: Rectangle {
                implicitWidth: 580
                implicitHeight: 9
                color: "#ffffff"
                radius: 0
            }

            id: progressBar
            x: 301
            y: 670
            width: 580
            height: 9
            visible: maincontroller.progressBarVisibility
            indeterminate: false
            to: maincontroller.totalBytesValueQml
            from: 0
            value: maincontroller.currentValueQml

            contentItem: Item {
                implicitWidth: 580
                implicitHeight: 9

                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height
                    radius: 0
                    color: "#0fa4e9"
                }
            }
        }

        Switch {
            id: switch1
            x: 69
            y: 174
            width: 120
            height: 42
            text: "off"
        }

        Text {
            id: text1
            x: 69
            y: 134
            width: 228
            height: 27
            color: "#ffffff"
            text: qsTr("Auto update definitions")
            font.pixelSize: 20
            font.bold: true
        }

        Text {
            id: progressBarText
            x: 301
            y: 649
            width: 209
            height: 15
            //visible: maincontroller.progressBarActivity
            color: "#ffffff"
            text: maincontroller.progressBarActivity
            font.pixelSize: 12
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:2;invisible:true}D{i:42}D{i:48}
}
##^##*/
