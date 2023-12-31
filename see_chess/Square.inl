#include "Square.hpp"
#include <cassert>

constexpr SquareType to_underlying_type(Direction direction) {
	return static_cast<SquareType>(direction);
}
constexpr SquareType to_underlying_type(Diagonal diagonal) {
	return static_cast<SquareType>(diagonal);
}
constexpr SquareType to_underlying_type(Antidiagonal antidiagonal) {
	return static_cast<SquareType>(antidiagonal);
}
constexpr SquareType to_underlying_type(Rank rank) {
	return static_cast<SquareType>(rank);
}
constexpr SquareType to_underlying_type(File file) {
	return static_cast<SquareType>(file);
}
constexpr SquareType to_underlying_type(Square square) {
	return static_cast<SquareType>(square);
}

constexpr int to_raw_offset(Direction direction) {
	switch (direction) {
	case Direction::East:
		return 1;
	case Direction::West:
		return -1;
	case Direction::North:
		return 8;
	case Direction::South:
		return -8;
	case Direction::Northeast:
		return 9;
	case Direction::Southwest:
		return -9;
	case Direction::Northwest:
		return 7;
	case Direction::Southeast:
		return -7;
	default:
		assert(false);
	}
}

constexpr Rank to_rank(Square square) {
	return static_cast<Rank>(to_underlying_type(square) >> 3);
}
constexpr File to_file(Square square) {
	return static_cast<File>(to_underlying_type(square) & 7);
}
constexpr Diagonal to_diagonal(Square square) {
	return static_cast<Diagonal>(7 + to_underlying_type(to_rank(square)) - to_underlying_type(to_file(square)));
}
constexpr Antidiagonal to_antidiagonal(Square square) {
	return static_cast<Antidiagonal>(to_underlying_type(to_rank(square)) + to_underlying_type(to_file(square)));
}
constexpr Square to_square(Rank rank, File file) {
	return static_cast<Square>((to_underlying_type(rank) << 3) + to_underlying_type(file));
}

//constexpr Rank move(Rank rank, int distance) {
//
//}
//
//constexpr int sign_x(Direction direction) {
//	switch (direction) {
//	case Direction::East:
//	case Direction::Northeast:
//	case Direction::Southeast:
//		return 1;
//	case Direction::West:
//	case Direction::Northwest:
//	case Direction::Southwest:
//		return -1;
//	case Direction::North:
//	case Direction::South:
//		return 0;
//	default:
//		assert(false);
//	}
//}
//
//constexpr int sign_y(Direction direction) {
//	switch (direction) {
//	case Direction::North:
//	case Direction::Northeast:
//	case Direction::Northwest:
//		return 1;
//	case Direction::South:
//	case Direction::Southeast:
//	case Direction::Southwest:
//		return -1;
//	case Direction::East:
//	case Direction::West:
//		return 0;
//	default:
//		assert(false);
//	}
//}
//
//constexpr Square move(Square square, Direction direction) {
//	const SquareType rank = to_underlying_type(to_rank(square));
//	const SquareType flie = to_underlying_type(to_file(square));
//	return to_square();
//}
