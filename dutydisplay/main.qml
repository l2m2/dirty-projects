import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQml 2.2
import "js/dateutil.js" as DateUtil
import "js/weatherservice.js" as WeatherService

ApplicationWindow {
    id: window
    visible: true
    width: 960
    height: 540
    title: qsTr("Duty Display")

    function getCurrentTimeStr() {
        var currentDate = new Date()
        var ret = DateUtil.format(currentDate, 'yyyy年MM月dd日')
        ret += (" 农历" + DateUtil.getLunarDay())
        ret += (" " + DateUtil.getCnDayOfWeek(currentDate))
        ret += (" " + DateUtil.format(currentDate, 'hh:mm:ss'))
        return ret
    }

    Connections {
        target: downloader
        ignoreUnknownSignals: true
        onFinished: {
            // 读取数据
            console.log("filename: ", filename);
            dutyModel.load(filename);
            var driver = "加载数据...", leader = "加载数据...", police = "加载数据..."

            var currentDate = new Date()
            var day = currentDate.getDate()
            if (dutyModel.leaders.length > 0) {
                leader = dutyModel.leaders[(day - 1) % dutyModel.leaders.length ]
            }
            if (dutyModel.polices.length > 0) {
                police = dutyModel.polices[(day - 1) % dutyModel.polices.length]
            }
            if (dutyModel.drivers.length > 0) {
                driver = dutyModel.drivers[(day - 1) % dutyModel.drivers.length]
            }

            text_driver.text = driver
            text_leader.text = leader
            text_police.text = police

            WeatherService.getWeather(function(result, json) {
                if (json.results !== undefined && json.results.length > 0) {
                    weather.text = json.results[0].weather_data[0].temperature
                            + " "
                            + json.results[0].weather_data[0].weather;
                    img_weather.source = json.results[0].weather_data[0].dayPictureUrl
                }
            })
        }
    }

    Item {
        id: item_main
        anchors.fill: parent

        Image {
            anchors.top:  parent.top
            anchors.bottom: parent.bottom
            width: parent.width
            source: "images/bg.bmp"
        }

        Rectangle {
            id: rect_title
            anchors.top: parent.top
            width: parent.width
            height: parent.height * 0.15
            color: "#88132891"

            Text {
                id: title
                anchors.centerIn: parent
                font.pixelSize: parent.height * 0.7
                font.bold: true
                color: "white"
                text: "惠  州  缉  私"
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: title.right
                anchors.leftMargin: 50
                source: "images/police-emblem.png"
                width: parent.height * 0.8
                height: width
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: title.left
                anchors.rightMargin: 50
                source: "images/customs-emblem.png"
                width: parent.height * 0.8
                height: width
            }
        }
        Item {
            id: item_date
            anchors.top: rect_title.bottom
            width: parent.width
            height: parent.height * 0.1
            Text {
                id: time
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: - parent.width * 0.13
                font.pixelSize: parent.height * 0.5
                color: "#3E2723"
            }
            Timer {
                interval: 1000; running: true; repeat: true
                onTriggered: time.text = getCurrentTimeStr()
            }

            Text {
                id: weather
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: img_weather.left
                anchors.rightMargin: 5
                font.pixelSize: parent.height * 0.5
                color: "#3E2723"
            }
            Image {
                id: img_weather
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
            }
        }
        Item {
            id: item_duty
            anchors.top: item_date.bottom
            width: parent.width
            height: parent.height * 0.12
            Text {
                anchors.centerIn: parent
                font.pixelSize: parent.height * 1.0
                font.bold: true
                text: "今 日 值 班"
            }
        }
        Item {
            id: content1
            anchors.top: item_duty.bottom
            anchors.topMargin: 40
            width: parent.width
            height: parent.height * 0.13
            Text {
                anchors.right: rect1.left
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height * 0.6
                text: "值班局领导:"
            }
            Rectangle {
                id: rect1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: parent.width * 0.13
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.width * 0.2
                radius: 6
                color: "#58DDDDDD"
                Text {
                    id: text_leader
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height * 0.6
                    font.bold: true
                }
            }
        }
        Item {
            id: content2
            anchors.top: content1.bottom
            width: parent.width
            height: parent.height * 0.13
            Text {
                anchors.right: rect2.left
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height * 0.6
                text: "值班民警:"
            }
            Rectangle {
                id: rect2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: parent.width * 0.13
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.width * 0.2
                radius: 6
                color: "#58DDDDDD"
                Text {
                    id: text_police
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height * 0.6
                    font.bold: true
                }
            }
        }
        Item {
            id: content3
            anchors.top: content2.bottom
            width: parent.width
            height: parent.height * 0.13
            Text {
                anchors.right: rect3.left
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height * 0.6
                text: "值班司机:"
            }
            Rectangle {
                id: rect3
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: parent.width * 0.13
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.width * 0.2
                radius: 6
                color: "#58DDDDDD"
                Text {
                    id: text_driver
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height * 0.6
                    font.bold: true
                }
            }
        }
        RollingMessage {
            id: msg
            visible: true
            width: parent.width
            height: parent.height * 0.15
            anchors.bottom: parent.bottom
            message: "聚焦铸魂强警，聚力固本强基，聚神打私主业，争创一流警队。"
        }
        Text {
            anchors.bottom: msg.top
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.pixelSize: 20
            text: dutyModel.debugMessage
        }

        Timer {
            id: main_timer
            triggeredOnStart: true
            interval: debug ? 1000 * 3 : 1000 * 30; running: true; repeat: true
            onTriggered: {
                if (debug) {
                    downloader.startDownload("http://192.168.2.107:9000/duty.csv")
                } else {
                    downloader.startDownload("http://192.168.1.186:9000/duty.csv")
                }
            }
        }
    }
}
