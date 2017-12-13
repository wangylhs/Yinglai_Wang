//: Playground - noun: a place where people can play

import UIKit

struct GPS {
    var latitude: Double
    var longitude: Double
}

var somePlace = GPS(latitude: 51.514004, longitude: 0.125226)
print(somePlace.latitude, somePlace.longitude)

struct Height {
    var heightInInches: Double
    var heightInCentimeters: Double
    init(heightInInches: Double) {
        self.heightInInches = heightInInches
        self.heightInCentimeters = 2.54*heightInInches
    }
    init(heightInCentimeters: Double) {
        self.heightInCentimeters = heightInCentimeters
        self.heightInInches = heightInCentimeters/2.54
    }
}

var someonesHeight = Height(heightInInches: 65)
print(someonesHeight.heightInCentimeters)

struct Distance {
    var meters: Double
    var feet: Double
    init(meters: Double) {
        self.meters = meters
        self.feet = meters*3.28084
    }
    init(feet: Double) {
        self.meters = feet/3.28084
        self.feet = feet
    }
}
var mile = Distance(meters: 1600)
print(mile.feet)

struct Book {
    var title: String
    var author: String
    var pages: Int
    var price: Double
    func description() {
        print("Book properties:")
        print("title: \(title)\nauthor: \(author)\nprice: \(price)")
    }
}
struct Post {
    var message: String
    var likes: Int
    var numberOfComments: Int
    mutating func like(){
        likes+=1
    }
}
var newPost = Post(message: "12345", likes: 0, numberOfComments: 0)
newPost.like()
print(newPost.likes)

/*
struct RunningWorkout {
    var distance: Double
    var time: Double
    var elevation: Double
    var averageMileTime: Double
    init(distance: Double, time: Double, elevation: Double) {
        self.distance = distance
        self.time = time
        self.elevation = elevation
        self.averageMileTime = (distance/1600)/time
    }
    func postWorkoutStats(){
        print("distance: \(distance)")
        print("time: \(time)")
        print("elevation: \(elevation)")
    }
}*/
struct Steps {
    var steps: Int {
        willSet {
            print("about to set steps")
        }
        didSet {
            if steps == goal {
                print("Congratulations!")
            }
        }
    }
    var goal: Int
    mutating func takeStep(){
        steps+=1
    }
}
var myStep = Steps(steps: 9999, goal: 10000)
myStep.takeStep()

struct User {
    var userName: String
    var age: Int
    var email: String
    static var currentUser: User = User(userName: "rock", age: 28, email: "123@163.com")
}
var u = User.currentUser
print(u.userName)

struct RunningWorkout {
    var distance: Double
    var time: Double
    var elevation: Double
    static func mileTimeFor(distance: Double, time: Double) -> Double{
        return (distance/1600)/time
    }
}




