import card.*
import playingCard.*

fun main(args: Array<String>)
{
    //Card

    val theFool  = Card("The Fool",Pair( 0,22))
    val theFoo2  = Card("The Fool",Pair( 0,22))
    val theMoon  = Card("The Moon",Pair(18,18))

    println("${theFool.p()} ${theMoon.p()}") // [The Fool] [The Moon]

    println(theFool == theMoon) //false
    println(theFool == theFoo2) //true
    println(theFool <  theMoon) //true
    println(theFool >= theMoon) //false

    //Playing card

    val card1 = PlayingCard(Suit.Heart, Rank.Ace)
    val card2 = PlayingCard(Suit.Heart, Rank.Two)
    println("${card1.p()}, ${card2.p()}, ${card2.value}") // [♥ A], [♥ 2], (2, 2)
    println(card1 >= card2) // false
    println(card1 == card1) // true

    val deck = DeckOfPlayingCards()

    deck.deck.forEach(
         {
            print("${it.p()} ") // Print the whole deck: [♠ A] [♠ 2] [♠ 3] [♠ 4] [♠ 5] [♠ 6] ... [♣ 8] [♣ 9] [♣10] [♣ J] [♣ Q] [♣ K]
         }
    )
    println("")

    // MiniJósda
    var majorArcana = MajorArcana() 
    
    var sum  = 0
    var last = Card("",Pair(0,0))
    for (i in 1..7) 
    {
        var card = majorArcana.pickRandomCard()
        print("${card.p()} ") // Kiír 7 random kártyát (lehet több egyforma): [The Lovers] [The Magician] [The Hierophant] [The Magician] [The Emperor] [The Chariot] [The Chariot]
        sum += if (last<card)
        {
          1
        }
        else
        { 
          -1
        }
        last=card
    }
    
    println("")
    
    //Sokkal nagyobb a "szerencse" valószínűsége (1. húzás után 1-ről indulunk, és a 0 is "szerencse")
    
    if (sum>=0){
      println("Szerencséd lesz!")
    }else{
      println("Balszerencséd lesz!")
    }

}