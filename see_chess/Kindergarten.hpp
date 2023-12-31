#pragma once
#include "Bitboard.hpp"
#include <array>

// A color of chess pieces.
enum class Color : SquareType {
	White,
	Black
};
constexpr size_t color_count = 2;

constexpr SquareType to_underlying_type(Color color) {
	return static_cast<SquareType>(color);
}
constexpr Color operator!(Color color) {
	return static_cast<Color>(!to_underlying_type(color));
}

constexpr Bitboard king_attacks(Square from) {
	constexpr auto lookup = [] {
		std::array<Bitboard, square_count> lookup{};
		auto bb = Bitboard::square(Square::A1);
		for (size_t i = 0; i < square_count; i++, bb << 1) {
			const auto temp = bb | bb.step(Direction::East) | bb.step(Direction::West);
			lookup[i] = (temp | temp.step(Direction::North) | temp.step(Direction::South)) & ~bb;
		}
		return lookup;
	}();
	return lookup[to_underlying_type(from)];
}

constexpr Bitboard knight_attacks(Square form) {
	constexpr auto lookup = [] {
		std::array<Bitboard, square_count> lookup{};
		auto bb = Bitboard::square(Square::A1);
		for (size_t i = 0; i < square_count; i++, bb << 1) {
			auto east = bb.step(Direction::East);
			auto west = bb.step(Direction::West);
			auto attacks = (east | west) << 16;
			attacks = attacks | ((east | west) >> 16);
			east = bb.step(Direction::East);
			west = bb.step(Direction::West);
			attacks = attacks | ((east | west) << 8);
			attacks = attacks | ((east | west) >> 8);
			lookup[i] = attacks;
		}
		return lookup;
	}();
	return lookup[to_underlying_type(form)];
}

// MAYBE: use setwise pawn attacks.
constexpr Bitboard pawn_attacks(Square from, Color color) {
	constexpr auto lookup = [] {
		std::array<std::array<Bitboard, square_count>, color_count> lookup{};
		auto bb = Bitboard::square(Square::A1);
		for (size_t i = 0; i < square_count; i++, bb << 1) {
			lookup[to_underlying_type(Color::White)][i] =
				bb.step(Direction::Northeast) | bb.step(Direction::Northwest);
			lookup[to_underlying_type(Color::Black)][i] =
				bb.step(Direction::Southeast) | bb.step(Direction::Southwest);
		}
		return lookup;
	}();
	return lookup[to_underlying_type(color)][to_underlying_type(from)];
}

// TODO: Finish the slider attacks...

constexpr Bitboard diagonal_attacks(Square from, Bitboard occupance) {
	const auto mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const auto occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return diagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard antidiagonal_attacks(Square from, Bitboard occupance) {
	const auto mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const auto occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return antidiagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard rank_attacks(Square from, Bitboard occupance) {
	const auto mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const auto occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return rank_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard file_attacks(Square from, Bitboard occupance) {
	const auto mask = Bitboard::diagonal(Diagonal::B1H7).north_fill();
	const auto file = to_underlying_type(to_file(from));
	const auto occ = (mask & (occupance >> file)) >> 58;
	return Bitboard::empty();
	// return Bitboard(a_file_attacks[sq >> 3][occ].bits << file);
}
