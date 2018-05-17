# Card Game Simulation
Simple simulation of standard 52-card deck (Spade, Heart, Club, Diamond) game with two player (Player and Computer).


## Card Rank
This table shows rank of each suit in order (_rank 1 will win against rank 2 and so on_).

|Rank|Suit      |Name    |
|:--:|:--------:|:------:|
|1   |&spades;  |Spade   |
|2   |&hearts;  |Heart   |
|3   |&clubs;   |Club    |
|4   |&diams;   |Diamond |


## Game Details
### Rules

- Each turn, players get 5 different cards.
- Each cards in players hand must have different number (one player cannot have 2 heart and 2 spade).
- Cards cannot be duplicate (there is no 2 hearts in one play).
- Played cards cannot be played again before deck is reset.

### Actions

- **Deal** - Each player get 5 new cards to be played
- **Compare** - Compare players cards and eliminate the same number cards with lower rank
- **Show result** - Calculate the score point of each players and determine the game result (Win, Lose, Draw)

### Result

- **Win** - When your player has more score point than computer
- **Lose** - When your player has less score point than computer
- **Draw** - When your score point equals to computer score point
