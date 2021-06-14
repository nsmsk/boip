#include "playwidget.h"

PlayWidget::PlayWidget(const QString & name, const QString & mode, QWidget *parent):
    QWidget(parent)
{
    randomGen = new QRandomGenerator(QDateTime::currentSecsSinceEpoch());

    nameLabel = new QLabel(tr("Player name"), this);
    modeLabel = new QLabel(tr("Game mode"), this);
    timeLabel = new QLabel(tr("Time left"), this);

    nameField = new QLineEdit(name, this);
    modeField = new QLineEdit(mode, this);
    timeField = new QLineEdit(timeoutToString(getInitialTimeout()), this);

    titleLabel = new QLabel(tr("Enter the value of the following expression"), this);
    taskField = new QLineEdit(this);
    answerField = new QLineEdit(this);

    nextButton = new QPushButton(tr("Next  >>"), this);

    nameField->setReadOnly(true);
    modeField->setReadOnly(true);
    timeField->setReadOnly(true);

    taskField->setReadOnly(true);

    QGridLayout * la = new QGridLayout();

    la->addWidget(nameLabel, 0, 0, 1, 1);
    la->addWidget(modeLabel, 0, 1, 1, 1);
    la->addWidget(timeLabel, 0, 2, 1, 1);

    la->addWidget(nameField, 1, 0, 1, 1);
    la->addWidget(modeField, 1, 1, 1, 1);
    la->addWidget(timeField, 1, 2, 1, 1);

    la->addWidget(titleLabel, 2, 0, 1, 3);
    la->addWidget(taskField, 3, 0, 1, 3);
    la->addWidget(answerField, 4, 0, 1, 3);

    la->addWidget(nextButton, 5, 2, 1, 1);

    la->setAlignment(Qt::AlignTop);

    setLayout(la);

    playTimer = new QTimer();

    playTimer->setInterval(1000);

    connect(playTimer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(answerField, SIGNAL(returnPressed()), this, SLOT(next()));
}

PlayWidget::~PlayWidget()
{

}

QString PlayWidget::getMode() const
{
    return modeField->text();
}

QString PlayWidget::getName() const
{
    return nameField->text();
}

int PlayWidget::getScore() const
{
    return currentScore;
}

void PlayWidget::start()
{
    resetTimeLeft();
    currentScore = 0;

    newExpression();

    playTimer->start();
    answerField->setFocus(Qt::OtherFocusReason);
}

void PlayWidget::tick()
{
    decreaseTimeLeft();

    if (!timeLeft) {
        stopGame();
    }
}

void PlayWidget::next()
{
    if (checkAnswer()) {
        increaseScore();

        newExpression();
    } else {
        pause();
        QMessageBox::information(
                    this,
                    tr("Sorry"),
                    tr("This is a wrong answer"),
                    QMessageBox::Ok);
        resume();
    }

    clearAnswer();
}

void PlayWidget::newExpression()
{
    QPair<QString, QString> expr = generateExpression();

    taskField->setText(expr.first);

    currentAnswer = expr.second;
}

QPair<QString, QString> PlayWidget::generateExpression()
{
    if(getRandom(0, 3)) {
        int a, b, c;
        if (getMode() == tr("Easy")) {
            a = getRandom(50, 100);
            b = getRandom(50, 100);
            c = getRandom(25, 50);
        } else {
            a = getRandom(150, 350);
            b = getRandom(150, 350);
            c = getRandom(100, 200);
        }

        return qMakePair(QString("%1 + %2 - %3").arg(a).arg(b).arg(c), QString::number(a + b - c));
    } else {
        int a = getRandom(11, 25);
        int b = getRandom(11, 25);

        return qMakePair(QString("%1 * %2").arg(a).arg(b), QString::number(a * b));
    }
}

int PlayWidget::getInitialTimeout() const
{
    return 60;
}

QString PlayWidget::timeoutToString(int timeout) const
{
    if (timeout >= 0) {
        return QString("%1:%2").arg(timeout / 60, 2, 10, QChar('0')).arg(timeout % 60, 2, 10, QChar('0'));
    } else {
        return QString("00:00");
    }
}

int PlayWidget::getTimeLeft() const
{
    return timeLeft;
}

void PlayWidget::resetTimeLeft()
{
    timeLeft = getInitialTimeout();
    timeField->setText(timeoutToString(timeLeft));
}

void PlayWidget::decreaseTimeLeft()
{
    timeLeft--;
    timeField->setText(timeoutToString(timeLeft));
}

void PlayWidget::stopGame()
{
    playTimer->stop();

    emit gameOver();
}

bool PlayWidget::checkAnswer() const
{
    return currentAnswer == answerField->text();
}

void PlayWidget::increaseScore()
{
    currentScore++;
}

void PlayWidget::clearAnswer()
{
    answerField->clear();
}

int PlayWidget::getRandom(int min, int max)
{
    return randomGen->bounded(min, max);
}

void PlayWidget::pause()
{
    playTimer->stop();
}

void PlayWidget::resume()
{
    playTimer->start();
}
