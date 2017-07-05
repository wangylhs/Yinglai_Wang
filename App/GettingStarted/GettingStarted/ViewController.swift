//
//  ViewController.swift
//  GettingStarted
//
//  Created by YinglaiWang on 7/2/17.
//
//

import UIKit

class ViewController:
UIViewController {

    @IBOutlet weak var myLabel: UILabel!
    @IBOutlet weak var myButton: UIButton!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        myButton.setTitleColor(.red, for: .normal)
        let label = UILabel(frame: CGRect(x: 16, y: 16, width: 200, height: 44))
        view.addSubview(label)
    }

    @IBAction func buttonPressed(_ sender: Any) {
        print("The button was pressed")
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

