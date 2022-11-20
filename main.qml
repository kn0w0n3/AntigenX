import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.12
import QtQuick.Layouts 1.12

//Video Issues - no codecs
//https://stackoverflow.com/questions/40106047/gstreamer-installation-is-missing-a-plug-in
//https://stackoverflow.com/questions/44045842/unable-to-play-video-in-qml
//https://stackoverflow.com/questions/39607522/no-decoder-available-for-type-video-x-h264

//If designer tab is greyed out: https://stackoverflow.com/questions/8494332/design-button-grayed-out-in-qt-creator-for-qml-project
Window {
    id: mainShell
    visible: true
    width: 1280
    height: 720
    maximumWidth: 1280
    maximumHeight: 720
    color: "#00ffffff"
    title: qsTr("AntigenX")

    //All connections can and should go in one place to make them easier to find and work with.
    //I didn't know they could be organized like this. I thought they had to be with the component.
    //Note: The first letter of signal name must be captialized even though it's not in the original signal name. Very small detail.
    //Think you will just capitalize it in the header file? Try it and see what happens lol.
    Connections {
        target: mainController

        onUrlResultsToQml:{
            scanWinScrollViewText.text += urlResut_1
        }

        onUrlScanComplete:{

        }

        onDScanStarted:{
            filesScannedLabel.visible = true
            numFilesScanned.visible = true
        }

        onDScanDone:{
            //scanWinScrollViewText.text +=
        }

        onDNumFilesScanned:{
            numFilesScanned.text = dirNumFilesScaned_X

        }

        onDInfectedFiles:{

        }

        onSScanStarted:{
            filesScannedLabel.visible = true
            numFilesScanned.visible = true
        }

        onSScanDone:{

        }

        onSInfectedFiles:{
            scanWinScrollViewText.text += sInfectedFiles_Y + "\n"
        }

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

    Image {
        id: mainBackground
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/mx-bg-new.png"
        //anchors.fill: parent



        AnimatedImage {
            id: animatedBgLightning
            x: 100
            y: 0
            width: 1180
            height: 720
            visible: false
            source: "images/lightning-and-clouds.gif"
            playing: false
        }
        //Experiment Video
        Video {
            id: videoX
            x: 100
            y: 4
            //width : 1180
            //height : 716
            visible: false
            //source: "/home/voldem0rt/Documents/Qt_Projects/AntigenX-main/video/lightning.avi"
            source: "qrc:/video/lightning.mp4"
            fillMode: VideoOutput.PreserveAspectCrop
            anchors.leftMargin: 100
            clip: false
            anchors.fill: parent


            //layer.enabled: true
            //autoPlay: true
            //play: false
            loops: MediaPlayer.Infinite

            //MouseArea {
            //anchors.fill: parent
            //onClicked: {
            //videoX.play()
            //}
            // }

            focus: true
            //Keys.onSpacePressed: videoX.playbackState == MediaPlayer.PlayingState ? videoX.pause() : videoX.play()
            //Keys.onLeftPressed: videoX.position = videoX.position - 5000
            //Keys.onRightPressed: videoX.position = videoX.position + 5000
        }

        Image {
            id: textLogo
            x: 489
            y: 4
            width: 369
            height: 54
            //width: 0.3 * parent.width
            //height: 0.3 * parent.height
            fillMode: Image.PreserveAspectFit
            source: "images/AntigenX_Logo.png"
            //sourceSize.width: 568
            //sourceSize.height: 102
            //anchors.fill: pare
        }

        Text {
            id: curTimeTxt
            x: 1195
            y: 8
            width: 75
            height: 25
            color: "#ffffff"
            text: qsTr("")
            font.pixelSize: 16
        }

        Text {
            id: curDateTxt
            x: 1192
            y: 29
            width: 89
            height: 25
            color: "#ffffff"
            font.pixelSize: 16
        }


        Image {
            id: antibodyLogo
            x: 1223
            y: 664
            width: 47
            height: 50
            visible: true
            source: "images/antibody.png"
            fillMode: Image.PreserveAspectFit
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
                onPressed: {
                    homeWinBtn.width = 65
                    homeWinBtn.height = 75
                }
                onReleased: {
                    homeWinBtn.width = 68
                    homeWinBtn.height = 78
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
                    if(!vpnWin.visible == false){
                        vpnWin.visible = false
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
                onPressed: {
                    scanWinBtn.width = 65
                    scanWinBtn.height = 75
                }
                onReleased: {
                    scanWinBtn.width = 68
                    scanWinBtn.height = 78
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
                    if(!vpnWin.visible == false){
                        vpnWin.visible = false
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
                onPressed: {
                    toolsWinBtn.width = 65
                    toolsWinBtn.height = 75
                }
                onReleased: {
                    toolsWinBtn.width = 68
                    toolsWinBtn.height = 78
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
                    if(!vpnWin.visible == false){
                        vpnWin.visible = false
                    }
                    toolsWin.visible = true
                    //maincontroller.test2("Hello world")

                }
            }
        }

        Image {
            id: updatesBtnImg
            x: 18
            y: 215
            width: 65
            height: 75
            MouseArea {
                id: updatesBtnMouseArea
                x: 0
                y: 0
                width: 66
                height: 75

                visible: true
                hoverEnabled: true
                onEntered: {
                    updatesBtnImg.width = 68
                    updatesBtnImg.height = 78
                }
                onExited: {
                    updatesBtnImg.width = 65
                    updatesBtnImg.height = 75
                }
                onPressed: {
                    updatesBtnImg.width = 65
                    updatesBtnImg.height = 75
                }
                onReleased: {
                    updatesBtnImg.width = 68
                    updatesBtnImg.height = 78
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
                    if(!vpnWin.visible == false){
                        vpnWin.visible = false
                    }
                    updatesWin.visible = true
                    //maincontroller.test2("Hello world")
                }
            }
            fillMode: Image.PreserveAspectFit
            source: "images/updates_icon.png"
        }

        Image {
            id: vpnBtnImg
            x: 18
            y: 308
            width: 65
            height: 75
            source: "images/vpn-button.png"
            MouseArea {
                id: vpnBtnMouseArea
                x: 0
                y: 0
                width: 65
                height: 75
                hoverEnabled: true
                onEntered: {
                    vpnBtnImg.width = 68
                    vpnBtnImg.height = 78
                }
                onExited: {
                    vpnBtnImg.width = 65
                    vpnBtnImg.height = 75
                }
                onPressed: {
                    vpnBtnImg.width = 65
                    vpnBtnImg.height = 75
                }
                onReleased: {
                    vpnBtnImg.width = 68
                    vpnBtnImg.height = 78
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
                    if(!updatesWin.visible == false){
                        updatesWin.visible = false
                    }
                    vpnWin.visible = true
                    //maincontroller.test2("Hello world")
                }
            }
            fillMode: Image.PreserveAspectFit
        }
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
            curDateTxt.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }

    Rectangle {
        id: vpnWin
        width: 1280
        height: 720
        visible: false
        color: "#00ffffff"

        Image {
            id: image
            x: 494
            y: 130
            width: 360
            height: 376
            source: "images/vpn-transparent-bg.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: labelVpnText
            x: 625
            y: 541
            width: 99
            height: 47
            visible: true
            color: "#ffffff"
            text: qsTr("VPN")
            font.pixelSize: 41
            font.bold: true
            minimumPixelSize: 12
        }
    }

    Timer {
        id: clockTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered:{
            curTimeTxt.text =  Qt.formatTime(new Date(),"hh:mm:ss")
        }
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
                x: 222
                y: 8
                width: 55
                height: 23
                color: "#ffffff"
                text: qsTr("Status:")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: lastUdateLable
                x: 178
                y: 29
                width: 99
                height: 23
                color: "#ffffff"
                text: qsTr("Last Update:")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinStatusTxt
                x: 280
                y: 8
                width: 91
                height: 23
                color: "#35f039"
                text: qsTr("Up to Date")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinLUT
                x: 280
                y: 30
                width: 106
                height: 23
                color: "#ffffff"
                text: qsTr("7/30/22")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinLCLable
                x: 187
                y: 51
                width: 89
                height: 23
                color: "#ffffff"
                text: qsTr("Last Check:")
                font.bold: true
                font.pixelSize: 16
            }

            Text {
                id: updateWinLCT
                x: 280
                y: 52
                width: 89
                height: 20
                color: "#ffffff"
                text: "7/29/22"
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
                    mainController.downloadSignatures() //1
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
            visible: false
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
            x: 271
            y: 147
            width: 706
            height: 323
            color: "#000000"
            border.color: "#ffffff"

            ScrollView {
                id: scanWinScrollView
                x: 8
                y: 8
                width: 690
                height: 307
                clip: true
                ScrollBar.vertical.policy: ScrollBar.AsNeeded
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                TextArea {
                    id: scanWinScrollViewText
                    x: -10
                    y: -6
                    text: qsTr("")
                    clip: true
                    color: "#ffffff"
                }
            }
        }

        Image {
            id: remove_selected_button
            x: 271
            y: 486
            width: 133
            height: 38
            source: "images/rmv-selected-btn.png"
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
                onPressed: {
                    remove_selected_button.width = 133
                    remove_selected_button.height = 38
                }
                onReleased: {
                    remove_selected_button.width = 136
                    remove_selected_button.height = 41
                }
            }
        }

        Image {
            id: remove_all_button
            x: 574
            y: 486
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
                onPressed: {
                    remove_all_button.width = 133
                    remove_all_button.height = 38
                }
                onReleased: {
                    remove_all_button.width = 136
                    remove_all_button.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: abort_scan_button
            x: 844
            y: 486
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
                onPressed: {
                    abort_scan_button.width = 133
                    abort_scan_button.height = 38
                }
                onReleased: {
                    abort_scan_button.width = 136
                    abort_scan_button.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: single_scan_button
            x: 996
            y: 147
            width: 133
            height: 38
            source: "images/scan-file-btn.png"
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
                onPressed: {
                    single_scan_button.width = 133
                    single_scan_button.height = 38
                }
                onReleased: {
                    single_scan_button.width = 136
                    single_scan_button.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: scan_directory_button
            x: 996
            y: 204
            width: 133
            height: 38
            source: "images/scan-dir-btn.png"
            fillMode: Image.PreserveAspectFit

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
                onPressed: {
                    scan_directory_button.width = 133
                    scan_directory_button.height = 38
                }
                onReleased: {
                    scan_directory_button.width = 136
                    scan_directory_button.height = 41
                }
            }
        }

        Image {
            id: fullScanBtnImg
            x: 996
            y: 261
            width: 133
            height: 38
            visible: true
            source: "images/full-scan-button-11-2-22.png"
            MouseArea {
                id: mouseAreaFullScan
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
                hoverEnabled: true
                onEntered: {
                    fullScanBtnImg.width = 136
                    fullScanBtnImg.height = 41
                }
                onExited: {
                    fullScanBtnImg.width = 133
                    fullScanBtnImg.height = 38
                }
                onPressed: {
                    //smart_scan_button.width = 133
                    //smart_scan_button.height = 38
                }
                onReleased: {
                    //smart_scan_button.width = 136
                    //smart_scan_button.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: threatsTextLabel
            x: 612
            y: 126
            width: 58
            height: 22
            color: "#ffffff"
            text: qsTr("Threats")
            visible: true
            font.pixelSize: 16
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
            id: scanStatusTextD
            x: 761
            y: 130
            width: 216
            height: 15
            color: "#ffffff"
            text: qsTr("")
            font.pixelSize: 13
            font.bold: false

        }

        Text {
            id: filesScannedLabel
            x: 271
            y: 130
            width: 80
            height: 15
            visible: false
            color: "#ffffff"
            text: qsTr("Files Scanned: ")
            font.pixelSize: 14
            font.bold: false
        }

        Text {
            id: numFilesScanned
            x: 362
            y: 130
            width: 149
            height: 15
            visible: false
            color: "#ffffff"
            text: qsTr("")
            font.pixelSize: 14
            font.bold: false
        }

        Text {
            id: scanStausTextS
            x: 873
            y: 109
            width: 104
            height: 18
            visible: false
            color: "#0000ff"
            text: qsTr("Scan in progress.......")
            font.pixelSize: 16
            font.bold: true
            minimumPixelSize: 10
        }

        Image {
            id: scanUrlBtnImg
            x: 271
            y: 587
            width: 133
            height: 38
            source: "images/scan-url-button-11-2-22.png"
            MouseArea {
                id: scanUrlMouseArea
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
                hoverEnabled: true
                onEntered: {
                    scanUrlBtnImg.width = 136
                    scanUrlBtnImg.height = 41
                }
                onExited: {
                    scanUrlBtnImg.width = 133
                    scanUrlBtnImg.height = 38
                }
                onClicked: {
                    mainController.checkUrl(urlTextEdit.text);
                    videoX.visible = true
                    videoX.play()
                }
                onPressed: {
                    scanUrlBtnImg.width = 133
                    scanUrlBtnImg.height = 38
                }
                onReleased: {
                    scanUrlBtnImg.width = 136
                    scanUrlBtnImg.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: rectangle1
            x: 418
            y: 595
            width: 559
            height: 23
            color: "#000000"
            border.color: "#ffffff"
        }

        TextEdit {
            id: urlTextEdit
            x: 421
            y: 596
            width: 551
            height: 21
            color: "#ffffff"
            font.pixelSize: 16
            clip: true
        }

        Image {
            id: addSigBtnImg
            x: 996
            y: 432
            width: 133
            height: 38
            visible: true
            source: "images/add-sigl-button-11-2-22.png"
            MouseArea {
                id: mouseAreaAddSig
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
                hoverEnabled: true
                onEntered: {
                    addSigBtnImg.width = 136
                    addSigBtnImg.height = 41
                }
                onExited: {
                    addSigBtnImg.width = 133
                    addSigBtnImg.height = 38
                }
                onPressed: {
                    addSigBtnImg.width = 133
                    addSigBtnImg.height = 38
                }
                onReleased: {
                    addSigBtnImg.width = 136
                    addSigBtnImg.height = 41
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: runSndbxBtnImg
            x: 996
            y: 378
            width: 133
            height: 38
            visible: true
            source: "images/run-sndbx-btn.png"
            MouseArea {
                id: mouseArearunSndbx
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
                hoverEnabled: true
                onEntered: {
                    runSndbxBtnImg.width = 136
                    runSndbxBtnImg.height = 41
                }
                onExited: {
                    runSndbxBtnImg.width = 133
                    runSndbxBtnImg.height = 38
                }
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: quickScanBtnImg
            x: 996
            y: 318
            width: 133
            height: 38
            visible: true
            source: "images/quick-scan-btn.png"
            MouseArea {
                id: mouseAreaQuickScan
                x: 0
                y: 0
                width: 133
                height: 38
                visible: true
                hoverEnabled: true
                onEntered: {
                    quickScanBtnImg.width = 136
                    quickScanBtnImg.height = 41
                }
                onExited: {
                    quickScanBtnImg.width = 133
                    quickScanBtnImg.height = 38
                }
            }
            fillMode: Image.PreserveAspectFit
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
        //Maybe move this
        Component.onCompleted: {
            database.getMainWinDBInfo()
        }

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
                y: 74
                width: 157
                height: 28
                color: "#ffffff"
                text: qsTr("Last Quick Scan:")
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
                text: "Protected"
                font.bold: true
                font.pixelSize: 20
                Connections {
                    target: database
                    onDbmwStatus2Qml: {
                        statusText.text = dbmwStatus2Qml_
                    }
                }
            }

            Text {
                id: lastFullScanText
                x: 285
                y: 52
                width: 142
                height: 28
                color: "#ffffff"
                text: qsTr("11/2/2022")
                font.pixelSize: 20
                font.bold: true
                Connections {
                    target: database
                    onDbmwlastFullScan2Qml: {
                        lastFullScanText.text = bmwlastFullScan2Qml_
                    }
                }
            }

            Text {
                id: lastUpdateText
                x: 285
                y: 136
                width: 142
                height: 28
                color: "#ffffff"
                text: "11/2/2022"
                font.pixelSize: 20
                font.bold: true
                Connections {
                    target: database
                    onDbmwLastUpdate2Qml: {
                        lastUpdateText.text = dbmwLastUpdate2Qml_
                    }
                }
            }

            Text {
                id: threathsFoundText
                x: 285
                y: 163
                width: 148
                height: 28
                color: "#ffffff"
                text: "3"
                font.pixelSize: 20
                font.bold: true
                Connections {
                    target: database
                    onDbmwThreatsFound2Qml: {
                        threathsFoundText.text = dbmwThreatsFound2Qml_
                    }
                }
            }

            Text {
                id: currentThreatsText
                x: 285
                y: 193
                width: 167
                height: 28
                color: "#ffffff"
                text: "0"
                font.bold: true
                font.pixelSize: 20
                Connections {
                    target: database
                    onDbmwCurrentThreats2Qml: {
                        currentThreatsText.text = dbmwCurrentThreats2Qml_
                    }
                }
            }

            Text {
                id: currentReportLabel
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
                y: 106
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
                text: "10/31/2022"
                font.pixelSize: 20
                font.bold: true
                Connections {
                    target: database
                    onDbmwLastSmartScan2Qml: {
                        lastSmartScanText.text = dbmwLastSmartScan2Qml_
                    }
                }
            }

            Text {
                id: lastSingleScanText
                x: 283
                y: 107
                width: 142
                height: 28
                color: "#ffffff"
                text: "10/4/2022"
                font.pixelSize: 20
                font.bold: true
                Connections {
                    target: database
                    onDbmwLastSingleScan2Qml: {
                        lastSingleScanText.text = dbmwLastSingleScan2Qml_
                    }
                }
            }
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















