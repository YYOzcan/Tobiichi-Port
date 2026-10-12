#pragma once

// Lógica del lanzador: detecta tarjetas gráficas, pantalla y archivos del juego, y arranca ps2EntryRunner con
// las variables de entorno que corresponden a los ajustes elegidos en la interfaz (QML).

#include <QElapsedTimer>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QUrl>
#include <QVariantList>
#include <QVariantMap>

class Lanzador : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool jugando READ jugando NOTIFY jugandoCambiado)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(QString sistema READ sistema CONSTANT)
    Q_PROPERTY(QString carpetaDatos READ carpetaDatos CONSTANT)
    Q_PROPERTY(QString rutaIcono READ rutaIcono CONSTANT)

public:
    explicit Lanzador(QObject *parent = nullptr);
    ~Lanzador() override;

    bool jugando() const;
    QString version() const;
    QString sistema() const;
    QString carpetaDatos() const;
    QString rutaIcono() const;

    // Tarjetas gráficas: [{id, nombre, fabricante, tipo ("integrada"/"dedicada"), predeterminada}].
    Q_INVOKABLE QVariantList tarjetasGraficas() const;
    // Pantalla principal en píxeles físicos: {ancho, alto, hz}.
    Q_INVOKABLE QVariantMap pantalla() const;
    // Rutas encontradas junto al lanzador o en la carpeta del repositorio: {elf, iso, ejecutable}.
    Q_INVOKABLE QVariantMap rutasDetectadas() const;
    // {existe, valido, crc, titulo}: valido si es el ELF de God of War (NTSC-U, SCUS-97399).
    Q_INVOKABLE QVariantMap comprobarJuego(const QString &elf) const;
    // {ok, iso, extraidos}: imagen de disco usada (la elegida o la que buscaría el juego) o archivos extraídos.
    Q_INVOKABLE QVariantMap comprobarDatos(const QString &elf, const QString &iso) const;
    // {existe, ejecutable}
    Q_INVOKABLE QVariantMap comprobarEjecutable(const QString &ruta) const;
    Q_INVOKABLE QString carpetaMemoria(const QString &elf) const;
    Q_INVOKABLE QString rutaDesdeUrl(const QUrl &url) const;
    Q_INVOKABLE QUrl urlDesdeRuta(const QString &ruta) const;

    Q_INVOKABLE bool iniciar(const QVariantMap &ajustes);
    Q_INVOKABLE void detener();
    Q_INVOKABLE void abrirCarpeta(const QString &ruta) const;
    Q_INVOKABLE void abrirRegistro() const;
    // Entrada del menú de aplicaciones (y, si se pide, acceso directo en el escritorio).
    Q_INVOKABLE bool crearAccesoDirecto(bool escritorio) const;
    // Imagen de portada elegida por el usuario: se copia a la carpeta de datos (no depende del original) y se
    // devuelve la ruta de la copia; vacío si no es una imagen legible.
    Q_INVOKABLE QString guardarPortada(const QString &origen) const;
    Q_INVOKABLE void borrarPortada() const;
    // true si la imagen es un recorte (figura sobre fondo transparente): el borde es casi todo transparente.
    Q_INVOKABLE bool esRecorte(const QString &ruta) const;

signals:
    void jugandoCambiado();
    void juegoTerminado(int codigo, bool fallo, int segundos, const QString &resumen);
    void error(const QString &clave, const QString &detalle);

private:
    QString rutaRegistro() const;
    void aplicarTarjeta(QProcessEnvironment &entorno, const QString &id, const QString &ejecutable) const;
    void terminado(int codigo, QProcess::ExitStatus estado);

    QProcess *m_proceso = nullptr;
    QElapsedTimer m_reloj;
};
