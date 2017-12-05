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

