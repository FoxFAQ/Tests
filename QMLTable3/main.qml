import QtQuick 2.12
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Table")

    C1.TableView
    {
        id: usersTable
        anchors.fill: parent
        model: users

        C1.TableViewColumn
        {
            role: "id"
            title: "User ID"
            width: 100
        }
        C1.TableViewColumn
        {
            role: "name"
            title: "User Name"
            width: 100
        }
        C1.TableViewColumn
        {
            role: "phone"
            title: "Phone Number"
            width: 100
        }
    }
}
