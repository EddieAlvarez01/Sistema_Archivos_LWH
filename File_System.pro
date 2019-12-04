TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    command.cpp \
    exec.cpp \
    fdisk.cpp \
    mount.cpp \
    rep.cpp \
    rmdisk.cpp \
    unmount.cpp \
    mkfs.cpp \
    login.cpp \
    logout.cpp \
    rmgrp.cpp \
    mkgrp.cpp \
    mkusr.cpp \
    rmusr.cpp \
    chmod.cpp \
    mkfile.cpp \
    mkdir.cpp \
    scanner.cpp \
    parser.cpp \
    mkdisk.cpp \
    listmount.cpp \
    nodelist.cpp \
    partition.cpp \
    mbr.cpp \
    ebr.cpp \
    plotter.cpp

DISTFILES += \
    lexico.l \
    parser.yy

HEADERS += \
    command.h \
    exec.h \
    fdisk.h \
    mount.h \
    rep.h \
    rmdisk.h \
    unmount.h \
    mkfs.h \
    login.h \
    logout.h \
    rmgrp.h \
    mkgrp.h \
    mkusr.h \
    rmusr.h \
    chmod.h \
    mkfile.h \
    mkdir.h \
    scanner.h \
    parser.h \
    mkdisk.h \
    listmount.h \
    nodelist.h \
    partition.h \
    mbr.h \
    ebr.h \
    plotter.h
