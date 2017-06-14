//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"
print("Hello, World!")

let myCounstant = 42
let float_const: float_t = 4.5
var myVariable = 42
myVariable = 50

let label = "length is "
let len = 90
let len_label = label + String(len)

let first: float_t = 1.5
//let greeting = "I have \(float_const + first) friends"

// swift 4 supports 3 quotes
/*let sentences = """
                This
                takes multiple lines.
                (") can appear here with no problem.
                I still have friends.
                """
print(sentences)
 */

var shoppingList = ["water","potato","orange juice","cracker"];
shoppingList[0] = "bottled water"
print(shoppingList)
var occupations = [
        "Mick": "Programmer",
        "Jhon": "Engineer",
        "Ted": "Mechanic"
]
print(occupations)
//create empty array or dictionary
let emptyArray = [String]()
let emptyDictionary = [String: Float]()
occupations = [:]
print(occupations)

let individualScores = [1,2,3,4,5]
var teamScore = 0

for score in individualScores{
    if score > 3 {
        teamScore += score
    } else {
        teamScore += 1
    }
}
print(teamScore)

var optionalString: String? = "Hello"
print(optionalString == nil)

var optionalName: String? = nil
var greeting = "Hello"
if let name = optionalName {
    greeting = "Hello, \(name)"
} else {
    greeting = "Hello, \"nil\""
}
print(greeting)

let nickName: String? = "John"
let fullName: String = "Johnathon Smith"
let informalGreeting = "Hi \(nickName ?? fullName)"

let vegetable = "red onion"
switch vegetable {
case "carrot":
    print("carrot............")
case "onion","potato":
    print("Stew with meat would be good")
case let x where x.hasSuffix("pepper"):
    print("Is \(x) spicy?")
default:
    print("everything tastes good in soup.")
}

var numDic = [
    "Prime": [2,3,5,7,11,13,17],
    "Fibonacci": [1,1,2,3,5,8,13],
    "Square":[1,4,9,16,25,36],
]
var largest = 0
var largestKind: String = "NULL"
for (kind, numbers) in numDic{
    for number in numbers {
        if number > largest {
            largest = number
            largestKind = kind
        }
    }
}
//numDic["largest"] = [largest]
print("largestKind is \(largestKind) and largest number is \(largest)")


