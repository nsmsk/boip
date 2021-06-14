#ifndef RATINGOBJECT_H
#define RATINGOBJECT_H

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QDir>

class RatingObject : public QObject
{
    Q_OBJECT
public:
    explicit RatingObject(QObject *parent = nullptr);

    ~RatingObject();

    QStringList getAllModes() const;

    QString getNameByMode(const QString & mode) const;
    int getScoreByMode(const QString & mode) const;

    void addScore(const QString & mode, const QString & name, int score);

signals:
    void changed();

private:
    QMap<QString,QPair<QString,int>> highScores;
};

#endif // RATINGOBJECT_H
