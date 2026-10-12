import QtQuick
import QtQuick.Particles

// Ascuas que suben desde abajo, como chispas de una hoguera.
Item {
    id: raiz
    property bool activas: true
    property real intensidad: 1.0

    ParticleSystem {
        id: sistema
        running: raiz.activas && raiz.visible
    }

    ImageParticle {
        system: sistema
        groups: ["ascua"]
        source: "qrc:///particleresources/glowdot.png"
        color: "#ff7a2e"
        colorVariation: 0.12
        redVariation: 0.1
        alpha: 0.85
        alphaVariation: 0.3
        entryEffect: ImageParticle.Fade
    }

    ImageParticle {
        system: sistema
        groups: ["brasa"]
        source: "qrc:///particleresources/glowdot.png"
        color: "#ffc070"
        alpha: 0.9
        entryEffect: ImageParticle.Fade
    }

    Emitter {
        system: sistema
        group: "ascua"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 30
        emitRate: 22 * raiz.intensidad
        lifeSpan: 7000
        lifeSpanVariation: 2500
        size: 11
        sizeVariation: 7
        endSize: 2
        velocity: AngleDirection {
            angle: 270
            angleVariation: 14
            magnitude: 42
            magnitudeVariation: 26
        }
        acceleration: PointDirection {
            y: -3
            xVariation: 5
        }
    }

    Emitter {
        system: sistema
        group: "brasa"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 10
        emitRate: 5 * raiz.intensidad
        lifeSpan: 4500
        lifeSpanVariation: 1500
        size: 4
        sizeVariation: 2
        endSize: 1
        velocity: AngleDirection {
            angle: 270
            angleVariation: 25
            magnitude: 70
            magnitudeVariation: 30
        }
    }

    Wander {
        system: sistema
        xVariance: 45
        pace: 30
    }
}
