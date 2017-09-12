import json


class MarkingPositionMonitor:
    def __init__(self):
        self.marking_position = {}
        self.order_buffer = []
        self.id_company_map = {}
        self.options = ["NEW", "FILL", "ORDER_ACK", "ORDER_REJECT", "CANCEL", "CANCEL_REJECT", "CANCEL_ACK"]

    def on_event(self, message):
        # checking if type is one of the options
        if message["type"] not in self.options:
            return

        order_type = message["type"]

        # Input Validation
        # only NEW orders can have a new order_id, if it does not exist in
        # our id_company_map then it is an invalid request
        if order_type != "NEW":
            if self.id_company_map[message['order_id']] not in self.marking_position:
                return 0

        # Marking Position Monitoring start here
        if order_type == "NEW":
            self.id_company_map[message['order_id']] = message['symbol']
            if message['symbol'] not in self.marking_position:
                self.marking_position[message['symbol']] = 0
            self.order_buffer.append(message)
            if message["side"] == "SELL":
                self.marking_position[message['symbol']] -= message["quantity"]

        elif order_type == "ORDER_ACK":
            # [inbound] no change
            pass

        elif order_type == "CANCEL":
            # [outbound] no change
            pass

        elif order_type == "CANCEL_ACK":
            for order in self.order_buffer:
                if order["order_id"] == message["order_id"]:
                    if order["side"] == "SELL":
                        self.marking_position[self.id_company_map[message['order_id']]] += order["quantity"]
                        break
                    if order["side"] == "BUY":
                        break

        elif order_type == "CANCEL_REJECT":
            for order in self.order_buffer:
                if order["order_id"] == message["order_id"]:
                    if order["side"] == "SELL":
                        self.marking_position[self.id_company_map[message['order_id']]] += order["quantity"]
                        break
                    if order["side"] == "BUY":
                        break

        elif order_type == "FILL":
            for order in self.order_buffer:
                if order["order_id"] == message["order_id"]:
                    if order["side"] == "BUY":
                        self.marking_position[self.id_company_map[message['order_id']]] = message["filled_quantity"] - self.marking_position[self.id_company_map[message['order_id']]]
                        order["quantity"] = message["remaining_quantity"]

                        break
                    if order["side"] == "SELL":
                        break

        elif order_type == "ORDER_REJECT":
            for order in self.order_buffer:
                if order["order_id"] == message["order_id"]:
                    if order["side"] == "SELL":
                        self.marking_position[self.id_company_map[message['order_id']]] += order["quantity"]
                        break
                    if order["side"] == "BUY":
                        break

        print json.dumps(message, indent=4)
        return self.marking_position[self.id_company_map[message['order_id']]]

test_cases = [
    {
        "type": "NEW",
        "symbol": "AAPL",
        "order_id": 1,
        "side": "SELL",
        "quantity": 900,
        "time": "2016-12-22T12:06:04.519266"
    },
    {
        "type": "ORDER_ACK",
        "order_id": 1,
        "time": "2016-12-22T12:06:04.519488"
    },
    {
        "type": "CANCEL",
        "order_id": 1,
        "time": "2016-12-22T12:06:04.519645"
    },
    {
        "type": "CANCEL_ACK",
        "order_id": 1,
        "time": "2016-12-22T12:06:04.519803"
    },
    {
        "type": "NEW",
        "symbol": "AAPL",
        "order_id": 2,
        "side": "BUY",
        "quantity": 400,
        "time": "2016-12-22T12:06:04.520013"
    },
    {
        "type": "ORDER_REJECT",
        "order_id": 2,
        "reason": "FIRM_RISK_LIMIT_EXCEEDED",
        "time": "2016-12-22T12:06:04.520190"
    },
    {
        "type": "NEW",
        "symbol": "AAPL",
        "order_id": 3,
        "side": "BUY",
        "quantity": 1800,
        "time": "2016-12-22T12:06:04.520492"
    },
    {
        "type": "ORDER_ACK",
        "order_id": 3,
        "time": "2016-12-22T12:06:04.520660"
    },
    {
        "type": "FILL",
        "order_id": 3,
        "filled_quantity": 1800,
        "remaining_quantity": 0,
        "time": "2016-12-22T12:06:04.520839"
    },
    {
        "type": "NEW",
        "symbol": "AAPL",
        "order_id": 4,
        "side": "SELL",
        "quantity": 1100,
        "time": "2016-12-22T12:06:04.521073"
    },
    {
        "type": "ORDER_REJECT",
        "order_id": 4,
        "reason": "MESSAGE_RATE_EXCEEDED",
        "time": "2016-12-22T12:06:04.521238"
    },
    {
        "type": "CANCEL",
        "order_id": 3,
        "time": "2016-12-22T12:06:04.521345"
    },
    {
        "type": "CANCEL_REJECT",
        "order_id": 3,
        "reason": "CANNOT_CANCEL_ZERO_QUANTITY",
        "time": "2016-12-22T12:06:04.521456"
    }
]


def test_code():
    a = MarkingPositionMonitor()
    for test in test_cases:
        print a.on_event(test)

test_code()
