#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QMessageBox>

#include "introwidget.h"
#include "playwidget.h"
#include "playwidgethard.h"
#include "ratingobject.h"
#include "ratingwidget.h"

/**
 * @brief Основное окно программы
 */
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    /* Создать основное окно */
    GameWindow(QWidget *parent = nullptr);

public slots:
    /* Показать вкладку лучших результатов */
    void showRating();
    /* Скрыть вкладку лучших результатов */
    void hideRating();

    /* Начать игру с выбранным именем и режимом */
    void startGame(const QString & name, const QString & mode);
    /* Закончить игру */
    void stopGame();

private:
    /* Создать основной игровой виджет */
    PlayWidget * createPlayWidget(const QString & name, const QString & mode);

private:
    /* Набор виджетов, из которых видимым будет только один */
    QStackedWidget * mainStack;

    /* Приглашение ввести имя и выбрать режим игры */
    IntroWidget * introWidget;

    /* Вкладка с лучшими результатами по режимам игры */
    RatingWidget * ratingWidget;

    /* Вкладка, на которой проходит собственно игра */
    PlayWidget * playWidget;

    /* Хранилище лучших результатов */
    RatingObject * ratingObject;
};

#endif // GAMEWINDOW_H
