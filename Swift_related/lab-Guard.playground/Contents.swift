//: Playground - noun: a place where people can play

import UIKit

func calculateArea(x:Double, y:Double) -> Double?{
    guard x>0, y>0 else {return nil}
    return x*y
}
func add(x:Int?, y:Int?) -> Int?{
    guard let a = x, let b = y else {return nil}
    return a+b
}

struct User {
    var firstName: String
    var lastName: String
    var age: String
}

let firstNameTextField = UITextField()
let lastNameTextField = UITextField()
let ageTextField = UITextField()

firstNameTextField.text = "Jonathan"
lastNameTextField.text = "Sanders"
ageTextField.text = "28"

func createUser() -> User? {
    guard let firstName = firstNameTextField.text,
        let lastName = lastNameTextField.text,
        let age = ageTextField.text else {return nil}
    let newUser = User(firstName: firstName, lastName: lastName, age: age)
    return newUser
}

let usr = createUser()
print(usr!.firstName)

struct Workout {
    var startTime: Double
    var endTime: Double
    init?(startTime: Double, endTime: Double) {
        guard (endTime-startTime)<10 else { return nil }
        self.startTime = startTime
        self.endTime = endTime
    }
}

struct Food {
    var name: String
    var calories: Int
}

let foodTextField = UITextField()
let caloriesTextField = UITextField()

foodTextField.text = "Banana"
caloriesTextField.text = "23"

func logFood() -> Food? {
    guard let food = foodTextField.text, let calories = caloriesTextField.text
    else { return nil }
    guard let c = Int(calories) else {return nil}
    let meal = Food(name: food, calories: c)
    return meal
}



