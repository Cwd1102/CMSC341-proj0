// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
Bingo::Bingo() {
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr; 
    m_helperSize = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
}

Bingo::Bingo(int rows, int columns, int min, int max) {
    m_trackCols = new int[m_numCols];
    m_trackRows = new int[m_numRows];
    m_helper = new Cell(); //DYNAMIC MEMORY<-----------------
    m_helperSize = 0;
    m_card = nullptr;
    if ((rows < 1 || columns < 1) || (min < 1 || max < 1)) {
        cout << "Invalid input, please try again" << endl;
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;
        m_maxBallVal = 0;
    }
    else {
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_card = new Cell*[m_numRows]; //CHECK LATER FOR DEBUG!!!<------------------------------------------
        for (int i = 0; i < m_numRows; i++) {
            m_card[i] = new Cell[m_numCols];
        }
    }
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max) {
    return true;
}

Bingo::~Bingo() {
    delete m_trackRows;
    delete m_trackCols;
}

void Bingo::clear() {
    delete m_card;
    delete m_helper;
    m_helper = nullptr;
    m_card = nullptr;
}

bool Bingo::initCard() {
    int rand = -1;
    int times = 0;
    int numPerCol = (floor((m_maxBallVal - m_minBallVal) / m_numCols)); //finds the range of numbers per column
    int tempMinBallVal = m_minBallVal;
    bool noDupe = false;

    for (int i = 0; i < m_numRows; i++) { 
        Random randgen(tempMinBallVal, tempMinBallVal + numPerCol , NORMAL);
        int* col = new int[(tempMinBallVal+numPerCol) - tempMinBallVal + 1];
        randgen.getShuffle(col);
        for (int j = 0; j < m_numCols; j++) {
            m_card[j][i].setRow(j);
            m_card[j][i].setCol(i);
            m_card[j][i].setVal(col[j]);
            times++;
        }
        tempMinBallVal = tempMinBallVal + numPerCol + 1;
        delete[] col;
        col = nullptr;
    }
    return true;//debug
}

vector<int> Bingo::drawBalls() {
    Random randBalls(m_minBallVal, m_maxBallVal, SHUFFLE);
    vector<int> vect;
    randBalls.getShuffle(vect);
    return vect;
}

int Bingo::play(int numDraws, vector<int> rndBalls) {
    int numPerCol = (floor((m_maxBallVal - m_minBallVal) / m_numCols));
    int tempMinBallVal = m_minBallVal;

    for (int i = 0; i < rndBalls.size(); i++) {
        for (int j = 0; j < m_numCols; j++) {
                if ((rndBalls[i] >= tempMinBallVal) && (rndBalls[i] <= tempMinBallVal + numPerCol)) {
                    for (int k = 0; k < m_numRows; k++) {
                        if (m_card[k][j].getVal() == rndBalls[i]) {
                            m_card[k][j].setVal(99);
                            k = m_numRows;
                            j = m_numCols;

                        }
                    }
                }
            tempMinBallVal = tempMinBallVal + numPerCol + 1;
        }
        tempMinBallVal = m_minBallVal;
        //*****CHECK FOR BINGO BELOW*******

    }

    return 0;
}

const Bingo& Bingo::operator=(const Bingo& rhs) {
    m_trackCols = rhs.m_trackCols;
    m_trackRows = rhs.m_trackRows;
    m_helper = rhs.m_helper;
    m_helperSize = rhs.m_helperSize;
    m_card = rhs.m_card;
    m_numRows = rhs.m_numRows;
    m_numCols = rhs.m_numCols;
    m_minBallVal = rhs.m_minBallVal;
    m_maxBallVal = rhs.m_maxBallVal;

    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard() {
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";
    cout << endl;
    for (int i = 1; i <= m_numRows; i++) {
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j = 1; j <= m_numCols; j++) {
            if (m_card[i - 1][j - 1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i - 1][j - 1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i - 1][j - 1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell& lhs, const Cell& rhs) {
    return ((lhs.m_col == rhs.m_col) &&
        (lhs.m_row == rhs.m_row) &&
        (lhs.m_value == rhs.m_value));
}