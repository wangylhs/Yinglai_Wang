//: Playground - noun: a place where people can play

import UIKit

class Spaceship {
    var name: String
    var health: Int
    var position: Int
    init(name: String, health: Int, position: Int) {
        self.name = name
        self.health = health
        self.position = position
    }
    func moveLeft() {
        position -= 1
    }
    func moveRight(){
        position += 1
    }
    func wasHit(){
        health -= 5
        if health <= 0 {
            print("Sorry. Your ship was hit one too many times. Do you want to play again?")
        }
    }
}

let falcon = Spaceship(name: "Falcon", health: 0, position: 0)
falcon.moveLeft()
falcon.moveLeft()
falcon.moveRight()
print(falcon.position)
falcon.wasHit()

class Fighter: Spaceship {
    var weapon: String
    var remainingFirePower: Int
    init(name: String, health: Int, position: Int, weapon: String, remainingFirePower: Int) {
        self.weapon = weapon
        self.remainingFirePower = remainingFirePower
        super.init(name: name, health: health, position: position)
    }
    func fire(){
        if remainingFirePower > 0 {
            remainingFirePower -= 1
        }else{
            print("You have no more fire power.")
        }
    }
}

let destroyer = Fighter(name: "Destroyer", health: 0, position: 0, weapon: "Laser", remainingFirePower: 10)
print(destroyer.weapon)
for i in 0...11 {
    destroyer.fire()
    print(destroyer.remainingFirePower)
}

class ShieldedShip: Fighter {
    var shieldStrength: Int
    init(name: String, health: Int, position: Int, weapon: String, remainingFirePower: Int, shieldStrength: Int) {
        self.shieldStrength = shieldStrength
        super.init(name: name, health: health, position: position, weapon: weapon, remainingFirePower: remainingFirePower)
    }
    override func wasHit() {
        if shieldStrength > 0 {
            shieldStrength -= 5
        }else{
            super.wasHit()
        }
    }
}
let defender = ShieldedShip(name: "Defender", health: 100, position: 0, weapon: "Cannon", remainingFirePower: 10, shieldStrength: 25)
for i in 0...11 {
    defender.wasHit()
    print("shieldStrength = \(defender.shieldStrength)")
    print("health = \(defender.health)")
}
let sameShip = falcon
sameShip.moveLeft()
print(falcon.position)
print(sameShip.position)



