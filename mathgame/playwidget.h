#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDateTime>

/**
 * @brief Вкладка, на которой собственно ведется игра
 */
class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(const QString & name, const QString & mode, QWidget *parent = nullptr);

    virtual ~PlayWidget();

    QString getMode() const;
    QString getName() const;
    int getScore() const;

public slots:
    virtual void start();
    virtual void tick();
    virtual void next();

signals:
    void gameOver();

protected:
    void newExpression();

    virtual QPair<QString, QString> generateExpression();

    virtual int getInitialTimeout() const;

    QString timeoutToString(int timeout) const;

    int getTimeLeft() const;
    void resetTimeLeft();
    void decreaseTimeLeft();
    void stopGame();
    bool checkAnswer() const;
    void increaseScore();
    void clearAnswer();
    int getRandom(int min, int max);
    void pause();
    void resume();

private:
    QLabel * nameLabel;
    QLabel * modeLabel;
    QLabel * timeLabel;

    QLineEdit * nameField;
    QLineEdit * modeField;
    QLineEdit * timeField;

    QLabel * titleLabel;
    QLineEdit * taskField;
    QLineEdit * answerField;

    QPushButton * nextButton;

    QTimer * playTimer;

    int timeLeft;
    int currentScore;
    QString currentAnswer;

    QRandomGenerator * randomGen;
};

#endif // PLAYWIDGET_H
