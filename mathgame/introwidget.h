#ifndef INTROWIDGET_H
#define INTROWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QMessageBox>

/**
 * @brief Вкладка с приглашением ввести имя, выбрать режим и начать игру
 */
class IntroWidget: public QWidget
{
    Q_OBJECT
public:
    /* Инициализация вкладки и ее содержимого */
    explicit IntroWidget(QWidget *parent = nullptr);

signals:
    /* Пользователь ввел имя и скомандовал начать игру */
    void startButtonPressed(const QString & name, const QString & mode);
    /* Пользователь нажал на просмотр рейтинга */
    void ratingButtonPressed();

private slots:
    /* Обработка нажатия на кнопку начать игру */
    void startGame();

private:
    /* Поясняющая надпись для имени пользователя */
    QLabel * nameLabel;
    /* Поясняющая надпись для списка режимов игры */
    QLabel * modeLabel;

    /* Поле ввода имени пользователя */
    QLineEdit * nameField;
    /* Поле выбора режима игры */
    QComboBox * modeField;

    /* Кнопка начаа игры */
    QPushButton * startButton;
    /* Кнопка просмотра рейтинга */
    QPushButton * ratingButton;
    /* Кнопка выхода из программы */
    QPushButton * quitButton;
};

#endif // INTROWIDGET_H
