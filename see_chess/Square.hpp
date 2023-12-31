#pragma once
#include <cstdint>

using SquareType = uint8_t;

// northwest    north   northeast
//         +7    +8    +9
//             \  |  /
// west    -1 <-  0 -> +1    east
//             /  |  \
//         -9    -8    -7
// southwest    south   southeast

// A direction on the chessboard. See compass above for detail.
enum class Direction : SquareType {
	East,  // +1
	West,  // -1
	North,  // +8
	South,  // -8
	Northwest,  // +7
	Southeast,  // -7
	Northeast,  // +9
	Southwest,  // -9
};
constexpr size_t direction_count = 8;

// Vertical position of a chessboard square.
// rank = square / 8;
enum class Rank : SquareType {
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8
};
constexpr size_t rank_count = 8;


// Horizontal position of a chessboard square.
// file = square % 8;
enum class File : SquareType {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H
};
constexpr size_t flie_count = 8;


// Diagonal (+x, +y) position of a chessboard square.
// diagonal = 7 + rank - file;
enum class Diagonal : SquareType {
	H1H1,
	G1H2,
	F1H3,
	E1H4,
	D1H5,
	C1H6,
	B1H7,
	A1H8,  // Main diagonal.
	A2G8,
	A3F8,
	A4E8,
	A5D8,
	A6C8,
	A7B8,
	A8A8
};
constexpr size_t diagonal_count = 15;

// Antidiagonal (+x, -y) position of a chessboard square.
// antidiagonal = rank + file;
enum class Antidiagonal : SquareType {
	A1A1,
	B1A2,
	C1A3,
	D1A4,
	E1A5,
	F1A6,
	G1A7,
	H1A8,  // Main antidiagonal.
	H2B8,
	H3C8,
	H4D8,
	H5E8,
	H6F8,
	H7G8,
	H8H8
};
constexpr size_t antidiagonal_count = 15;

// Chessboard square.
enum class Square : SquareType {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};
constexpr size_t square_count = 64;

constexpr SquareType to_underlying_type(Direction direction);
constexpr SquareType to_underlying_type(Rank rank);
constexpr SquareType to_underlying_type(File file);
constexpr SquareType to_underlying_type(Diagonal diagonal);
constexpr SquareType to_underlying_type(Antidiagonal antidiagonal);
constexpr SquareType to_underlying_type(Square square);

constexpr int to_raw_offset(Direction direction);

constexpr Rank to_rank(Square square);
constexpr File to_file(Square square);
constexpr Diagonal to_diagonal(Square square);
constexpr Antidiagonal to_antidiagonal(Square square);
constexpr Square to_square(Rank rank, File file);

#include "Square.inl"
