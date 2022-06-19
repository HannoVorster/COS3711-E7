QT -= gui
QT += widgets
QT += xml

CONFIG += c++11 console
CONFIG -= app_bundle

RC_ICONS = customers.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        addressvalidator.cpp \
        comboboxdelegate.cpp \
        custinput.cpp \
        customer.cpp \
        customerclient.cpp \
        customertablemodel.cpp \
        custview.cpp \
        doublespinboxdelegate.cpp \
        filereader.cpp \
        filewriter.cpp \
        listreader.cpp \
        listwriter.cpp \
        listxmlreader.cpp \
        listxmlwriter.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    addressvalidator.h \
    comboboxdelegate.h \
    custinput.h \
    customer.h \
    customerclient.h \
    customertablemodel.h \
    custview.h \
    doublespinboxdelegate.h \
    filereader.h \
    filewriter.h \
    listreader.h \
    listwriter.h \
    listxmlreader.h \
    listxmlwriter.h

DISTFILES += \
    Delete.png \
    Images/Delete.png \
    Images/Open_document.png \
    Images/Open_file.png \
    Images/add.png \
    Images/exit.png \
    Images/help.png \
    Images/info.png \
    Images/new.png \
    Images/open.png \
    Images/save.png \
    Images/saveas.png \
    Images/undo.png \
    Images/xml.png \
    Open_document.png \
    Open_file.png \
    add.png \
    customers.ico \
    exit.png \
    help.png \
    info.png \
    new.png \
    open.png \
    save.png \
    saveas.png \
    undo.png \
    xml.png

RESOURCES += \
    customers.qrc
