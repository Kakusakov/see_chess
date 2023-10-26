#pragma once
#include "Enums.hpp"

#include <bit>
#include <optional>

class Bitboard {
private:
	uint64_t bits = 0;
private:
	friend Bitboard operator|(Bitboard a, Bitboard b);
	friend Bitboard operator&(Bitboard a, Bitboard b);
	friend Bitboard operator^(Bitboard a, Bitboard b);

	explicit inline constexpr Bitboard(uint8_t bits) : bits(bits) {}
public:
	inline constexpr Bitboard() : bits(0) {}
	explicit inline constexpr Bitboard(Square square) {
		bits = static_cast<uint8_t>(1) << static_cast<uint8_t>(square);
	}
public:
	inline constexpr operator bool() const {
		return bits != 0;
	}
	inline Bitboard& operator|=(Bitboard other) {
		bits |= other.bits;
		return *this;
	}
	inline Bitboard& operator&=(Bitboard other) {
		bits &= other.bits;
		return *this;
	}
	inline Bitboard& operator^=(Bitboard other) {
		bits ^= other.bits;
		return *this;
	}
public:
	inline std::optional<Square> bitscan(Bitboard bitboard) const {
		if (!bitboard) return std::nullopt;
		return std::optional<Square>{static_cast<Square>(std::countr_zero(bitboard.bits))};
	}
	inline Bitboard with_reset() const {
		return Bitboard(bits & (bits - 1));
	}
private:
	static const uint64_t b_file = 0x0202020202020202;

	static const Bitboard diagonal_mask_ex[64];
	static const Bitboard antidiagonal_mask_ex[64];
	static const Bitboard rank_mask_ex[64];

	static const Bitboard fill_up_attacks[8][64];
	static const Bitboard a_file_attacks[8][64];
public:
	static inline Bitboard diagonal_attacks(Square from, Bitboard occupance) {
		const size_t sq = static_cast<size_t>(from);
		const uint64_t occ = (diagonal_mask_ex[sq] & occupance).bits * b_file >> 58;
		return diagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
	}
	static inline Bitboard antidiagonal_attacks(Square from, Bitboard occupance) {
		const size_t sq = static_cast<size_t>(from);
		const uint64_t occ = (antidiagonal_mask_ex[sq] & occupance).bits * b_file >> 58;
		return antidiagonal_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
	}
	static inline Bitboard rank_attacks(Square from, Bitboard occupance) {
		const size_t sq = static_cast<size_t>(from);
		const uint64_t occ = (rank_mask_ex[sq] & occupance).bits * b_file >> 58;
		return rank_mask_ex[sq] & fill_up_attacks[sq & 7][occ];
	}
	static inline Bitboard file_attacks(Square from, Bitboard occupance) {
		const uint64_t a_file = 0x0101010101010101;
		const uint64_t diag_c2h7 = 0x0080402010080400;
		const size_t sq = static_cast<size_t>(from);
		const uint64_t occ = (diag_c2h7 * a_file & (occupance.bits >> (sq & 7))) >> 58;
		return Bitboard(a_file_attacks[sq >> 3][occ].bits << (sq & 7));
	}
private:
	static const Bitboard pawn_attack[2][64];
	static const Bitboard knight_attack[64];
	static const Bitboard king_attack[64];
public:
	static inline Bitboard pawn_attacks(Square from, Color color) {
		return pawn_attack[static_cast<size_t>(color)][static_cast<size_t>(from)];
	}
	static inline Bitboard knight_attacks(Square from) {
		return knight_attack[static_cast<size_t>(from)];
	}
	static inline Bitboard king_attacks(Square from) {
		return king_attack[static_cast<size_t>(from)];
	}
	static inline Bitboard rook_attacks(Square from, Bitboard occupance) {
		return file_attacks(from, occupance) | rank_attacks(from, occupance);
	}
	static inline Bitboard bishop_attacks(Square from, Bitboard occupance) {
		return file_attacks(from, occupance) | rank_attacks(from, occupance);
	}
	static inline Bitboard queen_attacks(Square from, Bitboard occupance) {
		return rook_attacks(from, occupance) | bishop_attacks(from, occupance);
	}
};

inline Bitboard operator|(Bitboard a, Bitboard b) {
	return Bitboard(a.bits | b.bits);
}
inline Bitboard operator&(Bitboard a, Bitboard b) {
	return Bitboard(a.bits & b.bits);
}
inline Bitboard operator^(Bitboard a, Bitboard b) {
	return Bitboard(a.bits ^ b.bits);
}
