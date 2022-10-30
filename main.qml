import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import QtQuick.Controls.Styles 1.4

Window {
    id: mainShell
    visible: true
    width: 1280
    height: 720
    color: "#00ffffff"
    title: qsTr("AntigenX")

    Image {
        id: mainBackground
        x: 0
        y: 0
        width: 1280
        height: 720
        fillMode: Image.PreserveAspectFit
        source: "images/mx-bg-new.png"
    }

    Timer {
        id: dateTimer
        interval: 1000
        repeat: true
        running: true
        property var locale: Qt.locale()
        property date currentDate: new Date()
        property string dateString
        onTriggered:{
            currentDateText.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
            currentDateText1.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
            currentDateText2.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
            currentDateText3.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
            //currentDateText4.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }

    Timer {
        id: clockTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered:{
            currentTimeText.text =  Qt.formatTime(new Date(),"hh:mm:ss")
            currentTimeText1.text =  Qt.formatTime(new Date(),"hh:mm:ss")
            currentTimeText2.text =  Qt.formatTime(new Date(),"hh:mm:ss")
            currentTimeText3.text =  Qt.formatTime(new Date(),"hh:mm:ss")
        }
    }

    Rectangle {
        id: sidepanel
        x: 0
        y: 0
        width: 100
        height: 720
        color: "#14ffffff"
        visible: true

        Image {
            id: homeWinBtn
            x: 18
            y: 26
            width: 65
            height: 75
            source: "images/home_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: homeWinMouseArea
                x: 0
                y: 0
                width: 66
                height: 75
                visible: true
                hoverEnabled: true
                onEntered: {
                    homeWinBtn.width = 68
                    homeWinBtn.height = 78
                }
                onExited: {
                    homeWinBtn.width = 65
                    homeWinBtn.height = 75
                }
                onClicked: {
                    if(!scanWin.visible == false){
                        scanWin.visible = false
                    }
                    if(!toolsWin.visible == false){
                        toolsWin.visible = false
                    }
                    if(!updatesWin.visible == false){
                        updatesWin.visible = false
                    }
                    mainWin.visible = true
                }
            }
        }

        Image {
            id: scanWinBtn
            x: 18
            y: 123
            width: 65
            height: 75
            source: "images/scan_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: scanWinMouseArea
                x: 0
                y: 0
                width: 65
                height: 75
                hoverEnabled: true
                onEntered: {
                    scanWinBtn.width = 68
                    scanWinBtn.height = 78
                }
                onExited: {
                    scanWinBtn.width = 65
                    scanWinBtn.height = 75
                }
                onClicked: {
                    if(!mainWin.visible == false){
                        mainWin.visible = false
                    }
                    if(!updatesWin.visible == false){
                        updatesWin.visible = false
                    }
                    if(!toolsWin.visible == false){
                        toolsWin.visible = false
                    }
                    scanWin.visible = true
                    //maincontroller.test2("Hello world")
                }
            }
        }

        Image {
            id: toolsWinBtn
            x: 18
            y: 624
            width: 65
            height: 75
            source: "images/tools_btn.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: toolsWinMouseArea

                x: 0
                y: 0
                width: 65
                height: 75
                hoverEnabled: true
                onEntered: {
                    toolsWinBtn.width = 68
                    toolsWinBtn.height = 78
                }
                onExited: {
                    toolsWinBtn.width = 65
                    toolsWinBtn.height = 75
                }
                onClicked: {
                    if(!mainWin.visible == false){
                        mainWin.visible = false
                    }
                    if(!scanWin.visible == false){
                        scanWin.visible = false
                    }
                    if(!updatesWin.visible == false){
                        updatesWin.visible = false
                    }
                    toolsWin.visible = true
                    //maincontroller.test2("Hello world")

                }
            }
        }

        Image {
            id: image5
            x: 18
            y: 215
            width: 65
            height: 75
            MouseArea {
                id: mouseArea5
                x: 0
                y: 0
                width: 66
                height: 75

                visible: true
                hoverEnabled: true
                onEntered: {
                    image5.width = 68
                    image5.height = 78
                }
                onExited: {
                    image5.width = 65
                    image5.height = 75
                }
                onClicked: {
                    if(!mainWin.visible == false){
                        mainWin.visible = false
                    }
                    if(!scanWin.visible == false){
                        scanWin.visible = false
                    }
                    if(!toolsWin.visible == false){
                        toolsWin.visible = false
                    }

                    updatesWin.visible = true
                    //maincontroller.test2("Hello world")

                }
            }
            fillMode: Image.PreserveAspectFit
            source: "images/updates_icon.png"
        }
    }

    Image {
        id: textLogo
        x: 489
        y: 4
        width: 369
        height: 54
        fillMode: Image.PreserveAspectFit
        source: "images/AntigenX_Logo.png"
    }
    Rectangle {
        id: updatesWin
        width: 1280
        height: 720
        color: "#00ffffff"
        visible: false

        Rectangle {
            id: updatesDisplayWin
            x: 397
            y: 208
            width: 545
            height: 260
            color: "#000000"
            border.color: "#ffffff"

            Text {
                id: statusLable
                x: 187
                y: 14
                width: 58
                height: 23
                color: "#ffffff"
                text: qsTr("Status:")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: lastUdateLable
                x: 139
                y: 43
                width: 106
                height: 23
                color: "#ffffff"
                text: qsTr("Last Update:")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinStatusTxt
                x: 260
                y: 14
                width: 91
                height: 23
                color: "#35f039"
                text: qsTr("Up to Date")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinLUT
                x: 260
                y: 43
                width: 106
                height: 23
                color: "#ffffff"
                text: qsTr("7/30/2022")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinLCLable
                x: 148
                y: 72
                width: 97
                height: 23
                color: "#ffffff"
                text: qsTr("Last Check:")
                font.bold: true
                font.pixelSize: 16
            }
        }

        Image {
            id: logoSmallCorner
            x: 1223
            y: 664
            width: 47
            height: 50
            source: "images/antibody.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: currentTimeText2
            x: 1188
            y: 8
            width: 75
            height: 25
            color: "#ffffff"
            text: qsTr("15:15:15")
            font.pixelSize: 16
        }

        Text {
            id: currentDateText2
            x: 1187
            y: 29
            width: 89
            height: 25
            color: "#ffffff"
            text: qsTr("7/29/22")
            font.pixelSize: 16
        }

        ProgressBar {
            id: updateProgressBar
            x: 398
            y: 505
            width: 545
            height: 10
            visible: false
            indeterminate: false
            from: 0.00
            to: 415.255187
            enabled: true
            value: 0.00
            onValueChanged: {
                if(updateProgressBar.value == updateProgressBar.to){
                    progressText.visible = false
                    downloadingText.visible = false
                    updateProgressBar.visible = false
                }
            }

            background: Rectangle {
                //implicitWidth: 200
                //implicitHeight: 6
                color: "#000000"
                radius: 9
            }

            contentItem: Item {
                implicitWidth: 545
                implicitHeight: 14

                Rectangle {
                    width: updateProgressBar.visualPosition * parent.width
                    height: parent.height
                    radius: 9
                    color: "#0fa4e9"
                }
            }

            //Note: The first letter of signal name must be captialized even though it's not in the original signal name. Very small detail.
            //Think you will just capitalize it in the header file? Try it and see what happens lol.
            Connections{
                target: mainController
                onBytesReadToQml:{
                    updateProgressBar.value = bRTQML / 1000000
                    progressText.text = bRTQML/ 1000000
                }
                onTotalBytesToQml:{
                    //Currently getting -1 on the total bytes signal
                    //incomingDataSizeText.text = tBTQML
                    //updateProgressBar.to = tBTQML
                }
            }
        }

        Text {
            id: incomingDataSizeText
            x: 948
            y: 424
            width: 87
            height: 20
            color: "#ffffff"
            text: updateProgressBar.to  +  " MB"
            visible: false
            font.pixelSize: 12
        }

        Text {
            id: progressText
            x: 297
            y: 519
            width: 115
            height: 16
            color: "#ffffff"
            text: "test"
            visible: false
            font.pixelSize: 12
        }

        Text {
            id: updateWinLCT
            x: 658
            y: 281
            width: 89
            height: 20
            color: "#ffffff"
            text: "7/29/2022"
            font.bold: true
            font.pixelSize: 16
        }

        Button {
            id: updateBtn
            x: 605
            y: 540
            width: 131
            height: 29
            text: qsTr("Check for Updates")
            visible: false
            //property date currentDate: new Date()
            //property string dateString
            onClicked: {
                //currentDateText4.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
                //mainController.downloadSignatures()
            }
        }

        Image {
            id: checkUpdatesBtn
            x: 603
            y: 535
            width: 133
            height: 38
            visible: true
            fillMode: Image.PreserveAspectFit

            MouseArea {
                id: mouse_area_chk_updts
                x: 0
                y: 0
                width: 133
                height: 38
                hoverEnabled: true
                property var locale: Qt.locale()
                property date currentDate: new Date()
                property string dateString
                onEntered: {
                    checkUpdatesBtn.width = 136
                    checkUpdatesBtn.height = 41
                }
                onExited: {
                    checkUpdatesBtn.width = 133
                    checkUpdatesBtn.height = 38
                }
                onClicked: {
                    updateProgressBar.visible = true
                    progressText.visible = true
                    downloadingText.visible = true
                    mainController.downloadSignatures()
                    updateWinLCT.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat)
                    //TODO: Implement sqlite db to store information
                }
            }
            source: "images/checkUpdatesBtn.png"
        }

        Text {
            id: downloadingText
            x: 296
            y: 502
            width: 96
            height: 16
            color: "#ffffff"
            text: "Downloading...."
            visible: false
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: toolsWin
        width: 1280
        height: 720
        color: "#00ffffff"
        visible: false

        Image {
            id: image4
            x: 606
            y: 316
            width: 95
            height: 88
            source: "images/themes_icon.png"
            MouseArea {
                id: mouseArea4
                x: 0
                y: 0
                width: 95
                height: 88
                visible: true
                hoverEnabled: true
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: image10
            x: 1223
            y: 664
            width: 47
            height: 50
            source: "images/antibody.png"
            fillMode: Image.PreserveAspectFit
            visible: true
        }

        Text {
            id: currentTimeText3
            x: 1188
            y: 8
            width: 75
            height: 25
            color: "#ffffff"
            text: qsTr("15:15:15")
            font.pixelSize: 16
        }

        Text {
            id: currentDateText3
            x: 1187
            y: 29
            width: 89
            height: 25
            color: "#ffffff"
            text: qsTr("7/29/22")
            font.pixelSize: 16
        }
    }

    Rectangle {
        id: scanWin
        x: 0
        y: 0
        width: 1280
        height: 720
        color: "#00ffffff"
        visible: false

        Rectangle {
            id: displayWindow
            x: 397
            y: 208
            width: 545
            height: 260
            color: "#000000"
            border.color: "#ffffff"

            ListView {
                id: listView
                x: 4
                y: 3
                width: 545
                height: 260
                model: ListModel {
                    id:virusAlertModel
                    ListElement {
                        someText: ""
                    }
                }

                //Populating the list model dynaically is having some issues.
                //Janky workaround is to just remove the duplicate first entry.
                delegate: Rectangle{

                    id: iVirusLabel
                    width: 540
                    height: 20
                    border.color: "#000000"
                    color: "#000000"
                    radius: 6

                    Text {
                        id:iVirusText
                        text: someText
                        font.bold: false
                        color: "#ffffff"
                        anchors.verticalCenter: parent.verticalCenter
                        Connections {                    
                            target: mainController
                            property var locale: Qt.locale()
                            property date currentDate: new Date()
                            property string dateString

                            onSendResultToQml: {
                                iVirusText.text = singleScanResult
                                virusAlertModel.append({"someText": singleScanResult})
                            }
                            onScanStarted: {                               
                                filesScannedLabel.visible = true
                                numFilesScanned.visible = true
                                scanStausTextS.visible = true
                                scanStatusTextD.visible = false
                                numFilesScanned.text = ""
                                iVirusText.text = ""
                            }
                            onScanComplete: {
                                scanStatusTextD.visible = true
                                scanStausTextS.visible = false
                                virusAlertModel.remove(0)
                                scanStatusTextD.color = "#45f248"
                                scanStatusTextD.text = "Scan Complete @ " + Qt.formatTime(new Date(),"hh:mm:ss") + " " + currentDate.toLocaleDateString(locale, Locale.ShortFormat)
                            }
                            onFileCountInfo: {
                                numFilesScanned.text = numFilesScanned_
                            }
                        }
                    }
                }
            }
        }

        Image {
            id: remove_selected_button
            x: 409
            y: 502
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
            x: 603
            y: 502
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
            x: 793
            y: 502
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
            x: 989
            y: 208
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
                    mainController.singleFileScan()
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: scan_directory_button
            x: 989
            y: 319
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
                    mainController.scanDirectory()
                    filesScannedLabel.visible = true
                    numFilesScanned.visible = true
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: smart_scan_button
            x: 989
            y: 430
            width: 133
            height: 38
            visible: true
            source: "images/smart_scan_button.png"
            MouseArea {
                id: mouse_area_smart_scan
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
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
            x: 621
            y: 168
            width: 97
            height: 34
            color: "#ffffff"
            text: qsTr("Threats")
            visible: true
            font.pixelSize: 27
            font.underline: true
        }

        Image {
            id: image8
            x: 1223
            y: 664
            width: 47
            height: 50
            source: "images/antibody.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: currentTimeText1
            x: 1188
            y: 8
            width: 75
            height: 25
            color: "#ffffff"
            text: qsTr("15:15:15")
            font.pixelSize: 16
        }

        Text {
            id: currentDateText1
            x: 1187
            y: 29
            width: 89
            height: 25
            color: "#ffffff"
            text: qsTr("7/29/22")
            font.pixelSize: 16
        }

        Text {
            id: scanStatusTextD
            x: 696
            y: 474
            width: 248
            height: 15
            color: "#ffffff"
            text: qsTr("")
            font.pixelSize: 15
            font.bold: false

        }

        Text {
            id: filesScannedLabel
            x: 397
            y: 474
            width: 80
            height: 15
            visible: false
            color: "#ffffff"
            text: qsTr("Files Scanned: ")
            font.pixelSize: 14
            font.bold: true
        }

        Text {
            id: numFilesScanned
            x: 495
            y: 474
            width: 149
            height: 15
            visible: false
            color: "#ffffff"
            text: qsTr("")
            font.pixelSize: 14
            font.bold: true
        }

        Text {
            id: scanStausTextS
            x: 397
            y: 184
            width: 104
            height: 18
            visible: false
            color: "#0000ff"
            text: qsTr("Scan in progress.......")
            font.pixelSize: 16
            font.bold: true
            minimumPixelSize: 10
        }
    }
    Rectangle {
        id: mainWin
        x: 0
        y: 0
        width: 1280
        height: 720
        color: "#00ffffff"
        //color: "#00ffffff"
        visible: true

        Rectangle {
            id: rectangle
            x: 397
            y: 208
            width: 545
            height: 243
            color: "#000000"
            visible: true
            border.color: "#ffffff"

            Text {
                id: statusLabel
                x: 191
                y: 21
                width: 77
                height: 28
                color: "#ffffff"
                text: qsTr("Status:")
                font.bold: true
                font.pixelSize: 20
            }

            Text {
                id: lastSmartScanLabel
                x: 101
                y: 77
                width: 160
                height: 28
                color: "#ffffff"
                text: qsTr("Last Smart Scan:")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: lastUpdateLabel
                x: 139
                y: 134
                width: 133
                height: 28
                color: "#ffffff"
                text: qsTr("Last Update:")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: threathsFoundLabel
                x: 117
                y: 162
                width: 144
                height: 28
                color: "#ffffff"
                text: qsTr("Threats Found:")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: currentThreatLabel
                x: 101
                y: 192
                width: 167
                height: 28
                color: "#ffffff"
                text: qsTr("Current Threats:")
                font.bold: true
                font.pixelSize: 20
            }

            Text {
                id: statusText
                x: 285
                y: 21
                width: 103
                height: 28
                color: "#61f340"
                text: qsTr("Protected")
                font.bold: true
                font.pixelSize: 20
            }

            Text {
                id: lastFullScanText
                x: 285
                y: 52
                width: 142
                height: 28
                color: "#ffffff"
                text: qsTr("07/25/2022")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: lastUpdateText
                x: 285
                y: 136
                width: 142
                height: 28
                color: "#ffffff"
                text: qsTr("07/12/2022")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: threathsFoundText
                x: 285
                y: 163
                width: 148
                height: 28
                color: "#ffffff"
                text: qsTr("126")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: currentThreatsText
                x: 285
                y: 193
                width: 167
                height: 28
                color: "#ffffff"
                text: qsTr("0")
                font.bold: true
                font.pixelSize: 20
            }

            Text {
                id: element5
                x: 202
                y: -28
                width: 142
                height: 23
                color: "#ffffff"
                text: qsTr("Current Report")
                font.bold: true
                font.pixelSize: 19
            }

            Text {
                id: lastSingleScanLabel
                x: 99
                y: 107
                width: 160
                height: 28
                color: "#ffffff"
                text: qsTr("Last Single Scan:")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: lastFullScanLabel
                x: 123
                y: 47
                width: 136
                height: 28
                color: "#ffffff"
                text: qsTr("Last Full Scan:")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: lastSmartScanText
                x: 283
                y: 79
                width: 142
                height: 28
                color: "#ffffff"
                text: qsTr("07/12/2022")
                font.pixelSize: 20
                font.bold: true
            }

            Text {
                id: lastSingleScanText
                x: 283
                y: 107
                width: 142
                height: 28
                color: "#ffffff"
                text: qsTr("07/12/2022")
                font.pixelSize: 20
                font.bold: true
            }
        }

        Text {
            id: currentTimeText
            x: 1188
            y: 8
            width: 75
            height: 25
            color: "#ffffff"
            text: qsTr("15:15:15")
            font.pixelSize: 16
        }

        Text {
            id: currentDateText
            x: 1187
            y: 29
            width: 89
            height: 25
            color: "#ffffff"
            text: qsTr("7/29/22")
            font.pixelSize: 16
        }

        Image {
            id: image7
            x: 1223
            y: 664
            width: 47
            height: 50
            visible: true
            fillMode: Image.PreserveAspectFit
            source: "images/antibody.png"
        }
    }

}//Main Window end
/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
