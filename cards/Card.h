#ifndef CARD_H
#define CARD_H

#include <ncurses.h>  // for mvaddstr, etc.
#include <string>

// ------------------------------------------------
// Enums for Rank and Suit
// ------------------------------------------------
enum class Rank {
    Two, Three, Four, Five, Six, Seven, Eight, Nine,
    Ten, Jack, Queen, King, Ace
};

enum class Suit {
    Clubs, Diamonds, Hearts, Spades
};

// ------------------------------------------------
// Helper functions to convert enum -> single char
// ------------------------------------------------
char rankToChar(Rank rank);
char const * suitToChar(Suit suit);

// ------------------------------------------------
// Card class
// ------------------------------------------------
class Card {
public:
    Card(Rank rank, Suit suit, bool faceDown = false);

    bool isFaceDown() const;
    void setFaceDown(bool faceDown);

    Rank getRank() const;
    Suit getSuit() const;

    // Displays this card at (x, y) using ncurses ASCII art
    void display(int x, int y) const;

private:
    Rank rank_;
    Suit suit_;
    bool faceDown_;
};

#endif // CARD_H
