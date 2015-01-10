#include "Cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QList>
#include <qdebug.h>
#include <QGlobal.h>
#include <QTime>

void Cube::displayCube() {
    QString s = "\n";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 18; x++) {
            switch(matCube[x][y]) {
            case RED:
                s += "R ";
                break;
            case BLUE:
                s += "B ";
                break;
            case GREEN:
                s += "G ";
                break;
            case ORANGE:
                s += "O ";
                break;
            default:
                s += "? ";
                break;
            case WHITE:
                s += "W ";
                break;
            case YELLOW:
                s += "Y ";
                break;
            }
            if(x % 3 == 2) {
                s += " ";
            }
        }
        s += "\n";
    }
    qDebug() << s;
}

void Cube::setMatrix(color matrix[18][3])
{
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] = matrix[x][y];
        }
    }
}

color** Cube::getMatrix() const{
    color** mat = new color*[18];
    for (int i = 0; i < 18; ++i) {
        mat[i] = new color[3];
        for (int j = 0; j < 3; ++j) {
            mat[i][j] = matCube[i][j];
        }
    }
    return mat;
}

Cube::Cube(color matrix[18][3])
{
    setMatrix(matrix);
}

Cube::Cube(const Cube &c){
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] = c.getMatrix()[x][y];
        }
    }
}

//Utility methods

//returns indices of the cubie's stickers
//ordered by colors
QList<int> Cube::locateCubie(color c1, color c2) {
    //we're testing 3 cubies on 4 faces, it will cover the entire cube
    QList<int> cubi;
    for (int face = 0; face < 4; ++face) {
        cubi = cubie(face * 3 + 1, 0);
        if (cubieEqual(cubi, c1, c2)) {
            if (matCube[cubi.at(0)][cubi.at(1)] == c1) {
                return cubi;
            } else {
                QList<int> ret;
                ret += cubi.at(2);
                ret += cubi.at(3);
                ret += cubi.at(0);
                ret += cubi.at(1);
                return ret;
            }
        }
        cubi = cubie(face * 3 + 1, 2);
        if (cubieEqual(cubi, c1, c2)) {
            if (matCube[cubi.at(0)][cubi.at(1)] == c1) {
                return cubi;
            } else {
                QList<int> ret;
                ret += cubi.at(2);
                ret += cubi.at(3);
                ret += cubi.at(0);
                ret += cubi.at(1);
                return ret;
            }
        }
        cubi = cubie(face * 3, 1);
        if (cubieEqual(cubi, c1, c2)) {
            if (matCube[cubi.at(0)][cubi.at(1)] == c1) {
                return cubi;
            } else {
                QList<int> ret;
                ret += cubi.at(2);
                ret += cubi.at(3);
                ret += cubi.at(0);
                ret += cubi.at(1);
                return ret;
            }
        }
    }
    return cubi;
}

//returns indices of the cubie's stickers
//ordered by colors
QList<int> Cube::locateCubie(color c1, color c2, color c3) {
    //we're testing 2 cubies on 4 faces, it will cover the entire cube
    QList<int> cubi;
    for (int face = 0; face < 4; ++face) {
        cubi = cubie(face * 3, 0);
        if(cubieEqual(cubi, c1, c2, c3)) {
            QList<int> ret;
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c1) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c2) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c3) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            return ret;
        }
        cubi = cubie(face * 3, 2);
        if(cubieEqual(cubi, c1, c2, c3)) {
            QList<int> ret;
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c1) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c2) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[cubi.at(i)][cubi.at(i + 1)] == c3) {
                    ret += cubi.at(i);
                    ret += cubi.at(i + 1);
                }
            }
            return ret;
        }
    }
    return cubi;
}

QList<int> Cube::cubie(int i, int j) {
    //not on the cube
    if(i < 0 || i > 17 || j < 0 || j > 3) {
        QList<int> ret;
        return ret;
    } else {
        //indices on the face
        int x = i % 3;
        int y = j;
        //on this face
        color face = (color) (i /3);
        //we had the indices to this qlist and we will return it at the end of the method
        QList<int> ret;
        ret += i;
        ret += j;
        //if x = y = 1, it's a center
        if (x == 1 && y == 1) {
            return ret;
        }
        //if face is RED, BLUE, ORANGE OR GREEN
        else if (face < 4) {
            //if the sticker is adjacent to another RED, BLUE, ORANGE OR GREEN face
            //if the sticker is on the left of the face, return the sticker to the left of it
            if(x == 0){
                ret += (i + 11) % 12;
                ret += y;
            }
            //if the sticker is on the right of the face, return the sticker to the right of it
            if (x == 2) {
                ret += (i + 1) % 12;
                ret += y;
            }
            //if the sticker is adjacent to the WHITE face
            if (y == 0){
                switch(face){
                case RED:
                    ret += WHITE * 3 + x;
                    ret += 2;
                    break;
                case BLUE:
                    ret += WHITE * 3 + 2;
                    ret += 2 - x;
                    break;
                case ORANGE:
                    ret += WHITE * 3 + 2 - x;
                    ret += 0;
                    break;
                case GREEN:
                    ret += WHITE * 3;
                    ret += x;
                    break;
                default:
                    //should not happen
                    break;
                }
            }
            //if the sticker is adjacent to the YELLOW face
            if (y == 2){
                switch(face){
                case RED:
                    ret += YELLOW * 3 + 2 - x;
                    ret += 2;
                    break;
                case BLUE:
                    ret += YELLOW * 3;
                    ret += 2 - x;
                    break;
                case ORANGE:
                    ret += YELLOW * 3 + x;
                    ret += 0;
                    break;
                case GREEN:
                    ret += YELLOW * 3 + 2;
                    ret += x;
                    break;
                default:
                    //should not happen
                    break;
                }
            }
        }
        //if face is WHITE
        else if (face == WHITE){
            //if the face is adjacent to RED
            if (y == 2) {
                ret += RED * 3 + x;
                ret += 0;
            }
            //if the face is adjacent to BLUE
            if (x == 2) {
                ret += BLUE * 3 + 2 - y;
                ret += 0;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                ret += ORANGE * 3 + 2 - x;
                ret += 0;
            }
            //if the face is adjacent to GREEN
            if (x == 0) {
                ret += GREEN * 3 + y;
                ret += 0;
            }
        }
        //else face is YELLOW
        else {
            //if the face is adjacent to RED
            if (y == 2) {
                ret += RED * 3 + 2 - x;
                ret += 2;
            }
            //if the face is adjacent to BLUE
            if (x == 0) {
                ret += BLUE * 3 + 2 - y;
                ret += 2;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                ret += ORANGE * 3 + x;
                ret += 2;
            }
            //if the face is adjacent to GREEN
            if (x == 2) {
                ret += GREEN * 3 + y;
                ret += 2;
            }
        }
        return ret;
    }
}

QString Cube::scramble()
{
    QString scrambling;
    int lastMove = -1;
    int nextMove;
    int nbQ;
    QString cMove;
    QString cQ;

    qsrand(QDateTime::currentDateTime ().toTime_t ());

    for(int i = 0; i < 20; i++)
    {

        do{
            nextMove = qrand() % 6;
        }while(nextMove == lastMove);

        // Get move
        switch (nextMove) {
            case 0:
                cMove = 'U';
                break;
            case 1:
                cMove = 'D';
                break;
            case 2:
                cMove = 'L';
                break;
            case 3:
                cMove = 'R';
                break;
            case 4:
                cMove = 'F';
                break;
            case 5:
                cMove = 'B';
            break;
        }

        // Get nb of quarter turn
        switch(nbQ){
            case 0:
                cQ = "";
                break;
            case 1:
                cQ = '2';
                break;
            case 2:
                cQ = '\'';
                break;
        }

        nbQ = qrand() % 3;

        // add to scramble
        scrambling += cMove + cQ + ' ';

        lastMove = nextMove;
    }

    qDebug() << scrambling;

    this->moveSequence(scrambling, RED, YELLOW);

    return scrambling;

}

QString Cube::reverseSequence(QString sequence)
{
    QStringList moves = sequence.split(' ');
    QString reversed = "";
    QString tmp;

    for(int i = 0; i < moves.length(); i++)
    {
        tmp = moves.at(moves.length()-i-1);
        if(tmp.length()==1)
        {
            tmp+="'";
        }else if(tmp.length()==2)
        {
            if(tmp.at(1)== '\'')
            {
                tmp = tmp.at(0);
            }
        }

        reversed += tmp + " ";
    }

    return reversed;
}

/**
 * @brief Cube::moveSequence Move a sequence depending of the cube orientation
 * @param sequence The sequence to do
 * @param colorF The color on the Front
 * @param colorU The color on the Up
 * @return The actual sequence did
 */
QString Cube::moveSequence(QString sequence, color colorF, color colorU) {

    QStringList moves = sequence.split(' ');

    QChar theMove;
    int nbQTurn;

    QString facesTurned = "";

    foreach (QString move, moves)
    {
        theMove = move[0];

        if(move.length()>1)
        {
            if(move[1]=='2')
            {
                nbQTurn = 2;
            }else{
                nbQTurn = 3;
            }
        }else{
            nbQTurn = 1;
        }

        switch (theMove.toLatin1()) {
        case 'F':
            facesTurned += F(nbQTurn, colorF, colorU);
            break;
        case 'B':
            facesTurned += B(nbQTurn, colorF, colorU);
            break;
        case 'L':
            facesTurned += L(nbQTurn, colorF, colorU);
            break;
        case 'R':
            facesTurned += R(nbQTurn, colorF, colorU);
            break;
        case 'U':
            facesTurned += U(nbQTurn, colorF, colorU);
            break;
        case 'D':
            facesTurned += D(nbQTurn, colorF, colorU);
            break;
        }
    }
    return facesTurned;
}

//matrix rotation per face
//TODO: turn faces relatively
QString Cube::U(int nbQuarterTurn, color col1, color col2) {
    return turnFace(col2, nbQuarterTurn);
}

QString Cube::D(int nbQuarterTurn, color col1, color col2) {
    color face;
    switch(col2){
    case YELLOW:
        face = WHITE;
        break;
    case WHITE:
        face = YELLOW;
        break;
    default:
        face = (color) ((col2 + 2) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::B(int nbQuarterTurn, color col1, color col2) {
    color face;
    switch(col1){
    case YELLOW:
        face = WHITE;
        break;
    case WHITE:
        face = YELLOW;
        break;
    default:
        face = (color) ((col1 + 2) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::F(int nbQuarterTurn, color col1, color col2) {
    return turnFace(col1, nbQuarterTurn);
}

QString Cube::R(int nbQuarterTurn, color col1, color col2) {
    color face;
    switch(col1){
    case YELLOW:
        face = (color) ((col2 + 1) % 4);
        break;
    case WHITE:
        face = (color) ((col2 + 3) % 4);
        break;
    default:
        face = (color) ((col1 + 3) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::L(int nbQuarterTurn, color col1, color col2) {
    color face;
    switch(col1){
    case YELLOW:
        face = (color) ((col2 + 3) % 4);
    case WHITE:
        face = (color) ((col2 + 1) % 4);
        break;
    default:
        face = (color) ((col1 + 1) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::turnFace(int f, int number) {
    color face = (color) f;
    QString s = "";
//    qDebug() << "Rotating " << face << "face, by " << number << "quarter turns";
    //defining which stickers are on the face
    //those will get spinned
    number = (number + 4) % 4;
    if(number == 0){
        return "";
    }
    int* indicesFaceX = new int[8]{face * 3 + 2, face * 3 + 2,
                            face * 3 + 1, face * 3 + 2,
                            face * 3, face * 3,
                            face * 3 + 1, face * 3};
    int* indicesFaceY = new int[8]{1, 0,
                            2, 2,
                            1, 2,
                            0, 0};
    //defining which stickers are adjacent to the face
    //those too will get spinned
    int* indicesX;
    int* indicesY;
    switch(face) {
    case RED:
        s = "F";
        //if the RED face gets turned, then:
        //{WHITE, BLUE, YELLOW, GREEN} are adjacent, in this order;
        indicesX = new int[12]{WHITE * 3, WHITE * 3 + 1, WHITE * 3 + 2,
                                BLUE * 3, BLUE * 3, BLUE * 3,
                                YELLOW * 3, YELLOW * 3 + 1, YELLOW * 3 + 2,
                                GREEN * 3 + 2, GREEN * 3 + 2, GREEN * 3 + 2};
        indicesY = new int[12]{2, 2, 2,
                                0, 1, 2,
                                2, 2, 2,
                                2, 1, 0};
        break;
    case BLUE:
        s = "L";
        //if the BLUE face gets turned, then:
        //{WHITE, ORANGE, YELLOW, RED} are adjacent, in this order;
        indicesX = new int[12]{WHITE * 3 + 2, WHITE * 3 + 2, WHITE * 3 + 2,
                                ORANGE * 3, ORANGE * 3, ORANGE * 3,
                                YELLOW * 3, YELLOW * 3, YELLOW * 3,
                                RED * 3 + 2, RED * 3 + 2, RED * 3 + 2};
        indicesY = new int[12]{2, 1, 0,
                                0, 1, 2,
                                0, 1, 2,
                                2, 1, 0};
        break;
    case ORANGE:
        s = "B";
        //if the ORANGE face gets turned, then:
        //{WHITE, GREEN, YELLOW, BLUE} are adjacent, in this order;
        indicesX = new int[12]{WHITE * 3 + 2, WHITE * 3 + 1, WHITE * 3,
                                GREEN * 3, GREEN * 3, GREEN * 3,
                                YELLOW * 3 + 2, YELLOW * 3 + 1, YELLOW * 3,
                                BLUE * 3 + 2, BLUE * 3 + 2, BLUE * 3 + 2};
        indicesY = new int[12]{0, 0, 0,
                                0, 1, 2,
                                0, 0 ,0,
                                2, 1, 0};
        break;
    case GREEN:
        s = "R";
        //if the GREEN face gets turned, then:
        //{WHITE, RED, YELLOW, ORANGE} are adjacent, in this order;
        indicesX = new int[12]{WHITE * 3, WHITE * 3, WHITE * 3,
                                RED * 3, RED * 3, RED * 3,
                                YELLOW * 3 + 2, YELLOW * 3 + 2, YELLOW * 3 + 2,
                                ORANGE * 3 + 2, ORANGE * 3 + 2, ORANGE * 3 + 2};
        indicesY = new int[12]{0, 1, 2,
                                0, 1, 2,
                                2, 1, 0,
                                2, 1, 0};
        break;
    case WHITE:
        s = "D";
        //if the WHITE face gets turned, then:
        //{RED, GREEN, ORANGE, BLUE} are adjacent, in this order;
        indicesX = new int[12]{RED * 3, RED * 3 + 1, RED * 3 + 2,
                                GREEN * 3, GREEN * 3 + 1, GREEN * 3 + 2,
                                ORANGE * 3, ORANGE * 3 + 1, ORANGE * 3 + 2,
                                BLUE * 3, BLUE * 3 + 1, BLUE * 3 + 2};
        indicesY = new int[12]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        break;
    case YELLOW:
        s = "U";
        //if the YELLOW face gets turned, then:
        //{RED, BLUE, ORANGE, GREEN} are adjacent, in this order;
        indicesX = new int[12]{RED * 3, RED * 3 + 1, RED * 3 + 2,
                                BLUE * 3, BLUE * 3 + 1, BLUE * 3 + 2,
                                ORANGE * 3, ORANGE * 3 + 1, ORANGE * 3 + 2,
                                GREEN * 3, GREEN * 3 + 1, GREEN * 3 + 2};
        indicesY = new int[12]{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        break;
    default:
        break;
    }

    color saveFace[4];
    color saveAdjacent[6];
    //Rotating the face -1, 1 or 2 quarter turns clock wise
    switch(number){
    case 1:
        //turning the face
        saveFace[0] = matCube[indicesFaceX[6]][indicesFaceY[6]];
        saveFace[1] = matCube[indicesFaceX[7]][indicesFaceY[7]];
        for (int i = 7; i > 1; i -= 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i - 2]][indicesFaceY[i - 2]];
            matCube[indicesFaceX[i - 1]][indicesFaceY[i - 1]] = matCube[indicesFaceX[i - 3]][indicesFaceY[i - 3]];
        }
        matCube[indicesFaceX[0]][indicesFaceY[0]] = saveFace[0];
        matCube[indicesFaceX[1]][indicesFaceY[1]] = saveFace[1];
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 3; ++i) {
            saveAdjacent[i] = matCube[indicesX[i + 9]][indicesY[i + 9]];
        }
        for (int i = 11; i > 3; i-=3) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i - 3]][indicesY[i - 3]];
            matCube[indicesX[i - 1]][indicesY[i - 1]] = matCube[indicesX[i - 4]][indicesY[i - 4]];
            matCube[indicesX[i - 2]][indicesY[i - 2]] = matCube[indicesX[i - 5]][indicesY[i - 5]];
        }
        matCube[indicesX[0]][indicesY[0]] = saveAdjacent[0];
        matCube[indicesX[1]][indicesY[1]] = saveAdjacent[1];
        matCube[indicesX[2]][indicesY[2]] = saveAdjacent[2];
        break;
    case 2:
        s += "2";
        //turning the face
        for (int i = 0; i < 4; ++i) {
            saveFace[i] = matCube[indicesFaceX[i]][indicesFaceY[i]];
        }
        for (int i = 0; i < 4; i += 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i + 4]][indicesFaceY[i + 4]];
            matCube[indicesFaceX[i + 1]][indicesFaceY[i + 1]] = matCube[indicesFaceX[i + 5]][indicesFaceY[i + 5]];
        }
        for (int i = 0; i < 4; ++i) {
            matCube[indicesFaceX[i + 4]][indicesFaceY[i + 4]] = saveFace[i];
        }
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 6; ++i) {
            saveAdjacent[i] = matCube[indicesX[i]][indicesY[i]];
        }
        for (int i = 0; i < 6; ++i) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i + 6]][indicesY[i + 6]];
        }
        for (int i = 0; i < 6; ++i) {
            matCube[indicesX[i + 6]][indicesY[i + 6]] = saveAdjacent[i];
        }
        break;
    case 3: //3 = -1 % 4
        s += "'";
        //turning the face
        saveFace[0] = matCube[indicesFaceX[0]][indicesFaceY[0]];
        saveFace[1] = matCube[indicesFaceX[1]][indicesFaceY[1]];
        for (int i = 0; i < 6; i += 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i + 2]][indicesFaceY[i + 2]];
            matCube[indicesFaceX[i + 1]][indicesFaceY[i + 1]] = matCube[indicesFaceX[i + 3]][indicesFaceY[i + 3]];
        }
        matCube[indicesFaceX[6]][indicesFaceY[6]] = saveFace[0];
        matCube[indicesFaceX[7]][indicesFaceY[7]] = saveFace[1];
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 3; ++i) {
            saveAdjacent[i] = matCube[indicesX[i]][indicesY[i]];
        }
        for (int i = 0; i < 9; i += 3) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i + 3]][indicesY[i + 3]];
            matCube[indicesX[i + 1]][indicesY[i + 1]] = matCube[indicesX[i + 4]][indicesY[i + 4]];
            matCube[indicesX[i + 2]][indicesY[i + 2]] = matCube[indicesX[i + 5]][indicesY[i + 5]];
        }
        matCube[indicesX[9]][indicesY[9]] = saveAdjacent[0];
        matCube[indicesX[10]][indicesY[10]] = saveAdjacent[1];
        matCube[indicesX[11]][indicesY[11]] = saveAdjacent[2];
        break;
    default:
        qDebug() << "no rotation for " << number << "quarter turns";
        break;
    }
    s += " ";
    return s;
}

bool Cube::cubieEqual(QList<int> cubi, color c1, color c2) {
    return ((matCube[cubi.at(0)][cubi.at(1)] == c1 && matCube[cubi.at(2)][cubi.at(3)] == c2)
         || (matCube[cubi.at(0)][cubi.at(1)] == c2 && matCube[cubi.at(2)][cubi.at(3)] == c1));

}

bool Cube::cubieEqual(QList<int> cubi, color c1, color c2, color c3) {
    return((matCube[cubi.at(4)][cubi.at(5)] == c1 && cubieEqual(cubi, c2, c3))
        || (matCube[cubi.at(4)][cubi.at(5)] == c2 && cubieEqual(cubi, c1, c3))
        || (matCube[cubi.at(4)][cubi.at(5)] == c3 && cubieEqual(cubi, c1, c2)));
}

