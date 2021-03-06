#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "IsometricCubeWidget.h"
#include "Cube.h"
#include "Fridrich.h"
#include "ResolutionWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *e);

private:
    IsometricCubeWidget *isometricCubeWidget;
    ResolutionWidget *resolutionWidget;

    // Menu
    QPushButton *scramblePB;
    QPushButton *solvePB;
    QPushButton *resetPB;
    QPushButton *sequencePB;
    QPushButton *reverseSequencePB;
    QPushButton *cubeInputPB;
    QLineEdit *sequenceLE;
    QLabel *configModeLabel;

    // Orientation menu
    QPushButton *movesPB[6];

    Cube *displayedCube;

    void initSolvedCube();
    void refreshResolutionState();

signals:

public slots:
    void scrambleSlot();
    void solveSlot();
    void sendSequenceSlot();
    void resetSlot();
    void reverseSequenceSlot();
    void turnXSlot();
    void turnYSlot();
    void turnZSlot();
    void turnXpSlot();
    void turnYpSlot();
    void turnZpSlot();
    void startCubeInput();
    void cubieModified(int, int, color);

    void receiveMove(QString);

};

#endif // MAINWIDGET_H
