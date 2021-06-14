#ifndef PLAYWIDGETHARD_H
#define PLAYWIDGETHARD_H

#include "playwidget.h"

class PlayWidgetHard: public PlayWidget
{
    Q_OBJECT

public:
    PlayWidgetHard(const QString & name, const QString & mode, QWidget * parent = nullptr);

    virtual ~PlayWidgetHard();

public slots:
    virtual void tick();
    virtual void next();

protected:
    virtual QPair<QString, QString> generateExpression();

    virtual int getInitialTimeout() const;
};

#endif // PLAYWIDGETHARD_H
