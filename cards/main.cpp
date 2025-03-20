
#include <ncurses.h>
#include "Card.h"

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    // Create and display a few cards
    Card c1(Rank::Ace, Suit::Hearts);       // Face-up Ace of Hearts
    Card c2(Rank::Ten, Suit::Diamonds, true); // Face-down Ten of Diamonds

    c1.display(2, 2);   // top-left corner
    c2.display(12, 2);  // offset horizontally by 10 columns

    // Wait for user
    mvprintw(10, 2, "Press any key to exit...");
    getch();

    endwin();
    return 0;
}

