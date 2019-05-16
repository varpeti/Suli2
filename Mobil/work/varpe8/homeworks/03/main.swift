import Foundation

var input = 
[
  [0, -1, 1, -2, 3, -5, 8, -13, 21, -34],       // +-fibo
  [12, 6, 3, 10, 5, 16, 8, 4, 2, 1],            // Collatz(12)
  [-12, -7, -2, -12, -2, -21, 0, -17, 19, -35]  // [0]-[1]
]
//print(type(of: input))

//*///
// Bool (?)
func kiir1(input : Array<Array<Int>>, fun : (Array<Int>) -> Int )
{
  var overall = [Int]()

  //in ararys
  var a = 0
  for array in input
  {
    overall.insert(fun(array), at: a)
    print(a, overall[a])
    a=a+1
  }
  //overall
  print("s",fun(overall))
}
//print(type(of: kiir) )

//*///

func max(array: [Int]) -> Int 
{
  var cMax = array[0]
  for i in array
  {
      if i > cMax 
      {
          cMax = i
      }
  }
  return cMax
}

func sum(array: [Int]) -> Int
{
  var sum = 0
  for i in array
  {
      sum = sum + i
  }
  return sum
}

func avg(array: [Int]) -> Int
{
  return sum(array: array) / array.count
}

//*///

func replaceTheSmallestWithZero(input : inout Array<Array<Int>>)
{
  var min = (x: 0, y: 0, val: input[0][0])
  var x = 0
  for array in input
  {
    var y = 0
    for i in array
    {
      if min.val > i
      {
        min.val = i
        min.x = x
        min.y = y
      }
      y=y+1
    }
    x=x+1
  }
  print(min)
  input[min.x][min.y] = 0
}

//*///

func kiir2(input : Array<Array<Int>>, fil: (Int) -> Bool)
{
  var a = 0
  for array in input
  {
    print(a, array.filter(fil))
    a=a+1
  }
}

//*///

func love(i: Int) -> Bool
{
  return i<3//you
}

func rand(i: Int) -> Bool
{
  return love(i: Int.random(in: 0..<6))
}

//*///

print("### Functions:")
print("\nMax")
kiir1(input: input, fun: max)
print("\nSum")
kiir1(input: input, fun: sum)
print("\nAvg")
kiir1(input: input, fun: avg) //overall: average of averages

print("\n### Replace the smallest with zero")
replaceTheSmallestWithZero(input: &input)

print("\n### Filters:")
print("\nLove")
kiir2(input: input,fil: love)
print("\nEven")
kiir2(input: input,fil: {$0%2==0})
print("\nRandom")
kiir2(input: input,fil: rand)