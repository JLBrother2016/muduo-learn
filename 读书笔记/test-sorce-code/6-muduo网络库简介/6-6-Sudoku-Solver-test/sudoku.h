#ifndef MUDUO_EXAMPLES_SUDOKU_SUDOKU_H
#define MUDUO_EXAMPLES_SUDOKU_SUDOKU_H


#include "source-lib/Types.h"
#include "source-lib/StringPiece.h"

muduo::string solveSudoku(const muduo::StringPiece& puzzle);
const int kCells = 81;
extern const char kNoSolution[];

#endif
