//: Playground - noun: a place where people can play

import UIKit

let userInputAge: String = "34"

var heartRate: Int? = nil
heartRate = 74

let oldHR1 = 80
let oldHR2 = 76
let oldHR3 = 79
let oldHR4 = 70

var hrAverage: Int

if let oldHR5 = heartRate {
    hrAverage = (oldHR1+oldHR2+oldHR3+oldHR4+oldHR5)/5
    print(hrAverage)
} else {
    hrAverage = (oldHR1+oldHR2+oldHR3+oldHR4)/5
    print(hrAverage)
}

func checkAge(inputAge: String) -> Int?{
    let userAge: Int? = Int(inputAge)
    if let age = userAge {
        if age >= 18 {
            print("Welcome!")
        } else {
            print("Sorry, but you aren't old enough to use our app.")
        }
    } else {
        print("Sorry, something went wrong. Can you please re-enter your age?")
    }
    return userAge
}
print(checkAge(inputAge: userInputAge))

var prices = ["Chips": 2.99, "Donuts": 1.89, "Juice": 3.99, "Apple": 0.50, "Banana": 0.25, "Broccoli": 0.99]
var stock = ["Chips": 4, "Donuts": 0, "Juice": 12, "Apple": 6, "Banana": 6, "Broccoli": 3]
func makePurchase(itemName: String) -> Double?{
    let item: Int? = stock[itemName]
    if let quantity = item {
        if quantity == 0 {
            return nil
        } else {
            return prices[itemName]
        }
    } else {
        return nil
    }
}
print(makePurchase(itemName: "Juice"))

struct Meal {
    var food: [String]
    var calories: Int
}

var meals: [String: Meal] = ["Breakfast": Meal(food: ["Bagel", "Orange Juice", "Egg Whites"], calories: 530)]

func logMeal(name: String) -> Meal? {
    let meal: Meal? = meals[name]
    return meal
}
print(logMeal(name: "Breakfast"))


/*
 func checkLog() -> [String: Any] {
    let meal: [String: Any]? = UserDefaults.standard.dictionary(forKey: "mealLog")
    return meal
}*/
let meal = UserDefaults.standard.dictionary(forKey: "mealLog")

struct Computer {
    var ram: Int
    var yearManufactured: Int
    init?(ram: Int, yearManufactured: Int) {
        if ram > 0 && yearManufactured > 1970 && yearManufactured < 2017 {
            self.ram = ram
            self.yearManufactured = yearManufactured
        } else {
            return nil
        }
    }
}

let computer1 = Computer(ram: 128, yearManufactured: 1989)
let computer2 = Computer(ram: 128, yearManufactured: 1950)
if let ram1 = computer1?.ram {
    print(ram1)
}
if let ram2 = computer2?.ram {
    print(ram2)
}

struct Workout {
    var startTime: Double
    var endTime: Double
    init?(startTime: Double, endTime: Double){
        if (endTime-startTime)<10 {
            return nil
        } else {
            self.startTime = startTime
            self.endTime = endTime
        }
    }
}




