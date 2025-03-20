
/**

Prompt 1:
I want a C++ class that we can print cards on the screen.  Lets assume our
screen is wide terminal 80 chars wide and 40 chars tall (about).  We can have
players.  WE will create the game in steps and I will help tell you what we
need at each part.  Vibe code me a C++ class that can display a hand of cards
at an x,y location on the screen.  Each card can be face down or face up.

(Chat GPT generated some useless windows code)

Prompt 2:

Hold up, hold up.  We are on Linux.  Get Windows out of here.  Just ncurses.
*/


#include <ncurses.h>
#include <string>
#include <vector>

// A simple Card class
class Card {
public:
    // rank & suit can be single chars (e.g. 'A'/'K' for rank, 'H'/'S' for suit),
    // or small strings. Just note that 2-char ranks (like "10") can shift
    // alignment if you don’t carefully adjust. We'll keep it simple here.
    Card(const std::string& rank, const std::string& suit, bool faceDown = false)
        : rank_(rank), suit_(suit), faceDown_(faceDown) {}

    bool isFaceDown() const { return faceDown_; }
    void setFaceDown(bool fd) { faceDown_ = fd; }

    std::string getRank() const { return rank_; }
    std::string getSuit() const { return suit_; }

private:
    std::string rank_;
    std::string suit_;
    bool faceDown_;
};

class CardHandDisplayer {
public:
    void addCard(const Card& card) {
        hand_.push_back(card);
    }

    // Display all cards, starting at (startX, startY), with partial overlap.
    void displayHand(int startX, int startY) const {
        // Each card is 9 columns wide, 5 rows tall
        // We'll overlap them by overlapOffset columns.
        const int overlapOffset = 3; // shift each card by 3 columns from the previous
        for (size_t i = 0; i < hand_.size(); ++i) {
            int x = startX + static_cast<int>(i) * overlapOffset;
            drawCard(hand_[i], x, startY);
        }
    }

private:
    // Draw a single card (face up or down) at (x, y).
    void drawCard(const Card& card, int x, int y) const {
        if (card.isFaceDown()) {
            // Face-down card
            // (9 columns wide total)
            const char* lines[5] = {
                " ________",  // 1 space + 8 underscores = 9 chars
                "|#######|",  // 9 chars
                "|#######|",  // 9 chars
                "|#######|",  // 9 chars
                " ‾‾‾‾‾‾‾‾"   // 1 space + 8 '‾' = 9 chars
            };
            for (int i = 0; i < 5; ++i) {
                mvaddstr(y + i, x, lines[i]);
            }
        } else {
            // Face-up card
            // Ranks & suits in top-left and bottom-right corners
            // We'll assume rank_ and suit_ are each 1 char for neat alignment,
            // e.g. rank_ = "A", suit_ = "H" for hearts. 
            // If they’re longer, you might want to adjust carefully.
            std::string rank = card.getRank();
            std::string suit = card.getSuit();
            
            // Build the 5 lines, each 9 columns wide
            // line 1: top border
            const char* topBorder = " ________"; // 1 space + 8 underscores = 9 columns

            // line 2: "|A H    |", inserting rank/suit
            // Just naive insertion: rank + " " + suit. 
            // If rank.size() + suit.size() > 2, you may see weird alignment.
            char line2[10];
            snprintf(line2, sizeof(line2), "|%s %s    |", rank.c_str(), suit.c_str());
            // If that goes over 9 columns, it’ll overflow. 
            // For safety, you might want to trim or do a safer logic.

            // line 3: blank interior
            const char* line3 = "|       |"; // 9 columns

            // line 4: bottom-right rank/suit
            char line4[10];
            snprintf(line4, sizeof(line4), "|    %s %s|", rank.c_str(), suit.c_str());
            // same caution about length

            // line 5: bottom border
            const char* bottomBorder = " ‾‾‾‾‾‾‾‾"; // 1 space + 8 '‾' = 9 columns

            // Print them with ncurses
            mvaddstr(y,     x, topBorder);
            mvaddstr(y + 1, x, line2);
            mvaddstr(y + 2, x, line3);
            mvaddstr(y + 3, x, line4);
            mvaddstr(y + 4, x, bottomBorder);
        }
    }

    std::vector<Card> hand_;
};

int main() {
    // init ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Create a displayer
    CardHandDisplayer displayer;
    // Add a few sample cards
    displayer.addCard(Card("A", "H"));   // Ace of Hearts face-up
    displayer.addCard(Card("K", "S"));   // King of Spades face-up
    displayer.addCard(Card("Q", "D", true)); // Queen of Diamonds face-down
    displayer.addCard(Card("7", "C"));   // 7 of Clubs face-up
    displayer.addCard(Card("T", "H"));   // 10 of Hearts (using 'T') face-up

    // Let’s display them at row=2, col=2
    displayer.displayHand(2, 2);

    // Wait for user input
    mvaddstr(10, 2, "Press any key to exit...");
    getch();

    endwin();
    return 0;
}

