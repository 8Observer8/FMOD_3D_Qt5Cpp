#include "Widget.h"
#include <QtCore/QFile>
#include <QtCore/QDebug>

// https://forum.qt.io/topic/49342/solved-fmod-does-not-play-a-sound-from-qresource/2
// https://cuboidzone.wordpress.com/2013/07/26/tutorial-implementing-fmod/

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    FMOD_System_Create(&m_pSystem, FMOD_VERSION);
    FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, 0);

//    FMOD_System_CreateSound(m_pSystem, "Assets/spell.ogg", FMOD_DEFAULT, 0, &m_pSound);

    QString soundPath(":/Assets/drumloop.wav");
    QFile f(soundPath);
    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Faild to open the file: " << soundPath;
        return;
    }
    QByteArray soundData = f.readAll();

    FMOD_CREATESOUNDEXINFO* exinfo = new FMOD_CREATESOUNDEXINFO();
    exinfo->length = static_cast<unsigned int>(soundData.length());
    exinfo->cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    FMOD_System_CreateSound(m_pSystem, soundData.data(), FMOD_OPENMEMORY | FMOD_3D, exinfo, &m_pSound);

    FMOD_System_PlaySound(m_pSystem, m_pSound, 0, true, &m_channel);

    connect(&m_timer, &QTimer::timeout, this, &Widget::onUpdateLoop);
    m_timer.start(1000.f / 60.f);
    m_elapsedTimer.start();

    // FMOD_Sound_SetMode(m_pSound, FMOD_LOOP_NORMAL); // Default

    QTimer::singleShot(2000, this, &Widget::onStartMusic);
}

Widget::~Widget()
{
}

void Widget::onUpdateLoop()
{
    m_deltaTime = m_elapsedTimer.elapsed() / 1000.f;
    m_elapsedTimer.restart();

    FMOD_VECTOR pos;
    pos.x = 10.f;
    FMOD_System_Set3DListenerAttributes(m_pSystem, 0, &pos, 0, 0 ,0);


    FMOD_System_Update(m_pSystem);
}

void Widget::onStartMusic()
{
    FMOD_Channel_SetPaused(m_channel, false);
//    FMOD_System_PlaySound(m_pSystem, m_pSound, 0, false, 0);
}
