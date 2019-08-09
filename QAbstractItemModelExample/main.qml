import QtQuick 2.12
import TableModel 0.1
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Kvant Table")

    TableView {
          anchors.fill: parent
          columnSpacing: 1
          rowSpacing: 1
          clip: true

          model: TableModel {}

          delegate: Rectangle {
              implicitWidth: 200
              implicitHeight: 30
              border.color: "black"
              border.width: 1
              color: (heading==true)?"lightgrey":"white"

              TableView.onPooled: console.log(tabledata + " pooled")
              TableView.onReused: console.log(tabledata + " reused")
              Text {
                  text: tabledata
                  anchors.centerIn: parent
              }
          }
      }
}
