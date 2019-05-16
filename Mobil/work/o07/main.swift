enum Rank: Int
{
  case Ace = 1
  case Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten
  case Jack, Queen, King

  func value() -> Int
  {
    switch self
    {
      case .Ace : return 11
      case .Jack, .Queen, .King : return 10
      case let x where x.rawValue>=2 && x.rawValue<=10 : return rawValue
    }
  }
}

let card = Rank.Ten
let rawcard = card.rawValue

print(card, rawcard, card.value())

struct Point_s
{
  var x,y : Int
}

let point_s = Point_s(x: 1,y: 2)
//point_s.x = 9 nem változtatható az attributoma se
print(point_s)

struct FixPoint_s
{
  let x,y : Int
}

var fixPoint_s = FixPoint_s(x: 9,y: 8)
//fixPoint_s.x = 9 nem változtatható az attributoma
print(point_s)

//*///

structRect{varorigin=Point()varsize=Size()varcenter:Point{get{letcenterX=origin.x+ (size.width/2)letcenterY=origin.y+ (size.height/2)returnPoint(x:centerX,y:centerY)}set(newCenter) {origin.x=newCenter.x-(size.width/2)origin.y=newCenter.y-(size.height/2)}}}structPoint{varx=0.0,y=0.0}structSize{varwidth=0.0,height=0.0}

//*///

struct Counter
{
  var count: Int = 0

  // Vagy class vagy mutating kell (kizáró)
  mutating func increment() 
  {
    count += 1
  }
}

var counter = Counter()
print(counter)
counter.increment()
print(counter)


//*///

struct Counter
{
  var count: Int

  mutating func increment() // Vagy class vagy mutating kell (kizáró)
  {
    count += 1
  }
  init(count: Int)
  {
    self.count = count
  }
  init()
  {
    self.count = 0
  }
}

var counter = Counter()
print(counter)
counter.increment()
print(counter)


//*///

class Counter
{
  var count: Int = 0

  func increment() 
  {
    count += 1
  }
}

class Better : Counter
{
  override func increment()
  {
    count += 2
  }
}

var better = Better()
print(better.count)
better.increment()
print(better.count)

