#include "Scoreboard.h"

Scoreboard::Scoreboard(QWidget* parent) : QGraphicsView(parent) {
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);
    //donner un nom à la page
    setWindowTitle("Tableau de scores");
    pScene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //this->background.load("../img/space-invader.jpg");
    //this->setSceneRect(0,0, background.width(), background.height());

    QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(5);
    tableWidget->setColumnCount(1);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(tableWidget);
    bestScoreLabel = new QLabel(this);
    bestScoreLabel->setText("Meilleur score : 0");
    bestScoreLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(bestScoreLabel);


    QStringList headerLabels;
    headerLabels << "Score";
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    QList<int> scores;
    scores << 100 << 200 << 150 << 120 << 180;

    int bestScore = 0;

    for (int row = 0; row < scores.size(); ++row) {
        int score = scores[row];
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(score));
        tableWidget->setItem(row, 0, item);

        if (score > bestScore) {
            bestScore = score;
        }
    }

    bestScoreLabel->setText("Meilleur score : " + QString::number(bestScore));

    tableWidget->resizeColumnsToContents();
}
void Scoreboard::drawBackground(QPainter *painter, const QRectF &rect) {
    // Fonction du TP4 qui permet de dessiner l'image de fond
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
Scoreboard::~Scoreboard() {
    delete this->tableWidget;
}