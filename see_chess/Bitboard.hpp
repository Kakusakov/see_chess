#pragma once
#include "Square.hpp"

// An efficient representation of a chessboard occupance.
class Bitboard {
public:
	constexpr Bitboard() {};
	constexpr static Bitboard empty();
	constexpr static Bitboard filled();
	constexpr static Bitboard square(Square square);
	constexpr static Bitboard rank(Rank rank);
	constexpr static Bitboard file(File file);
	constexpr static Bitboard diagonal(Diagonal diagonal);
	constexpr static Bitboard antidiagonal(Antidiagonal antidiagonal);
	constexpr bool operator==(Bitboard other) const;
	constexpr Bitboard operator~() const;
	constexpr Bitboard operator|(Bitboard other) const;
	constexpr Bitboard operator&(Bitboard other) const;
	constexpr Bitboard operator^(Bitboard other) const;
	constexpr Bitboard operator>>(int shift) const;
	constexpr Bitboard operator<<(int shift) const;

	// Checks whether the board is completely empty.
	constexpr bool is_empty() const;
	// Checks whether the board is completely occupied.
	constexpr bool is_filled() const;
	// Checks whether the square is occupied.
	constexpr bool has_square(Square square) const;
	// Counts the amount of occupied squares.
	constexpr int popcount() const;
	// Finds the square with the smallest value. 
	// Board must be non-empty.
	constexpr Square bitscan() const;
	// Positive shift shifts to the LEFT (increasing), 
	// negative shift shifts to the RIGHT (decreasing).
	constexpr Bitboard generalized_shift(int shift) const;
	// Removes the square with the smallest value.
	// Does nothing if board is empty.
	constexpr Bitboard reset_bit() const;
	constexpr Bitboard step(Direction direction) const;
	constexpr Bitboard north_fill() const;
private:
	constexpr explicit Bitboard(uint64_t value) : value(value) {}
	uint64_t value = 0;
};

#include "Bitboard.inl"
