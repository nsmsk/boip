#include "introwidget.h"

/**
 * @brief Инициализация вкладки с приглашением начать игру
 * @param parent Родительское окно - основное окно программы
 */
IntroWidget::IntroWidget(QWidget *parent):
    QWidget(parent)
{
    nameLabel = new QLabel(tr("Player name: "), this);
    modeLabel = new QLabel(tr("Game mode: "), this);

    nameField = new QLineEdit(this);
    modeField = new QComboBox(this);

    /* Легкий режим - за минуту вычислить как можно больше выражений вида
     * A + B - C или A * B, где A, B, C - двузначные числа
     */
    modeField->addItem(tr("Easy"));
    /* Нормальныйй режим - за минуту вычислить как можно больше выражений вида
     * A + B - C, где A, B, C - трехзначные числа или A * B, где A и B -
     * двузначные числа
     */
    modeField->addItem(tr("Normal"));
    /* Трудный режим - на каждое выражение вида A + B - C дается 10 секунд,
     * игра идет до первого неверного ответа
     */
    modeField->addItem(tr("Hard"));

    /* Кнопки для начала игры, вывода личших результатов и выхода из программы */
    startButton = new QPushButton(tr("Start game"), this);
    ratingButton = new QPushButton(tr("High scores"), this);
    quitButton = new QPushButton(tr("Quit"), this);

    /* Установка обработчиков на нажатие каждой из трех кнопок */
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ratingButton, SIGNAL(clicked()), this, SIGNAL(ratingButtonPressed()));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    /* Размещение полей ввода и кнопок на вкладке */
    QGridLayout * la = new QGridLayout();

    /* Вверху - поля ввода имени игрока и выбора режима игры */
    la->addWidget(nameLabel, 0, 0, 1, 1);
    la->addWidget(modeLabel, 1, 0, 1, 1);
    la->addWidget(nameField, 0, 1, 1, 1);
    la->addWidget(modeField, 1, 1, 1, 1);

    /* В середине - свободное пространство, сколько нужно */
    la->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 2);

    /* Внизу - кнопки начала игры, показа рейтинга и выхода из программы */
    la->addWidget(startButton, 3, 0, 1, 2);
    la->addWidget(ratingButton, 4, 0, 1, 2);
    la->addWidget(quitButton, 5, 0, 1, 2);

    la->setAlignment(Qt::AlignHCenter);

    setLayout(la);
}

/**
 * @brief Нажатие на кнопку начала игры
 *
 * Проверяет, что имя пользователя введено и выбран корректный режим игры. Если все
 * правильно, то сообщает основному окну о запуске игры. Иначе - показывает сообщение
 * об ошибке (пользователь не ввел имя и т.п.)
 */
void IntroWidget::startGame()
{
    QString name = nameField->text();
    QString mode = modeField->currentText();

    if (name.isEmpty() || mode.isEmpty()) {
        QMessageBox::critical(
                    this,
                    tr("Please fill out all the fields"),
                    tr("Please enter your name and select game mode"),
                    QMessageBox::Ok);
    } else {
        emit startButtonPressed(name, mode);
    }
}
