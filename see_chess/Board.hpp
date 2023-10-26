#pragma once
#include "Bitboard.hpp"
#include <variant>

class Board {
private:
	Bitboard boards[8] = {};
	Color turn = Color::White;
	CastlingRights castling_rights = CastlingRights::Both;
	std::optional<File> en_passant = std::nullopt;
	uint8_t halfmove_clock = 0;
public:
	inline Bitboard get_bitboard(Color color) const {
		return boards[static_cast<size_t>(color)];
	}
	inline Bitboard get_bitboard(Piece piece) const {
		return boards[static_cast<size_t>(piece) + 2];
	}
	inline Color get_turn() const {
		return turn;
	}
	inline CastlingRights get_castling_rights() const {
		return castling_rights;
	}
	inline std::optional<File> get_en_passant() const {
		return en_passant;
	}
};
