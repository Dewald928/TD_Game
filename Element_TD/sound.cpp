#include "sound.h"


Sound::Sound(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/sound.png"));

//    //play music
//    theme = new QSound(":/images/sounds/Marimba.wav");
//    theme->play();
//    theme->setLoops(QSound::Infinite);
//    playing = true;

}

void Sound::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (playing == true) {
        theme->stop();
        playing = false;
    }
    else
    {
        //play music
        theme = new QSound(":/images/sounds/Marimba.wav");
        theme->play();
        theme->setLoops(QSound::Infinite);
        playing = true;
    }




}
