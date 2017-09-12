;;;usm.nw:459
(class FinancialHistory Object
    (cashOnHand incomes outgoes)
    (method setInitialBalance: (amount) ; private
        (set cashOnHand amount)
        (set incomes      (new Dictionary))
        (set outgoes (new Dictionary))
        self)
    (method deposit:from: (amount source)
        (at:put: incomes source (+ (totalDepositedFrom: self source) amount))
        (set cashOnHand (+ cashOnHand amount)))
    (method withdraw:for: (amount reason)
        (at:put: outgoes reason (+ (totalWithdrawnFor: self reason) amount))
        (set cashOnHand (- cashOnHand amount)))
    (method cashOnHand () cashOnHand)
    (method totalDepositedFrom: (source)
        (at:ifAbsent: incomes source [0]))
    (method totalWithdrawnFor: (reason)
        (at:ifAbsent: outgoes reason [0]))
    (class-method initialBalance: (amount)
        (setInitialBalance: (new self) amount))
)