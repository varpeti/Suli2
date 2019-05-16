//*/// Cards

class Card
{
  // A legtöbb kártyában van többértékűség (Ace, TheFool, Joker stb)
  let value: (Int, Int)
  // A legtöbb kártyában van rank és suit
  let rank: String
  let suit: String

  init(suit: String, rank: String, value: (Int, Int))
  {
    self.value = value
    self.rank = rank
    self.suit = suit
  }

  init(rank: String, value: (Int, Int))
  {
    self.value = value
    self.rank = rank
    self.suit = ""
  }

  // Kiíráshoz
  func p() -> String
  {
    return "[\(suit)\(rank)]"
  }

  // Összehasonlítás (a tuplesekkel jól megy)
  static func ==(lhs: Card, rhs: Card) -> Bool 
  {
    return lhs.value==rhs.value
  }
  static func <(lhs: Card, rhs: Card) -> Bool 
  {
    return lhs.value<rhs.value
  }
  static func >(lhs: Card, rhs: Card) -> Bool 
  {
    return lhs.value>rhs.value
  }
  static func <=(lhs: Card, rhs: Card) -> Bool 
  {
    return lhs.value<=rhs.value
  }
  static func >=(lhs: Card, rhs: Card) -> Bool 
  {
    return lhs.value>=rhs.value
  }
  
}

//*/// Playing Cards

// "CaseIterable after the enumeration’s name and Swift exposes a collection of all the cases as an allCases property of the enumeration type."
enum Rank: Int, CaseIterable
{
  case Ace = 1
  case Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten
  case Jack, Queen, King

  // BlackJack értékek
  func value() -> (Int, Int)
  {
    switch self
    {
      case .Ace : return (0, 11)
      case .Jack, .Queen, .King : return (10, 10)
      default : return (rawValue, rawValue)
    }
  }

  func name() -> String
  {
    switch self
    {
      case .Ace   : return " A"
      case .Jack  : return " J"
      case .Queen : return " Q"
      case .King  : return " K"
      case .Ten   : return "10"
      default     : return " \(rawValue)"
    }
  }
}

enum Suit: String, CaseIterable
{
  case Spade, Heart, Diamond, Club

  func name() -> String
  {
    //I \u{2665} Unicode
    switch self
    {
      case .Spade   : return "\u{2660}"
      case .Heart   : return "\u{2665}"
      case .Diamond : return "\u{2666}"
      case .Club    : return "\u{2663}"
    }
  }
}

class PlayingCard : Card
{
  init(suit : Suit, rank : Rank)
  {
    super.init(suit: suit.name(),rank: rank.name(),value: rank.value())
  }
}

//*/// Decks

class DeckOfPlayingCards
{
  var deck : [PlayingCard] = []
  init()
  {
    for s in Suit.allCases 
    {
      for r in Rank.allCases
      {
        deck.append(PlayingCard(suit: s, rank: r))
      }
    }
  }
  func p(_ id : Int) -> String
  {
    return deck[id].p()
  }
}

class MajorArcana
{
  var deck: [Card] = []
  init()
  {
    //Enum azoknak való akik nem tudják a szövegszerkeztőjüket használni :)
    deck.append(Card(rank: "The Fool", value: (0,22)))
    deck.append(Card(rank: "The Magician", value: (1,1)))
    deck.append(Card(rank: "The High Priestess", value: (2,2)))
    deck.append(Card(rank: "The Empress", value: (3,3)))
    deck.append(Card(rank: "The Emperor", value: (4,4)))
    deck.append(Card(rank: "The Hierophant", value: (5,5)))
    deck.append(Card(rank: "The Lovers", value: (6,6)))
    deck.append(Card(rank: "The Chariot", value: (7,7)))
    deck.append(Card(rank: "Strength", value: (8,8)))
    deck.append(Card(rank: "The Hermit", value: (9,9)))
    deck.append(Card(rank: "Wheel of Fortune", value: (10,10)))
    deck.append(Card(rank: "Justice", value: (11,11)))
    deck.append(Card(rank: "The Hanged Man", value: (12,12)))
    deck.append(Card(rank: "Death", value: (13,13)))
    deck.append(Card(rank: "Temperance", value: (14,14)))
    deck.append(Card(rank: "The Devil", value: (15,15)))
    deck.append(Card(rank: "The Tower", value: (16,16)))
    deck.append(Card(rank: "The Star", value: (17,17)))
    deck.append(Card(rank: "The Moon", value: (18,18)))
    deck.append(Card(rank: "The Sun", value: (19,19)))
    deck.append(Card(rank: "Judgement", value: (20,20)))
    deck.append(Card(rank: "The World", value: (21,21)))
  }

  func drawRandomCard() -> Card
  {
    let id = Int.random(in: 0..<deck.count)
    let card = deck[id]
    deck.remove(at: id)
    return card
  }
}

//*/// Test

let theFool = Card(rank: "The Fool", value: ( 0,22))
let theMoon = Card(rank: "The Moon", value: (18,18))
print(theFool.p(),theMoon.p())
print(theFool <  theMoon)
print(theFool == theMoon)
print("\n")

let card1 = PlayingCard(suit: Suit.Heart, rank: Rank.Ace)
let card2 = PlayingCard(suit: Suit.Heart, rank: Rank.Two)
print(card1.p(), card2.p(), card2.value)
print(card1 >= card2)
print(card1 == card1)
print("\n")

for s in Suit.allCases 
{
    print(s,terminator:", ")
}
print("\n")

var deck = DeckOfPlayingCards()

for i in 0..<52
{
  print(deck.p(i), terminator:", ")
}
print("\n")

// MiniJósda
var majorArcana = MajorArcana() 

var sum  = 0
var last = Card(rank: "",value: (0,0))
for _ in 0..<7
{
  let card = majorArcana.drawRandomCard()
  print(card.p(),terminator:", ")
  if (last<card)
  {
    sum+=1
  }
  else
  {
    sum-=1
  }
  last=card
  //print(sum, terminator:" ")
}
print("")
//Sokkal nagyobb a "szerencse" valószínűsége (1. húzás után 1-ről indulunk, és a 0 is "szerencse")
if (sum>=0)
{
  print("Szerencséd lesz!")
}
else
{
  print("Balszerencséd lesz!")
}
print("\n")