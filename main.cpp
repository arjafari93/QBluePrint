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
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QThread>
#include <QFontDatabase>
#include <QUrl>

#include "src/CBPBoxManager/BPBoxManager.h"
#include "src/CBPStatic/BPStatic.h"
#include "src/CIOTerminal/CInputTerminal/InputTerminal.h"
#include "src/CIOTerminal/COutputTerminal/OutputTerminal.h"
#include "src/COperationBox/Miscellaneous/BlueScriptBox.h"
#include "src/COperationBox/dataSinkBoxes/CSocketClientSink.h"
#include "src/COperationBox/dataSinkBoxes/LineSeriesChartBox.h"
#include "src/COperationBox/dataSinkBoxes/LiveDataXYModel.h"
#include "src/COperationBox/dataSourceBoxes/HTTPGetter.h"

QQmlApplicationEngine* pQmlEngine = nullptr;


static void loadAppFonts()
{
    const QStringList fontResPaths = {
        ":/fonts/calibri.ttf",
        ":/fonts/calibrib.ttf"
    };

    for (const auto& p : fontResPaths) {
        int id = QFontDatabase::addApplicationFont(p);
        if (id < 0) {
            qWarning() << "Failed to load font:" << p;
        }
    }

    const QString family = QFontDatabase::applicationFontFamilies(
                               QFontDatabase::addApplicationFont(":/fonts/calibri.ttf")
                               ).value(0);

    if (!family.isEmpty()) {
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
    qmlRegisterUncreatableType<COperationBox>("org.bluePrintType.OperationBox", 1, 0, "COperationBox", " can not create COperationBox");
    qmlRegisterUncreatableType<CFlowConnectionLine>("org.bluePrintType.FlowConnectionLine", 1, 0, "CFlowConnectionLine", " can not create CFlowConnectionLine");
    qmlRegisterUncreatableType<QAbstractSocket>("org.bluePrintType.AbstractSocket", 1, 0, "QAbstractSocket", " can not create AbstractSocket");
    qmlRegisterUncreatableType<CLineSeriesChartBox>("org.bluePrintType.LineSeriesChartBox", 1, 0, "CLineSeriesChartBox", " can not create LineSeriesChartBox");
    qmlRegisterUncreatableType<CLiveDataXYModel>("org.bluePrintType.LiveDataXYModel", 1, 0, "CLiveDataXYModel", " can not create CLiveDataXYModel");

    qmlRegisterUncreatableType<CSocketClientSink>("org.bluePrintType.SocketClientSink", 1, 0, "CSocketClientSink", " can not create CSocketClientSink");

    qmlRegisterUncreatableType<CIOTerminal>("org.bluePrintType.IOTerminal", 1, 0, "CIOTerminal", " can not create CIOTerminal");
    qmlRegisterUncreatableType<CInputTerminal>("org.bluePrintType.InputTerminal", 1, 0, "CInputTerminal", " can not create CInputTerminal");
    qmlRegisterUncreatableType<COutputTerminal>("org.bluePrintType.OutputTerminal", 1, 0, "COutputTerminal", " can not create COutputTerminal");
    qmlRegisterUncreatableType<CFlowConnectionLine>("org.bluePrintType.FlowConnectionLine", 1, 0, "CFlowConnectionLine", " can not create CFlowConnectionLine");
    qmlRegisterUncreatableType<CBlueScriptBox>("org.bluePrintType.BlueScriptBox", 1, 0, "CBlueScriptBox", " can not create CBlueScriptBox");
    qmlRegisterUncreatableType<CHTTPGetter>("org.bluePrintType.HTTPGetter", 1, 0, "CHTTPGetter", " can not create CHTTPGetter");
    qmlRegisterUncreatableType<CHTTPRawHeaderFormat>("org.bluePrintType.HTTPRawHeaderFormat", 1, 0, "CHTTPRawHeaderFormat", " can not create CHTTPRawHeaderFormat");
    qmlRegisterUncreatableType<CBluePrintPage>("org.bluePrintType.BluePrintPage", 1, 0, "CBluePrintPage", " can not create CBluePrintPage");

    QQmlApplicationEngine engine;
    pQmlEngine = &engine;
    CBPBoxManager* mainAppInstance = CBPBoxManager::getInstance();
    engine.rootContext()->setContextProperty("BPBoxManager", mainAppInstance);

    qmlRegisterType<CBPStatic>("org.bluePrintType.BPStatic", 1, 0, "CBPStatic");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
