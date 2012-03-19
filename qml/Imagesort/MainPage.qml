import QtQuick 1.1
import com.nokia.symbian 1.1
import "Constants.js" as Constants;

Page {
    id: mainPage
    property string testImage: ":/images/rgb.jpg";
    function reloadGridView() {

        // force reload of image
        var i = imgLoader.item;
        if(i) {
            i.model = 0;
            i.model = imageengine.blocksCount;
        }
        else {
            imgLoader.sourceComponent = sortedImageViewComponent;
        }

    }

    Component.onCompleted: {
        imageengine.setImageSource(testImage);
        imageengine.sort();
        reloadGridView();
    }

    Component {
        id: sortedImageViewComponent;
        GridView {
            id: sortedImageView
            width: imageengine.imageWidth();
            height: imageengine.imageHeight();
            cellWidth: imageengine.blockWidth();
            cellHeight: imageengine.blockHeight();
            model: imageengine.blocksCount();
            delegate: imageDelegate;
            anchors.horizontalCenter: parent.horizontalCenter;
        }
    }

    Component {
        id: imageDelegate;
        Image {
            source: "image://sortedimages/"+index;
            cache: false;
        }
    }

    Column {
        width: parent.width;
        height: parent.width;
        spacing: 15;

        Text {
            text: "Original";
            color: "white";
            width: parent.width;
            wrapMode: Text.WordWrap;
            horizontalAlignment: Text.AlignHCenter;
        }

        Image {
            id: original
            source: testImage;
            anchors.horizontalCenter: parent.horizontalCenter;
        }

        Text {
            text: "After sorting in ascending order on red";
            color: "white";
            width: parent.width;
            wrapMode: Text.WordWrap;
            horizontalAlignment: Text.AlignHCenter;
        }

        Loader {
            id: imgLoader;
            anchors.horizontalCenter: parent.horizontalCenter;
        }

        ButtonRow {
            id: algoButtons
            width: parent.width;
            exclusive: true;
            checkedButton: qsort;
            Button {
                id: qsort;
                text: "qSort()"
                onClicked: {
                    imageengine.setAlgorithm(Constants.QSORT);
                    imageengine.sort();
                    reloadGridView();
                }
            }
            Button {
                text: "Quick Sort"
                onClicked: {
                    imageengine.setAlgorithm(Constants.QUICK_SORT);
                    imageengine.sort();
                    reloadGridView();
                }
            }
        }
    }
}
