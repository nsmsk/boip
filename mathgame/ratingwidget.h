#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>

#include "ratingobject.h"

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RatingWidget(RatingObject * hs, QWidget *parent = nullptr);

public slots:
    void redrawScores();

signals:
    void okPressed();

private:
    RatingObject * highScores;

    QLabel * titleLabel;

    QTableWidget * scoreTable;

    QPushButton * okButton;
};

#endif // RATINGWIDGET_H
