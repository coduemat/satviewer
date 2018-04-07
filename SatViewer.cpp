// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * SatViewer.cpp
 *
 *  Created on: 05.05.2009
 *      Author: Ivan Ryazanov
 */

#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include "SWindow.h"

void copyDefault() {
    QString home = QDir::home().path() + QDir::separator() + "satviewer" + QDir::separator();
    if (QDir(home).exists()) {
        qWarning("profile is exists");
        return;
    }
    QDir().mkpath(home);
    QString profile = QDir(qApp->applicationDirPath() + QDir::separator() + "profile").path();
    QDirIterator it(profile, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        if (it.fileInfo().isDir()) {
            if (!it.fileInfo().dir().mkdir(home + QDir(profile).relativeFilePath(it.fileInfo().filePath()))) {
                qWarning("Error mkdir:");
                qWarning(it.fileInfo().filePath().toLocal8Bit().data());
            } else {
                qWarning("mkdir:");
                qWarning(it.fileInfo().filePath().toLocal8Bit().data());
            }
        }

        if (it.fileInfo().isFile()) {
            if (!QFile(it.filePath()).copy(QString(home + QDir(profile).relativeFilePath(it.fileInfo().filePath())))) {
                qWarning("Error copy:");
                qWarning(it.fileInfo().filePath().toLocal8Bit().data());
            } else {
                qWarning("copy:");
                qWarning(it.fileInfo().filePath().toLocal8Bit().data());
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    format.setVersion(3, 3);
//    qWarning("%d.%d", format.majorVersion(), format.minorVersion());
//    QSurfaceFormat::setDefaultFormat(format);

    copyDefault();
    SWindow wndMain;
    wndMain.show();
    return app.exec();
}
