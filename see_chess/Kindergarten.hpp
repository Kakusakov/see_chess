#pragma once
#include "Bitboard.hpp"
#include <array>

constexpr Bitboard king_attacks(Square from) {
	constexpr std::array<Bitboard, square_count> lookup = [] {
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
	constexpr std::array<Bitboard, square_count> lookup = [] {
		std::array<Bitboard, square_count> lookup{};
		auto bb = Bitboard::square(Square::A1);
		for (size_t i = 0; i < square_count; i++, bb << 1) {
			Bitboard east = bb.step(Direction::East);
			Bitboard west = bb.step(Direction::West);
			Bitboard attacks = (east | west) << 16;
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

// TODO: Finish the slider attacks...

constexpr Bitboard diagonal_attacks(Square from, Bitboard occupance) {
	const Bitboard mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const Bitboard occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return diagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard antidiagonal_attacks(Square from, Bitboard occupance) {
	const Bitboard mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const Bitboard occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return antidiagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard rank_attacks(Square from, Bitboard occupance) {
	const Bitboard mask = Bitboard::diagonal(to_diagonal(from)) & ~Bitboard::square(from);
	const Bitboard occ = (((mask & occupance).north_fill().step(Direction::East)) >> 58);
	return Bitboard::empty();
	//return rank_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
}
constexpr Bitboard file_attacks(Square from, Bitboard occupance) {
	return Bitboard::empty();
	/*const uint64_t a_file = 0x0101010101010101;
	const uint64_t diag_c2h7 = 0x0080402010080400;
	const size_t sq = static_cast<size_t>(from);
	const uint64_t occ = (diag_c2h7 * a_file & (occupance.bits >> (sq & 7))) >> 58;
	return Bitboard(a_file_attacks[sq >> 3][occ].bits << (sq & 7));*/
}
