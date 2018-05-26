//: Playground - noun: a place where people can play

import UIKit

func greeting(greeting: String?, name: String){
    if let greeting = greeting {
        print("\(greeting), my name is \(name)")
    }else{
        print("Hello, my name is \(name)")
    }
}

greeting(greeting: "Hi there", name: "Sara")
greeting(greeting: nil, name: "Sara")

class Car {
    var make: String
    var model: String
    var year: Int
    init(make: String, model: String, year: Int){
        self.make = make
        self.model = model
        self.year = year
    }
}

struct User {
    var name: String
    var stepsToday: Int
    init(name: String, stepsToday: Int){
        self.name = name
        self.stepsToday = stepsToday
    }
    init?(name: String?, stepsToday: Int?){
        if let name = name, let stepsToday = stepsToday {
            self.name = name
            self.stepsToday = stepsToday
        } else {
            return nil
        }
    }
}

let stepMaster = User(name: "StepMaster", stepsToday: 8394)
let activeSitter = User(name: "ActiveSitter", stepsToday: 9132)
let monsterWalker = User(name: "MonsterWalker", stepsToday: 7193)
let competitors = [stepMaster, activeSitter, monsterWalker]

func getWinner(competitors: [User]) -> User? {
    var topCompetitor: User?
    
    for competitor in competitors {
        if let topCompetitor1 = topCompetitor {
            if competitor.stepsToday > topCompetitor1.stepsToday {
                topCompetitor = competitor
            }
        } else {
            topCompetitor = competitor
        }
    }
    return topCompetitor
}

var winner = getWinner(competitors: competitors)

print(winner!.name)





