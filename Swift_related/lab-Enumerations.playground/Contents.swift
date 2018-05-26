//: Playground - noun: a place where people can play

import UIKit

enum Suit {
    case clubs,spades,diamonds,hearts
}

var cardInHand: Suit = .hearts
cardInHand = .spades

func getFortune(cardSuit: Suit) {
    switch cardSuit {
    case .clubs:
        print("clubs")
    case .diamonds:
        print("diamonds")
    case .hearts:
        print("hearts")
    case .spades:
        print("spades")
    }
}

struct Card {
    var suit: Suit
    enum Value {
        case ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king
    }
    
    var value: Value
}
var card1 = Card(suit: .diamonds, value: .jack)
print(card1.value)

struct SwimmingWorkout {
    var distance: Double
    var time: Double
    enum Stroke {
        case freestyle, butterfly, backstroke, breaststroke
    }
    var stroke: Stroke
    func save(){
        switch stroke {
        case .freestyle:
            freeStyleWorkouts.append(self)
        case .butterfly:
            butterflyWorkouts.append(self)
        case .backstroke:
            backstrokeWorkouts.append(self)
        case .breaststroke:
            breaststrokeWorkouts.append(self)
        }
    }
}

var freeStyleWorkouts: [SwimmingWorkout] = []
var butterflyWorkouts: [SwimmingWorkout] = []
var backstrokeWorkouts: [SwimmingWorkout] = []
var breaststrokeWorkouts: [SwimmingWorkout] = []

var swim1 = SwimmingWorkout(distance: 200, time: 60, stroke: .freestyle)
swim1.save()
print(freeStyleWorkouts[0].stroke)




