var a:[Int] = [2, 3]
print(a, a[1])

var b = (1, 4)
print(b)
//print(b[1])
//print(b(1))

var b1 = 0
var b2 = 0
(b1, b2) = b
print(b1,b2)

var c = (2, "alma")
print(c)

//Dic

var dic =
[
  2: "k",
  3: "h",
  4: "f"
]

print(dic, dic[2]!)
if dic[1] != nil 
{
  print(dic[1]!)
}else
{
  print("nil")
}

var matrix =
[
  [1, 2 ,3],
  [4, 5, 6],
  [7, 8, 9]
]
print(matrix)

for vector in matrix
{
  for scalar in vector
  {
    print(scalar)
  }
}

var dic2 = 
[
  "asd" : [1, 2, 3],
  "boo" : [4, 3],
  "n"   : [0, 0, 0]
]
print(dic2)

for (name, vec) in dic2
{
  print(name)
  for sca in vec
  {
    print(sca)
  }
}

var food = "red pepper"
var msg = ""

switch food
{
  case "apple" : msg = "apple"
  case let a where a.hasSuffix("pepper") :
    msg = "asd"
  default :
    msg = "nil"
}
print(msg)

func greet(name n: String, day d: String) -> String
{
  return "Hello \(n) its a \(d)!"
}

print( greet(name:"Bob",day:"asd") )

func sumOf (numbers: Int ...) -> Int
{
  var sum = 0
  for num in numbers
  {
    sum += num
  }
  return sum
}

print( sumOf(numbers: 1,2,3,4,5,6,7) )


func funIO (name: inout String)
{
  print(name)
  name = "alma"
}

var nev = "asdasd"
funIO(name: &nev)
print(nev)

func funInc () -> ((Int) -> Int)
{
  func addOne(number: Int) -> Int
  {
    return number + 1
  }
  return addOne
}

var i = 99
var f = funInc()
print( f(i) )