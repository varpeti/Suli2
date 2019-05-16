package playingCard

import card.*

class DeckOfPlayingCards
{
    var deck = Array<PlayingCard>(52, {PlayingCard(Suit.Spade,Rank.Ace)})
    
    constructor()
    {
        var i : Int = 0;
        enumValues<Suit>().forEach(
            { 
                val s = it
                enumValues<Rank>().forEach(
                    { 
                        val r = it
                        //println("[${s.str}${r.str}]")
                        this.deck[i]= PlayingCard(s,r)
                        i++
                    }
                )
            }
        )
    }
}

class MajorArcana
{
    var deck = Array<Card>(22, {Card(" ",Pair(0,0))})

    constructor()
    {
        //Enum azoknak való akik nem tudják a szövegszerkeztőjüket használni :)
        deck[0]  = (Card("The Fool", Pair(0,22)))
        deck[1]  = (Card("The Magician", Pair(1,1)))
        deck[2]  = (Card("The High Priestess", Pair(2,2)))
        deck[3]  = (Card("The Empress", Pair(3,3)))
        deck[4]  = (Card("The Emperor", Pair(4,4)))
        deck[5]  = (Card("The Hierophant", Pair(5,5)))
        deck[6]  = (Card("The Lovers", Pair(6,6)))
        deck[7]  = (Card("The Chariot", Pair(7,7)))
        deck[8]  = (Card("Strength", Pair(8,8)))
        deck[9]  = (Card("The Hermit", Pair(9,9)))
        deck[10] = (Card("Wheel of Fortune", Pair(10,10)))
        deck[11] = (Card("Justice", Pair(11,11)))
        deck[12] = (Card("The Hanged Man", Pair(12,12)))
        deck[13] = (Card("Death", Pair(13,13)))
        deck[14] = (Card("Temperance", Pair(14,14)))
        deck[15] = (Card("The Devil", Pair(15,15)))
        deck[16] = (Card("The Tower", Pair(16,16)))
        deck[17] = (Card("The Star", Pair(17,17)))
        deck[18] = (Card("The Moon", Pair(18,18)))
        deck[19] = (Card("The Sun", Pair(19,19)))
        deck[20] = (Card("Judgement", Pair(20,20)))
        deck[21] = (Card("The World", Pair(21,21)))
    }

    fun pickRandomCard() : Card
    {
        val id = (0..(deck.size-1)).random()
        return deck[id]
    }
}