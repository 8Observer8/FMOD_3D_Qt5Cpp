#ifndef WIDGET_H
#define WIDGET_H

#include <QtCore/QTimer>
#include <QtCore/QElapsedTimer>
#include <QtWidgets/QWidget>
#include <fmod.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onUpdateLoop();
    void onStartMusic();

private:
    FMOD_SYSTEM *m_pSystem;
    FMOD_SOUND *m_pSound;
    FMOD_CHANNEL *m_channel;

    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime;
    float m_x = 0.f;
};
#endif // WIDGET_H
