//: Playground - noun: a place where people can play

import UIKit

var registrationList:[String] = []
registrationList.append("Sara")
registrationList += ["Amy","Bob","kate","Jack"]
print(registrationList)
registrationList.insert("Charlie", at: 1)
print(registrationList)
registrationList[5] = "Rebecca"
print(registrationList)
let deletedItem = registrationList.removeLast()
print(registrationList)
var walkingChallenges:[String] = ["Walk 3 miles a day", "Walk 7 times a week"]
var runningChallenges:[String] = ["Run 5 times a week", "Run 3 miles a day"]
var challenges = [walkingChallenges, runningChallenges]
print(challenges[1][0])
challenges.removeAll()
var committed:[String] = ["Walk 3 miles a day"]
if committed.isEmpty {
    print("Please commit to a challenge")
}else if committed.count == 1{
    print("The challenge you have chosen is \(committed[0]).")
}else{
    print("You have chosen multiple challenges.")
}
var calendar:[String: Int] = ["January":31, "February":28, "March":31]
calendar["April"] = 30
calendar.updateValue(29, forKey: "February")
print(calendar)
if let days = calendar["January"] {
    print("January has \(days) days")
}
let shapesArray = ["Circle", "Square", "Triangle"]
let colorsArray = ["Red", "Green", "Blue"]
let mydic:[String:[String]] = ["Shapes":shapesArray, "Colors":colorsArray]
//print(mydic)
if let result = mydic["Colors"] {
    print(result.last)
}

var paces:[String: Double] = ["Easy":10.0, "Medium":8.0, "Fast":6.0]
paces["Sprint"] = 4.0
paces.updateValue(7.5, forKey: "Medium")
paces.updateValue(5.8, forKey: "Fast")
paces["Sprint"] = nil
print(paces)

if let p = mydic["Medium"] {
    
}






