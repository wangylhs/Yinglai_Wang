//
//  MiddleViewController.swift
//  OrderOfEvents
//
//  Created by YinglaiWang on 1/29/18.
//  Copyright © 2018 YinglaiWang. All rights reserved.
//

import UIKit

class MiddleViewController: UIViewController {

    
    @IBOutlet weak var middleLabel: UILabel!
    var eventNumber: Int = 1
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        if let existingText = middleLabel.text {
            middleLabel.text = "\(existingText)\nEvent Number \(eventNumber) was viewDidLoad"
            eventNumber += 1
        }
    }
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        if let existingText = middleLabel.text {
            middleLabel.text = "\(existingText)\nEvent Number \(eventNumber) was viewWillAppear"
            eventNumber += 1
        }
        
    }
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        if let existingText = middleLabel.text {
            middleLabel.text = "\(existingText)\nEvent Number \(eventNumber) was viewDidAppear"
            eventNumber += 1
        }
    }
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        if let existingText = middleLabel.text {
            middleLabel.text = "\(existingText)\nEvent Number \(eventNumber) was viewWillDisappear"
            eventNumber += 1
        }
    }
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        if let existingText = middleLabel.text {
            middleLabel.text = "\(existingText)\nEvent Number \(eventNumber) was viewDidDisappear"
            eventNumber += 1
        }
    }
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
