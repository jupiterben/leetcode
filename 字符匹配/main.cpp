

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const static int ROW_SIZE = 3;
const static int COL_SIZE = 4;
const char board[ROW_SIZE][COL_SIZE] = {
    {'A', 'B', 'C', 'E'},
    {'S', 'F', 'C', 'S'},
    {'A', 'D', 'E', 'E'},
};

class Position
{
public:
    int row_idx;
    int col_idx;
    Position(int row, int col)
    {
        row_idx = row;
        col_idx = col;
    }
    bool operator==(const Position &otherP) const
    {
        return (row_idx == otherP.row_idx) && (col_idx == otherP.col_idx);
    }
    bool isValid() const
    {
        return row_idx < ROW_SIZE && col_idx < COL_SIZE;
    }

    std::vector<Position> getNeighbour()const
    {
        std::vector<Position> neighbour;
        Position left(row_idx, col_idx + 1);
        if (left.isValid())
            neighbour.push_back(left);
        Position right(row_idx, col_idx - 1);
        if (right.isValid())
            neighbour.push_back(right);
        Position top(row_idx - 1, col_idx);
        if (top.isValid())
            neighbour.push_back(top);
        Position bottom(row_idx + 1, col_idx);
        if (bottom.isValid())
            neighbour.push_back(bottom);
        return neighbour;
    }
};

char getCharInBoard(const Position &pos)
{
    return board[pos.row_idx][pos.col_idx];
}

bool isInList(const Position &pos, const std::vector<Position> &list)
{
    return std::find(list.begin(), list.end(), pos) != list.end();
}

bool matchString(const string &str, int cPos, const Position &startPos, std::vector<Position> excludePos)
{
    if (cPos >= str.length())
        return true;

    if (str.at(cPos) != getCharInBoard(startPos))
        return false;

    excludePos.push_back(startPos);

    std::vector<Position> neighbour = startPos.getNeighbour();
    for (std::vector<Position>::const_iterator itr = neighbour.begin(); itr != neighbour.end(); ++itr)
    {
        if (!isInList(*itr, excludePos) && matchString(str, cPos + 1, *itr, excludePos))
        {
            return true;
        }
    }
    return false;
}

bool isWordInBoard(const string &word)
{
    if (word.empty())
        return false;
    std::vector<Position> excludePos;

    for (int i = 0; i < COL_SIZE; i++)
    {
        for (int j = 0; j < ROW_SIZE; j++)
        {
            Position pos(j, i);
            if (matchString(word, 0, pos, excludePos))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cout << isWordInBoard("ABCCED") << endl;
    cout << isWordInBoard("SEE") << endl;
    cout << isWordInBoard("ABCB") << endl;
}