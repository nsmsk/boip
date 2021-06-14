#include "gamewindow.h"

/**
 * @brief Инициализация основного окна программы
 * @param parent Родительский виджет, обычно nullptr
 */
GameWindow::GameWindow(QWidget *parent):
    QWidget(parent)
{
    /* Заголовок окна, минимальный размер */
    setWindowTitle(tr("Math game"));
    setMinimumSize(640, 480);

    /* Загружаем из файла конфигурации лучшие результаты */
    ratingObject = new RatingObject(this);

    /* Создаем вкладки для начала игры и лучших результатов */
    mainStack = new QStackedWidget(this);
    introWidget = new IntroWidget(this);
    ratingWidget = new RatingWidget(ratingObject, this);

    /* Реакция на нажатие кнопок начала игры, вызова лучших результатов и возврата в меню */
    connect(introWidget, SIGNAL(ratingButtonPressed()), this, SLOT(showRating()));
    connect(ratingWidget, SIGNAL(okPressed()), this, SLOT(hideRating()));
    connect(introWidget, SIGNAL(startButtonPressed(QString, QString)), this, SLOT(startGame(QString, QString)));

    /* Добавляем вкладки начала игры и лучших результатов в переключатель вкладок */
    mainStack->addWidget(introWidget);
    mainStack->addWidget(ratingWidget);
    mainStack->setCurrentWidget(introWidget);

    /* Разворачиваем текущую вкладку на все окно */
    QHBoxLayout * la = new QHBoxLayout();

    la->addWidget(mainStack);

    setLayout(la);
}

/**
 * @brief Показ вкладки с лучшими результатами игры
 */
void GameWindow::showRating()
{
    mainStack->setCurrentWidget(ratingWidget);
}

/**
 * @brief Возврат в меню начала игры
 */
void GameWindow::hideRating()
{
    mainStack->setCurrentWidget(introWidget);
}

/**
 * @brief Запуск игры
 * @param name Введенное имя игрока
 * @param mode Выбранный режим игры
 */
void GameWindow::startGame(const QString & name, const QString & mode)
{
    playWidget = createPlayWidget(name, mode);

    mainStack->addWidget(playWidget);
    mainStack->setCurrentWidget(playWidget);

    connect(playWidget, SIGNAL(gameOver()), this, SLOT(stopGame()));

    playWidget->start();
}

/**
 * @brief Окончание игры
 *
 * Сохранить результат в списке лучших, если рекорд побит и показать
 * таблицу рекордов
 */
void GameWindow::stopGame()
{
    QString name = playWidget->getName();
    int score = playWidget->getScore();

    ratingObject->addScore(playWidget->getMode(), name, score);

    mainStack->removeWidget(playWidget);
    mainStack->setCurrentWidget(ratingWidget);

    playWidget->deleteLater();
    playWidget = nullptr;

    QMessageBox::information(
                this,
                tr("Level done"),
                tr("Your score is %1").arg(score),
                QMessageBox::Ok);
}

/**
 * @brief Создать основной игровой виджет
 * @param name Имя игрока
 * @param mode Режим игры
 * @return Виджет для игры. Его класс зависит от режима игры
 */
PlayWidget * GameWindow::createPlayWidget(const QString &name, const QString &mode)
{
    if (mode == tr("Hard")) {
        return new PlayWidgetHard(name, mode, this);
    } else {
        return new PlayWidget(name, mode, this);
    }
}
