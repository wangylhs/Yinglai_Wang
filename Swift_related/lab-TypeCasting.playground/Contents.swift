//: Playground - noun: a place where people can play

import UIKit

var myCollection: [Any] = [3.42, 42, "apple", true]
print(myCollection)

for x in myCollection {
    print("The integer has a value of \(x)")
}

var myDictionary: [String:Any] = ["first":3.42, "second":42, "third":"apple", "fourth":true, "fifth":false]
for (x,y) in myDictionary {
    print("\(x) \(y)")
}
var total:Double = 0
for (key,value) in myDictionary {
    if let v = value as? Int {
        total += Double(v)
    } else if let v = value as? Double {
        total += v
    } else if let v = value as? String {
        total += 1
    } else if let v = value as? Bool {
        if v == true {
            total += 2
        }else{
            total -= 3
        }
    }
    print("total = \(total)")
}
var total2:Double = 0
for (key,value) in myDictionary {
    if let v = value as? Int {
        total2 += Double(v)
    } else if let v = value as? Double {
        total2 += v
    }
}

class Workout {
    let time: Double
    let distance: Double
    
    init(time: Double, distance: Double) {
        self.time = time
        self.distance = distance
    }
}

class Run: Workout {
    let cadence: Double
    
    init(cadence: Double, time: Double, distance: Double) {
        self.cadence = cadence
        super.init(time: time, distance: distance)
    }
}

class Swim: Workout {
    let stroke: String
    
    init(stroke: String, time: Double, distance: Double) {
        self.stroke = stroke
        super.init(time: time, distance: distance)
    }
}

var workouts: [Workout] = [
    Run(cadence: 80, time: 1200, distance: 4000),
    Swim(stroke: "Freestyle", time: 32.1, distance: 50),
    Swim(stroke: "Butterfly", time: 36.8, distance: 50),
    Swim(stroke: "Freestyle", time: 523.6, distance: 500),
    Run(cadence: 90, time: 358.9, distance: 1600)
]

func describeRun(runningWorkout: Run){
    print("This is a running workout")
    print("Cadence is \(runningWorkout.cadence) steps per minute")
    print("Time is \(runningWorkout.time) seconds")
    print("Distance is \(runningWorkout.distance) meters")
}
func describeSwim(swimmingWorkout: Swim){
    print("This is a swimming workout")
    print("Stroke is \(swimmingWorkout.stroke)")
    print("Time is \(swimmingWorkout.time) seconds")
    print("Distance is \(swimmingWorkout.distance) meters")
}
describeRun(runningWorkout: workouts[0] as! Run)
describeSwim(swimmingWorkout: workouts[1] as! Swim)

for workout in workouts {
    if let type = workout as? Run {
        describeRun(runningWorkout: type)
    } else if let type = workout as? Swim {
        describeSwim(swimmingWorkout: type)
    }
}







