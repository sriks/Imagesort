import QtQuick 1.1
import com.nokia.symbian 1.1

PageStackWindow {
    id: window
    showStatusBar: true
    showToolBar: true

    Component.onCompleted: {
        pageStack.push("qrc:/qml/Imagesort/MainPage.qml",{"tools":toolBarLayout});
    }

    ToolBarLayout {
        id: toolBarLayout
        ToolButton {
            flat: true
            iconSource: "toolbar-back"
            onClicked: window.pageStack.depth <= 1 ? Qt.quit() : window.pageStack.pop()
        }
    }
}
