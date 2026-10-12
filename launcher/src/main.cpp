// God of War: Tobiichi Launcher. Punto de entrada: fuente del título, icono generado y motor QML.
#include "lanzador.h"

#include <QDir>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QIcon>
#include <QLinearGradient>
#include <QPainter>
#include <QPainterPath>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QTimer>
#include <QRadialGradient>

namespace
{
    // Icono: omega dorada sobre fondo rojo oscuro. Se dibuja con la fuente del título para no depender de
    // archivos de imagen.
    QImage dibujarIcono(const QString &familia, int lado)
    {
        QImage imagen(lado, lado, QImage::Format_ARGB32_Premultiplied);
        imagen.fill(Qt::transparent);
        QPainter p(&imagen);
        p.setRenderHint(QPainter::Antialiasing);
        const qreal s = lado / 256.0;
        const QRectF marco(8 * s, 8 * s, 240 * s, 240 * s);
        QRadialGradient fondo(QPointF(128 * s, 100 * s), 170 * s);
        fondo.setColorAt(0.0, QColor(0x8e, 0x16, 0x12));
        fondo.setColorAt(0.55, QColor(0x45, 0x08, 0x07));
        fondo.setColorAt(1.0, QColor(0x12, 0x03, 0x03));
        QLinearGradient oro(0, 20 * s, 0, 236 * s);
        oro.setColorAt(0.0, QColor(0xf6, 0xdc, 0x96));
        oro.setColorAt(0.5, QColor(0xd2, 0xa5, 0x52));
        oro.setColorAt(1.0, QColor(0x8c, 0x62, 0x22));
        p.setPen(QPen(QBrush(oro), 7 * s));
        p.setBrush(fondo);
        p.drawRoundedRect(marco, 46 * s, 46 * s);

        QFont fuente(familia);
        fuente.setPixelSize(static_cast<int>(176 * s));
        fuente.setWeight(QFont::Black);
        QPainterPath omega;
        omega.addText(0, 0, fuente, QStringLiteral("Ω"));
        const QRectF caja = omega.boundingRect();
        omega.translate(128 * s - caja.center().x(), 132 * s - caja.center().y());
        p.setPen(QPen(QColor(0, 0, 0, 120), 6 * s));
        p.setBrush(Qt::NoBrush);
        p.drawPath(omega.translated(0, 4 * s));
        p.setPen(Qt::NoPen);
        p.setBrush(QBrush(oro));
        p.drawPath(omega);
        return imagen;
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName(QStringLiteral("Tobiichi"));
    QGuiApplication::setApplicationName(QStringLiteral("Launcher"));
    QGuiApplication::setApplicationDisplayName(QStringLiteral("God Of War: Tobiichi Launcher"));
    QGuiApplication::setApplicationVersion(QStringLiteral(TOBIICHI_VERSION));
    QGuiApplication::setDesktopFileName(QStringLiteral("tobiichi-launcher"));
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    QString familiaTitulo = QStringLiteral("serif");
    const int idFuente = QFontDatabase::addApplicationFont(QStringLiteral(":/qt/qml/Tobiichi/recursos/fuentes/Cinzel.ttf"));
    if (idFuente >= 0 && !QFontDatabase::applicationFontFamilies(idFuente).isEmpty())
        familiaTitulo = QFontDatabase::applicationFontFamilies(idFuente).first();

    Lanzador lanzador;
    const QImage icono = dibujarIcono(familiaTitulo, 256);
    QDir().mkpath(lanzador.carpetaDatos());
    icono.save(lanzador.rutaIcono());
    QGuiApplication::setWindowIcon(QIcon(QPixmap::fromImage(icono)));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("lanzador"), &lanzador);
    engine.rootContext()->setContextProperty(QStringLiteral("fuenteTitulo"), familiaTitulo);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, [] { QCoreApplication::exit(1); },
                     Qt::QueuedConnection);
    // Para la documentación y las pruebas: TOBIICHI_CAPTURA=<png> guarda la ventana y sale;
    // TOBIICHI_CAPTURA_PESTANA elige la pestaña.
    const QByteArray captura = qgetenv("TOBIICHI_CAPTURA");
    engine.rootContext()->setContextProperty(QStringLiteral("pestanaInicial"), qEnvironmentVariableIntValue("TOBIICHI_CAPTURA_PESTANA"));
    engine.loadFromModule(QStringLiteral("Tobiichi"), QStringLiteral("Main"));
    if (!captura.isEmpty())
        QTimer::singleShot(3000, &app, [&engine, captura]
        {
            if (auto *ventana = qobject_cast<QQuickWindow *>(engine.rootObjects().value(0)))
                ventana->grabWindow().save(QString::fromLocal8Bit(captura));
            QCoreApplication::quit();
        });
    return app.exec();
}
