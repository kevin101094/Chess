#include "Queen.h"
#include "Board.h"

Queen::Queen() {
	
}
bool Queen::isOutside(int X, int Y) {
	return X < 0 || X >= 8 || Y < 0 || Y >= 8;
}
bool Queen::isSameColor(bool color, int X, int Y, BoardControl& board) {
	return board.GetPieceID(X, Y) != Empty and board.getPieceColor(X, Y) == color;
}
std::vector<pair> Queen::getPossibleMove(bool color, int row, int col, BoardControl& board) {
	std::vector<pair> tmp;
	for (int r = row + 1, c = col + 1; c < 8 and r < 8; r++, c++) {
		if (isSameColor(color, r, c, board)) break;
		if (isValidMove(row, col, r, c, board))
			tmp.push_back({ r,c });
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int r = row - 1, c = col - 1; r >= 0 and c >= 0; r--, c--) {
		if (isSameColor(color, r, c, board)) break;
		if (isValidMove(row, col, r, c, board))
			tmp.push_back({ r,c });
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int c = col + 1, r = row - 1; c < 8 and r >= 0; c++, r--) {
		if (isSameColor(color, r, c, board)) break;
		if (isValidMove(row, col, r, c, board))
			tmp.push_back({ r,c });
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int c = col - 1, r = row + 1; c >= 0 and r < 8; c--, r++) {
		if (isSameColor(color, r, c, board)) break;
		if (isValidMove(row, col, r, c, board))
			tmp.push_back({ r,c });
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int r = row + 1; r < 8; r++) {
		if (isSameColor(color, r, col, board)) break;
		if (isValidMove(row, col, r, col, board))
			tmp.push_back({ r,col });
		if (board.GetPieceID(r, col) != Empty) break;
	}
	for (int r = row - 1; r >= 0; r--) {
		if (isSameColor(color, r, col, board)) break;
		if (isValidMove(row, col, r, col, board))
			tmp.push_back({ r,col });
		if (board.GetPieceID(r, col) != Empty) break;
	}
	for (int c = col + 1; c < 8; c++) {
		if (isSameColor(color, row, c, board)) break;
		if (isValidMove(row, col, row, c, board))
			tmp.push_back({ row,c });
		if (board.GetPieceID(row, c) != Empty) break;
	}
	for (int c = col - 1; c >= 0; c--) {
		if (isSameColor(color, row, c, board)) break;
		if (isValidMove(row, col, row, c, board))
			tmp.push_back({ row,c });
		if (board.GetPieceID(row, c) != Empty) break;
	}
	return tmp;
}
bool Queen::isValidMove(int X, int Y, int toX, int toY, BoardControl& board) {
	bool copycolor = board.getPieceColor(toX, toY), fromcolor = board.getPieceColor(X, Y);
	ID copyID = board.GetPieceID(toX, toY), fromID = board.GetPieceID(X, Y);
	BoardControl copy = BoardControl();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (r == toX and c == toY) copy.setPiece(r, c, fromcolor, fromID);
			else if (r == X and c == Y) copy.setPiece(r, c, NULL, Empty);
			else copy.setPiece(r, c, board.getPieceColor(r, c), board.GetPieceID(r, c));
		}
	}
	copy.setPiece(toX, toY, fromcolor, fromID);
	copy.setPiece(X, Y, NULL, Empty);
	bool ans;
	if (fromcolor == black) ans = board.isBlackChecked(copy);
	else if (fromcolor == white) ans = board.isWhiteChecked(copy);
	copy.setPiece(X, Y, fromcolor, fromID);
	copy.setPiece(toX, toY, copycolor, copyID);
	return !ans;
}
bool Queen::canCheck(int X, int Y, int toX, int toY, BoardControl& board) {
	for (int r = X + 1, c = Y + 1; c < 8 and r < 8; r++, c++) {
		if (r == toX and c == toY) return 1;
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int r = X - 1, c = Y - 1; r >= 0 and c >= 0; r--, c--) {
		if (r == toX and c == toY) return 1;
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int c = Y + 1, r = X - 1; c < 8 and r >= 0; c++, r--) {
		if (r == toX and c == toY) return 1;
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int c = Y - 1, r = X + 1; c >= 0 and r < 8; c--, r++) {
		if (r == toX and c == toY) return 1;
		if (board.GetPieceID(r, c) != Empty) break;
	}
	for (int r = X + 1; r < 8; r++) {
		if (r == toX and Y == toY) return 1;
		if (board.GetPieceID(r, Y) != Empty) break;
	}
	for (int r = X - 1; r >= 0; r--) {
		if (r == toX and Y == toY) return 1;
		if (board.GetPieceID(r, Y) != Empty) break;
	}
	for (int c = Y + 1; c < 8; c++) {
		if (X == toX and c == toY) return 1;
		if (board.GetPieceID(X, c) != Empty) break;
	}
	for (int c = Y - 1; c >= 0; c--) {
		if (X == toX and c == toY) return 1;
		if (board.GetPieceID(X, c) != Empty) break;
	}
	return 0;
}