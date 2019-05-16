package playingCard

enum class Rank(val value: Pair<Int,Int>,val str : String) 
{
    // BlackJack értékek
    Ace(Pair(1,11)," A"),
    Two(Pair(2,2)," 2"), Three(Pair(3,3)," 3"), Four(Pair(4,4)," 4"), Five(Pair(5,5)," 5"), Six(Pair(6,6)," 6"), Seven(Pair(7,7)," 7"), Eight(Pair(8,8)," 8"), Nine(Pair(9,9)," 9"), Ten(Pair(10,10),"10"),
    Jack(Pair(10,10)," J"), Queen(Pair(10,10)," Q"), King(Pair(10,10)," K")
}