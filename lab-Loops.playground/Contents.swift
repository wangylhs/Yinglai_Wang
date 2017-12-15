//: Playground - noun: a place where people can play

import UIKit

let alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
for (index,letter) in alphabet.characters.enumerated() {
    if index % 2 == 0{
        print("\(index)  \(letter)")
    }
}
var stateAndCapial:[String:String] = ["IN":"Indianapolis","IL":"SpringField","CA":"Sacramento"]
for (state,capital) in stateAndCapial {
    print("\(state)  \(capital)")
}
let movements: [String] = ["Walking", "Running", "Swimming", "Cycling", "Skiing", "Climbing"]
for move in movements {
    print(move)
}
let lowHR = 110
let highHR = 125
var movementHeartRates: [String: Int] = ["Walking": 85, "Running": 120, "Swimming": 130, "Cycling": 128, "Skiing": 114, "Climbing": 129]
for (type, rate) in movementHeartRates {
    if rate > lowHR && rate < highHR {
        print("You could go \(type).")
    }
    print("Heart rate is \(rate) during \(type)")
}
while true {
    var dice =  Int(arc4random_uniform(6)+1)
    print(dice)
    if dice == 1 {
        break
    }
}
let cadence: Double = 180
var testSteps = 0
while testSteps < 10 {
    print("Take a step")
    testSteps += 1
    Thread.sleep(forTimeInterval: 60/cadence)
}