#include <locale.h>    // for setlocale
#include <ncurses.h>
#include "Card.h"      // your Card class, with Rank & Suit enums, etc.

/**
 vibe me up a main that prints all 52 cards on the screen.  the delta y and x
 values should be variables i can easily change.  print 4 rows of cards, all
 anks on a row of a single suit
 */

int main() {
    // Enable UTF-8 in case you have special suit symbols
    // (If you're just using single chars like C/D/H/S, this is optional.)
    setlocale(LC_ALL, "");

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    // You can adjust these to space out the cards differently
    int startX = 2;
    int startY = 2;
    int deltaX = 4; // horizontal spacing between cards
    int deltaY = 9; // vertical spacing between rows (suits)

    // Define the suits in the order you want them displayed (top to bottom)
    Suit suits[4] = {
        Suit::Clubs,
        Suit::Diamonds,
        Suit::Hearts,
        Suit::Spades
    };

    // Define the ranks in the order you want them displayed (left to right)
    Rank ranks[13] = {
        Rank::Two,   Rank::Three, Rank::Four,  Rank::Five,
        Rank::Six,   Rank::Seven, Rank::Eight, Rank::Nine,
        Rank::Ten,   Rank::Jack,  Rank::Queen, Rank::King,
        Rank::Ace
    };

    // Loop over 4 suits (rows)
    for(int row = 0; row < 4; ++row) {
        // Loop over 13 ranks (columns)
        for(int col = 0; col < 13; ++col) {
            // Create a face-up Card and display it
            Card c(ranks[col], suits[row], false);
            int x = startX + col * deltaX;
            int y = startY + row * deltaY;
            c.display(x, y);
        }
    }

    // Show instructions & wait
    mvprintw(startY + 4*deltaY + 2, startX, "Press any key to exit...");
    refresh();
    getch();

    // Cleanup
    endwin();
    return 0;
}
