/**

Prompt 3:

Have the rank as a single letter (numbers, A, T, J, Q, K).  The suits should go
 on the line underneath the rank.  Give me a function that I can use to display
a card of a given rank suit (create me an enum for this) at an X,Y location on
the screen
*/



#include <ncurses.h>
#include <string>

// ------------------------------------------------
// 1) Enums for rank and suit
// ------------------------------------------------
enum class Rank {
    Two, Three, Four, Five, Six, Seven, Eight, Nine,
    Ten, Jack, Queen, King, Ace
};

enum class Suit {
    Clubs, Diamonds, Hearts, Spades
};

// ------------------------------------------------
// 2) Helper functions to convert enums -> single char
// ------------------------------------------------
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
    return '?'; // fallback
}

char suitToChar(Suit suit) {
    switch(suit) {
        case Suit::Clubs:    return 'C';
        case Suit::Diamonds: return 'D';
        case Suit::Hearts:   return 'H';
        case Suit::Spades:   return 'S';
    }
    return '?'; // fallback
}

// ------------------------------------------------
// 3) The function to display a card at (x, y)
// ------------------------------------------------
void displayCard(Rank rank, Suit suit, int x, int y, bool faceDown = false) {
    // Card dimensions: 7 columns wide, 5 rows tall
    //   line 1: " ______"
    //   line 2: "|  R  |"
    //   line 3: "|  S  |"
    //   line 4: "|     |"
    //   line 5: " ‾‾‾‾‾‾"
    // If faceDown, lines 2-4 become "|#####|"

    if (faceDown) {
        // Face-down card
        mvaddstr(y + 0, x, " ______");  // 7 chars
        mvaddstr(y + 1, x, "|#####|");
        mvaddstr(y + 2, x, "|#####|");
        mvaddstr(y + 3, x, "|#####|");
        mvaddstr(y + 4, x, " ‾‾‾‾‾‾");
    } else {
        // Face-up card
        // Put rank on line 2, suit on line 3
        char r = rankToChar(rank);
        char s = suitToChar(suit);

        mvaddstr(y + 0, x, " ______");  // top
        // Build line with rank
        {
            // e.g. "|  A  |"
            // We'll place rank in the 3rd column:
            char line2[8] = "|     |"; // 7 chars + null terminator
            line2[2] = r; // place rank at offset 2
            mvaddstr(y + 1, x, line2);
        }
        // Build line with suit
        {
            // e.g. "|  S  |"
            char line3[8] = "|     |";
            line3[2] = s; 
            mvaddstr(y + 2, x, line3);
        }
        // Empty line
        mvaddstr(y + 3, x, "|     |");
        // Bottom
        mvaddstr(y + 4, x, " ‾‾‾‾‾‾");
    }
}

// ------------------------------------------------
// 4) Demo usage in main()
// ------------------------------------------------
int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    // Display some example cards
    // Face-up Ace of Hearts at (2,2)
    displayCard(Rank::Ace, Suit::Hearts, 2, 2, false);

    // Face-down Ten of Diamonds at (12,2)
    displayCard(Rank::Ten, Suit::Diamonds, 12, 2, true);

    // Display King of Spades at (2,9) face-up
    displayCard(Rank::King, Suit::Spades, 2, 9, false);

    // Wait for the user so we can see the cards
    mvaddstr(15, 2, "Press any key to exit...");
    getch();

    endwin(); // Cleanup ncurses
    return 0;
}
