import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 400
    height: 600
    visible: true
    title: qsTr("QT Website")

    Column {
        anchors.centerIn: parent
        spacing: 20

        TextField {
            id: inputField
            placeholderText: qsTr("Enter Item here")
        }
        Button {
            text: qsTr("Add Item")
            onClicked: {
                if (inputField.text !== "") {
                    dbManager.addItem(inputField.text);
                    inputField.text = "";
                    itemList.model = dbManager.fetchItems();
                }
            }
        }
        ListView {
            id: itemList
            width: parent.width
            height: 300
            model: []
            delegate: Text {
                text: modelData
            }
        }
    }
}
