#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T09:53:11
#
#-------------------------------------------------

QT       += core gui network
#RC_ICONS = myico.ico #添加应用程序图标的方法一
RC_FILE = myico.rc #添加应用程序图标的方法二，在当前目录下添加*.rc文件，文件中采用固定格式，最后的文件名与当前路径下的图标文件名保持一致

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        timeclient.cpp

HEADERS  += timeclient.h



