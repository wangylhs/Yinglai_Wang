//: Playground - noun: a place where people can play

import UIKit

let firstName: String
firstName = "Yinglai"
let lastName: String
lastName = "Wang"
let fullName = firstName + " " + lastName
print(fullName)
let previousBest = 14392
let newBest = 15125
let congratulations = "Congratulations, \(fullName)! You beat your previous daily high score of \(previousBest) steps by walking \(newBest) steps yesterday!"

let nameInCaps = "Yinglai Wang"
let name = "yinglai wang"
if nameInCaps.lowercased() == name.lowercased() {
    print("LOWER CASE VERSION OF \(nameInCaps) and LOWER CASE VERSION OF \(name) are the same.")
}else{
    print("LOWER CASE VERSION OF \(nameInCaps) and LOWER CASE VERSION OF \(name) are not the same.")
}

let junior = "Cal Ripken Jr."
print(junior.hasSuffix("Jr."))

import Foundation
let textToSearchThrough = "To be, or not to be--that is the question"
let textToSearchFor = "to be, or not to be"

print(textToSearchThrough.lowercased().contains(textToSearchFor))

let storedUserName = "TheFittest11"
let storedPassword = "a8H1LuK91"
let enteredUserName = "thefittest11"
let enteredPassword: String = "a8H1LuK91"
let userName = "StepChallenger"
let searchName = "step"
if storedUserName.lowercased() == enteredUserName.lowercased() {
    if storedPassword == enteredPassword {
        print("Your are now logged in!")
        if userName.lowercased().contains(searchName.lowercased()) {
            print("\(userName)")
        }
        
    }else{
        print("please check your user name and password and try again.")
    }
}else{
    print("please check your user name and password and try again.")
}











