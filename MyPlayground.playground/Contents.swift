//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"

func multiply(first: Int, second: Int){
    let result = first*second
    print("The result is \(result).")
}
multiply(first: 2, second: 20)

//argument labels
func sayHello(to person: String, and anotherperson: String){
    print("Hello \(person) and \(anotherperson)")
}

sayHello(to: "Luke", and: "Sam")

//default parameter values
func display(teamName: String, score: Int = 0){
    print("\(teamName): \(score)");
}
display(teamName: "Wombats")
display(teamName: "Wombats", score: 100)

//return values
func multiplywithreturn(first: Int, second: Int) -> Int {
    let result = first * second
    return result
}
print("2 * 3 is \(multiplywithreturn(first: 2, second: 3))")

enum Color{
    case blue
    case black
    case silver
}
/*
struct Car{
    var make: String
    var year: Int
    var color: Color
    var topSpeed: Int
    func start(){}
    func drive(){}
    func park(){}
    //func steet(direction: Direction){}
}

let firstCar = Car(make: "Jeep", year: 2012, color: .black, topSpeed: 120)
firstCar.start()
*/
//default initializer, memberwise initializer, custom initializer
struct Temperature{
    var celsius: Double
    
    init(celsius: Double){
        self.celsius = celsius
    }
    init(fahrenheit: Double){
        celsius = (fahrenheit-32)/1.8
    }
}
let boiling = Temperature(fahrenheit: 212)
print(boiling.celsius)

//mutating method
struct Odometer{
    var count: Int = 0
    mutating func increment(){
        count += 1
    }
    mutating func increment(by amount: Int){
        count += amount
    }
    mutating func reset(){
        count = 0
    }
}
var odometer = Odometer()
odometer.increment()
odometer.increment(by: 100)
print(odometer.count)

//classes, inheritance
class Person{
    let name: String
    init (name: String){
        self.name = name
    }
    func sayHello(){
        print("Hello!")
    }
}

let person = Person(name:"Wang")
print(person.name)
person.sayHello()

class Vehicle{
    var currentSpeed = 0
    var description: String{
        return "traveling at \(currentSpeed) miles per hour"
    }
    func makeNoise(){
        
    }
}
class Bicycle: Vehicle{
    var hasBasket = false
    
}
let bicycle = Bicycle()
bicycle.hasBasket = true
bicycle.currentSpeed = 15
print(bicycle.description)
class Car: Vehicle{
    var gear = 1
    override var description: String{
        return super.description + " in gear \(gear)"
    }
}
let car = Car()
car.currentSpeed = 30
car.gear = 3
print("Car: \(car.description)")
class Student: Person{
    var favoriteSubject: String
    init(name: String, favoriteSubject: String){
        self.favoriteSubject = favoriteSubject
        super.init(name: name)
    }
}



