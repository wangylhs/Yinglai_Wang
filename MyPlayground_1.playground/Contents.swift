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
let greeting = "I have \(float_const + first) friends"
print(greeting)

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

