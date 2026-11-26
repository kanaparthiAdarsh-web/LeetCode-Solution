/*
 * AnyPush — AI explanation
 * This solution simulates the Stone Removal game. Players take turns removing a decreasing
 * number of stones (from 10 down to 1). We track remaining stones and the current turn
 * until no more moves are possible; the player whose turn it is then loses.
 *
 * Time Complexity: O(1). The game has a fixed maximum of 10 turns, independent of 'n'.
 * Space Complexity: O(1). Uses only a few constant variables.
 *
 * This approach is optimal because the game's limited and fixed move sequence allows
 * for direct simulation, achieving best-case complexity without complex game theory.
 * A more general (but naive) attempt might use dynamic programming, which is overkill
 * given the small, fixed number of turns.
 */

bool canAliceWin(int n) {
    int remove = 10;
    bool aliceTurn = true;
    
    while (n >= remove) {
        n -= remove;
        remove--;
        aliceTurn = !aliceTurn;
    }
    
    return !aliceTurn;
}
