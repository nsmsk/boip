#include "ratingwidget.h"

RatingWidget::RatingWidget(RatingObject * hs, QWidget *parent):
    QWidget(parent)
{
    highScores = hs;

    titleLabel = new QLabel(tr("Best scores"), this);
    scoreTable = new QTableWidget(this);
    okButton = new QPushButton(tr("OK"), this);

    QVBoxLayout * la = new QVBoxLayout();

    la->addWidget(titleLabel);
    la->addWidget(scoreTable);
    la->addWidget(okButton);

    setLayout(la);

    redrawScores();

    connect(okButton, SIGNAL(clicked()), this, SIGNAL(okPressed()));
    connect(highScores, SIGNAL(changed()), this, SLOT(redrawScores()));
}

void RatingWidget::redrawScores()
{
    scoreTable->setHorizontalHeaderLabels(
                QStringList() << tr("Mode") << tr("Name") << tr("Score")
                );

    QStringList modes = highScores->getAllModes();

    scoreTable->clear();
    scoreTable->setRowCount(modes.length());
    scoreTable->setColumnCount(3);
    scoreTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < modes.length(); i++) {
        scoreTable->setItem(i, 0, new QTableWidgetItem(modes.at(i)));
        scoreTable->setItem(i, 1, new QTableWidgetItem(highScores->getNameByMode(modes.at(i))));
        scoreTable->setItem(i, 2, new QTableWidgetItem(QString::number(highScores->getScoreByMode(modes.at(i)))));
    }
}
