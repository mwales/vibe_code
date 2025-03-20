/**

Prompt 4:

Create me a header file for my Card.cpp class and a Makefile to build my project

*/


#include "Card.h"

#define CARD_HEIGHT 7

// Convert a Rank to a single character
char rankToChar(Rank rank) {
    switch(rank) {
        case Rank::Two:    return '2';
        case Rank::Three:  return '3';
        case Rank::Four:   return '4';
        case Rank::Five:   return '5';
        case Rank::Six:    return '6';
        case Rank::Seven:  return '7';
        case Rank::Eight:  return '8';
        case Rank::Nine:   return '9';
        case Rank::Ten:    return 'T';
        case Rank::Jack:   return 'J';
        case Rank::Queen:  return 'Q';
        case Rank::King:   return 'K';
        case Rank::Ace:    return 'A';
    }
    // Should never happen
    return '?';
}

// Convert a Suit to a single character
char const * suitToChar(Suit suit) {
    switch(suit) {
        case Suit::Clubs:    return "♣";
        case Suit::Diamonds: return "♦";
        case Suit::Hearts:   return "♥";
        case Suit::Spades:   return "♠";
    }
    return "?";
}

Card::Card(Rank rank, Suit suit, bool faceDown)
    : rank_(rank), suit_(suit), faceDown_(faceDown)
{
}

bool Card::isFaceDown() const {
    return faceDown_;
}

void Card::setFaceDown(bool faceDown) {
    faceDown_ = faceDown;
}

Rank Card::getRank() const {
    return rank_;
}

Suit Card::getSuit() const {
    return suit_;
}

// Display the card at (x, y) using ncurses ASCII art
void Card::display(int x, int y) const {
    // For simplicity, let's define a 7×5 card layout:

    // line 1 (top): " ______"
    // line 2: rank at (x+2), e.g. "|  A  |"
    // line 3: suit at (x+2), e.g. "|  H  |"
    // line 4: empty
    // line 5: bottom border " ‾‾‾‾‾‾"

    int deltaY = 0;
    if (faceDown_) {
        // Fill lines 2-4 with '#' to hide rank & suit
        for ( deltaY = 0; deltaY < CARD_HEIGHT; deltaY++ )
        {
            if (deltaY == 0) {
                mvprintw(y + deltaY, x, "-------");
                continue;
                }
            if (deltaY == CARD_HEIGHT - 1) {
                mvprintw(y + deltaY, x, "-------");
                continue;
                }
            mvprintw(y + deltaY, x, "|#####|");

        }

    } else {
        // Face-up card
        char r = rankToChar(rank_);
        char const * s = suitToChar(suit_);

        mvprintw(y + deltaY++, x, "-------"); // top border

        // line 2: place rank
        {
            // e.g. "|  A  |"
            char line2[8] = "|     |"; // 7 chars + null
            line2[1] = r;
            mvprintw(y + deltaY++, x, "%s", line2);
        }

        // line 3: place suit
        {
            // e.g. "|  S  |"
            char line3[8] = "|     |";
            mvaddstr(y + deltaY, x, line3);
            mvaddstr(y + deltaY++, x+1, s);
        }

        for (int i = 0; i < CARD_HEIGHT - 4; i++)
            mvprintw(y + deltaY++, x, "|     |");


        // line 5: bottom border
        mvprintw(y + deltaY, x, "-------");
    }
}

