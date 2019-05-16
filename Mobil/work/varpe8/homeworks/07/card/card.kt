package card

open class Card
{
    // A legtöbb kártyában van többértékűség (Ace, TheFool, Joker stb)
    val value : Pair<Int, Int>
    // A legtöbb kártyában van rank és suit
    val rank : String
    val suit : String

    constructor(suit: String, rank: String, value: Pair<Int, Int>)
    {
        this.value = value
        this.rank = rank
        this.suit = suit
    }

    constructor(rank: String, value: Pair<Int, Int>) //Second constructor, in case of no Suit
    {
        this.value = value
        this.rank = rank
        this.suit = ""
    }

    // Kiíráshoz
    fun p() : String
    {
        return "[${suit}${rank}]"
    }

    override operator fun equals(other: Any?) =
        when (other) 
        {
            is Card -> this.value == other.value
            else -> throw Exception("")
        }

    operator fun compareTo(other: Card) = 
        this.value.first - other.value.first
    
}