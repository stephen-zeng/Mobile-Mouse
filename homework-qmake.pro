QT += quick bluetooth core gui

CONFIG += c++11

SOURCES += \
    beserver.cpp \
    getserver.cpp \
    info.cpp \
    main.cpp \

resources.files = \
    Main.qml\
    Client.qml\
    Footer.qml\
    Header.qml\
    Mode.qml\
    Server1.qml\
    Server2.qml\
    Connect.qml

resources.prefix = /
RESOURCES += resources \
    icons.qrc

RC_ICONS = win_icon.ico

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    beserver.h \
    getserver.h \
    info.h

android: {
    SOURCES += \
    getsensor.cpp

    HEADERS += \
    getsensor.h

    QT += sensors
}

macos: {
    QMAKE_INFO_PLIST    = ./macInfo.plist
    SOURCES += \
    mousemove_mac.cpp
    HEADERS += \
    mousemove.h
}
ios {
    OBJECTIVE_SOURCES += \
    getsensor.mm

    SOURCES += \
    getsensor.mm

    HEADERS += \
    getsensor.h

    QMAKE_INFO_PLIST = ./iosInfo.plist
    QMAKE_LFLAGS += -framework CoreMotion
    QMAKE_LFLAGS += -framework Foundation
}

windows: {
    SOURCES += \
    mousemove_win.cpp
    HEADERS += \
    mousemove.h
    LIBS += -lUser32
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/xml/qtprovider_paths.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

