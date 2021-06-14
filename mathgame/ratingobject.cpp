#include "ratingobject.h"

RatingObject::RatingObject(QObject *parent):
    QObject(parent),
    highScores()
{
    QString filename =
            QDir::homePath() +
            QDir::separator() +
            QString(".mathgame") +
            QDir::separator() +
            QString("highscores.ini");

    QSettings prefs(filename, QSettings::IniFormat);

    prefs.beginGroup("HighScores");
    int size = prefs.beginReadArray("mode");

    for (int i = 0; i < size; i++) {
        prefs.setArrayIndex(i);

        QString mode = prefs.value("mode").toString();
        QString name = prefs.value("name").toString();
        int value = prefs.value("score").toInt();

        highScores[mode] = qMakePair(name, value);
    }

    prefs.endArray();
    prefs.endGroup();
}

RatingObject::~RatingObject()
{
    QString filename =
            QDir::homePath() +
            QDir::separator() +
            QString(".mathgame") +
            QDir::separator() +
            QString("highscores.ini");

    QSettings prefs(filename, QSettings::IniFormat);

    prefs.beginGroup("HighScores");
    prefs.beginWriteArray("mode");

    int i = 0;
    for (const QString & mode: highScores.keys()) {
        prefs.setArrayIndex(i);
        prefs.setValue("mode", mode);
        prefs.setValue("name", highScores[mode].first);
        prefs.setValue("score", highScores[mode].second);
        i++;
    }

    prefs.endArray();
    prefs.endGroup();
}

QStringList RatingObject::getAllModes() const
{
    return highScores.keys();
}

QString RatingObject::getNameByMode(const QString &mode) const
{
    return highScores[mode].first;
}

int RatingObject::getScoreByMode(const QString &mode) const
{
    return highScores[mode].second;
}

void RatingObject::addScore(const QString &mode, const QString &name, int score)
{
    if (highScores.contains(mode)) {
        if (highScores[mode].second < score) {
            highScores[mode] = qMakePair(name, score);
            emit changed();
        }
    } else {
        highScores[mode] = qMakePair(name, score);
        emit changed();
    }
}
