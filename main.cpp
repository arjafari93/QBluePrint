/*
 * Copyright (c) 2025 Alireza Jafari (https://github.com/arjafari93)
 *
 * This software is provided "as is", without warranty of any kind.
 * You may use, modify, and distribute this software, but you MUST keep
 * this copyright notice and credit the original author.
 *
 * Licensed under the BSD 3-Clause License
 */

#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QThread>
#include <QUrl>

#include "BPStatic.h"

QQmlApplicationEngine* pQmlEngine = nullptr;

static void loadAppFonts()
{
    const QStringList fontResPaths = {":/fonts/calibri.ttf", ":/fonts/calibrib.ttf"};

    for (const auto& p : fontResPaths)
    {
        int id = QFontDatabase::addApplicationFont(p);
        if (id < 0)
        {
            qWarning() << "Failed to load font:" << p;
        }
    }

    const QString family = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/fonts/calibri.ttf")).value(0);

    if (!family.isEmpty())
    {
        QFont fnt(family);
        fnt.setPointSize(CBPStatic::defaultFontPointSize());
        QApplication::setFont(fnt);
    }
}

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("QBluePrint");
    QCoreApplication::setApplicationName("QBluePrint");
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setApplicationVersion(QString(APP_VERSION));
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    QQuickStyle::setStyle("Material");

    QApplication app(argc, argv);
    loadAppFonts();

    QQmlApplicationEngine engine;
    pQmlEngine = &engine;

    engine.addImportPath(QCoreApplication::applicationDirPath());
    engine.addImportPath(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("qml"));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
