#include "playwidgethard.h"

PlayWidgetHard::PlayWidgetHard(const QString & name, const QString & mode, QWidget * parent):
    PlayWidget(name, mode, parent)
{

}

PlayWidgetHard::~PlayWidgetHard()
{

}

void PlayWidgetHard::tick()
{
    decreaseTimeLeft();

    if (!getTimeLeft()) {
        QMessageBox::information(
                    this,
                    tr("Sorry"),
                    tr("Time over"),
                    QMessageBox::Ok);

        stopGame();
    }
}

void PlayWidgetHard::next()
{
    if (checkAnswer()) {
        increaseScore();

        newExpression();
        resetTimeLeft();
    } else {
        pause();
        QMessageBox::information(
                    this,
                    tr("Sorry"),
                    tr("This is a wrong answer"),
                    QMessageBox::Ok);
        resume();
        emit gameOver();
    }

    clearAnswer();
}

QPair<QString, QString> PlayWidgetHard::generateExpression()
{
    int a = getRandom(100, 250);
    int b = getRandom(100, 250);

    return qMakePair(QString("%1 + %2").arg(a).arg(b), QString::number(a + b));
}

int PlayWidgetHard::getInitialTimeout() const
{
    return 10;
}
