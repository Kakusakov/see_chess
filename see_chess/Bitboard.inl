#include "Bitboard.hpp"
#include <cassert>
#include <bit>

constexpr Bitboard Bitboard::empty() {
	return Bitboard(0);
}
constexpr Bitboard Bitboard::filled() {
	return Bitboard(UINT64_MAX);
}
constexpr Bitboard Bitboard::square(Square square) {
	// PERF: shift may be replaced by table lookup.
	const uint64_t magic = 0x1;
	return Bitboard(magic << to_underlying_type(square));
}
constexpr Bitboard Bitboard::rank(Rank rank) {
	// PERF: shift may be replaced by table lookup.
	const uint64_t magic = 0xFF;
	return Bitboard(magic << (to_underlying_type(rank) * 8));
}
constexpr Bitboard Bitboard::file(File file) {
	// PERF: shift may be replaced by table lookup.
	const uint64_t magic = 0x0101010101010101;
	return Bitboard(magic << to_underlying_type(file));
}
constexpr Bitboard Bitboard::diagonal(Diagonal diagonal) {
	// PERF: shift may be replaced by table lookup.
	const uint64_t magic = 0x8040201008040201;
	const int diag = 7 - to_underlying_type(diagonal);
	return Bitboard(magic).generalized_shift(diag * 8);
}
constexpr Bitboard Bitboard::antidiagonal(Antidiagonal antidiagonal) {
	// PERF: shift may be replaced by table lookup.
	const uint64_t magic = 0x0102040810204080;
	const int antidiag = to_underlying_type(antidiagonal) - 7;
	return Bitboard(magic).generalized_shift(antidiag * 8);
}
constexpr Bitboard Bitboard::operator~() const {
	return Bitboard(~value);
}
constexpr Bitboard Bitboard::operator|(Bitboard other) const {
	return Bitboard(value | other.value);
}
constexpr Bitboard Bitboard::operator&(Bitboard other) const {
	return Bitboard(value & other.value);
}
constexpr Bitboard Bitboard::operator^(Bitboard other) const {
	return Bitboard(value ^ other.value);
}
constexpr Bitboard Bitboard::operator>>(int shift) const {
	assert(shift >= 0 && shift < 64);
	return Bitboard(value >> shift);
}
constexpr Bitboard Bitboard::operator<<(int shift) const {
	assert(shift >= 0 && shift < 64);
	return Bitboard(value << shift);
}
constexpr bool Bitboard::operator==(Bitboard other) const {
	return value == other.value;
}
constexpr bool Bitboard::is_empty() const {
	return *this == Bitboard::empty();
}
constexpr bool Bitboard::is_filled() const {
	return *this == Bitboard::filled();
}
constexpr bool Bitboard::has_square(Square square) const {
	return !(*this & Bitboard::square(square)).is_empty();
}
constexpr int Bitboard::popcount() const {
	return std::popcount(value);
}
constexpr Square Bitboard::bitscan() const {
	assert(value);
	return static_cast<Square>(std::countr_zero(value));
}
constexpr Bitboard Bitboard::generalized_shift(int shift) const {
	assert(shift > -64 && shift < 64);
	return Bitboard(shift >= 0 ? value << shift : value >> -shift);
}
constexpr Bitboard Bitboard::reset_bit() const {
	return Bitboard(value & (value - (uint64_t)1));
}
constexpr Bitboard Bitboard::step(Direction direction) const {
	const Bitboard bb = generalized_shift(to_raw_offset(direction));
	switch (direction) {
	case Direction::East:
	case Direction::Northeast:
	case Direction::Southwest:
		return bb & ~Bitboard::file(File::A);
	case Direction::West:
	case Direction::Northwest:
	case Direction::Southeast:
		return bb & ~Bitboard::file(File::H);
	case Direction::North:
	case Direction::South:
		return bb;
	default:
		assert(false);
	}
}
constexpr Bitboard Bitboard::north_fill() const {
	return Bitboard(Bitboard::file(File::A).value * value);
}

//static inline Bitboard diagonal_attacks(Square from, Bitboard occupance) {
//	const size_t sq = static_cast<size_t>(from);
//	const Bitboard occ = (((diagonal_mask_ex[sq] & occupance) * b_file) >> 58).get_bits();
//	return diagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
//}
//static inline Bitboard antidiagonal_attacks(Square from, Bitboard occupance) {
//	const size_t sq = static_cast<size_t>(from);
//	const uint64_t occ = (antidiagonal_mask_ex[sq] & occupance).bits * b_file >> 58;
//	return antidiagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
//}
//static inline Bitboard rank_attacks(Square from, Bitboard occupance) {
//	const size_t sq = static_cast<size_t>(from);
//	const uint64_t occ = (rank_mask_ex[sq] & occupance).bits * b_file >> 58;
//	return rank_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
//}
//static inline Bitboard file_attacks(Square from, Bitboard occupance) {
//	const uint64_t a_file = 0x0101010101010101;
//	const uint64_t diag_c2h7 = 0x0080402010080400;
//	const size_t sq = static_cast<size_t>(from);
//	const uint64_t occ = (diag_c2h7 * a_file & (occupance.bits >> (sq & 7))) >> 58;
//	return Bitboard(a_file_attacks[sq >> 3][occ].bits << (sq & 7));
//}
//static const Bitboard pawn_attack[2][64];
//static const Bitboard knight_attack[64];
//static const Bitboard king_attack[64];
//static inline Bitboard pawn_attacks(Square from, Color color) {
//	return pawn_attack[static_cast<size_t>(color)][static_cast<size_t>(from)];
//}
//static inline Bitboard knight_attacks(Square from) {
//	return knight_attack[static_cast<size_t>(from)];
//}
//static inline Bitboard king_attacks(Square from) {
//	return king_attack[static_cast<size_t>(from)];
//}
//static inline Bitboard rook_attacks(Square from, Bitboard occupance) {
//	return file_attacks(from, occupance) | rank_attacks(from, occupance);
//}
//static inline Bitboard bishop_attacks(Square from, Bitboard occupance) {
//	return file_attacks(from, occupance) | rank_attacks(from, occupance);
//}
//static inline Bitboard queen_attacks(Square from, Bitboard occupance) {
//	return rook_attacks(from, occupance) | bishop_attacks(from, occupance);
//}
