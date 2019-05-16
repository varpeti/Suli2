package playingCard

import card.*

class PlayingCard : Card
{
    constructor(suit: Suit, rank: Rank) : super(suit.str,rank.str,rank.value)
    {
    }
}