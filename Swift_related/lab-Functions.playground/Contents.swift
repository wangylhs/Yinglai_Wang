//: Playground - noun: a place where people can play

import UIKit
import Foundation

func introduceMyself(name: String, home: String, age: Int){
    print("\(name), \(age), is from \(home).")
}
introduceMyself(name:"Mary",home:"California",age:32)
func magicEightBall(){
    let randomNum = arc4random_uniform(UInt32(5))
    if randomNum < 2 {
        print("hits in lower area!")
    }else if randomNum == 2 {
        print("hits right in the middle!")
    }else {
        print("hits in higher area!")
    }
}
magicEightBall()

func multiply(firstNumber: Double, by secondNumber: Double){
    let result = firstNumber*secondNumber
    print("\(firstNumber) * \(secondNumber) = \(result)")
}
multiply(firstNumber: 1.5, by: 2.0)
func greeting(name: String) -> String{
    return "Hi, \(name)! How are you?"
}
print(greeting(name: "Dan"))

func calculatePace(currentDistance: Double, totalDistance: Double, currentTime: Double) -> Double{
    let result = (totalDistance-currentDistance)/(currentDistance/currentTime)
    return result
}
func pacing(currentDistance: Double, totalDistance: Double, currentTime: Double, goalTime: Double) -> String{
    let pace = calculatePace(currentDistance: currentDistance, totalDistance: totalDistance, currentTime: currentTime)
    if pace > (goalTime-currentTime) {
        return "You've got to push it just a bit harder!"
    } else {
        return "Keep it up!"
    }
}




