# 1. a.
# object datatype for person having a Bank Account XYZ
person_details = []
bank_no = 100010001000
size = 0

class Person:
    def __init__(self, name, sex, amount, age, phone_no):
        self.name = name
        self.sex = sex
        self.amount = amount
        self.age = age
        self.bank_no = bank_no + size # unique bank number
        self.phone_no = phone_no 
        self.is_suspended = 1 if amount < 500 else 0
        # It's ok to use int as boolean, but remember it should be only 0 and 1!

# 1. b. create person
def create_person(name, sex, amount, age, phone_no):
    for person in person_details:
        # 1. e.
        if person.phone_no == phone_no:
            print(f"Bank account with the mobile no. {phone_no} already exists!")
            return -1
        
    person = Person(name, sex, amount, age, phone_no)
    person_details.append(person)
    global size
    size += 1
    return 0

# 1. c. deposit and withdraw some amount from bank acc
def deposit(bank_no, dep_amount):
    for person in person_details:
        if person.bank_no == bank_no:
            if person.is_suspended == 1:
                print("Sorry, your bank account has been suspended!")
                return -1
            person.amount += dep_amount
            print(f"You have successfully deposited Rs {dep_amount}!")
            return 0
    
    print("Invalid bank account number!")
    return -1
def withdraw(bank_no, withdraw_amount):
    for person in person_details:
        if person.bank_no == bank_no:
            if person.is_suspended == 1:
                print("Sorry, your bank account has been suspended!")
                return -1
            if person.amount < withdraw_amount:
                print(f"Sorry, your balance is low {person.amount}!")
                return -1
            person.amount -= withdraw_amount
            print(f"You have successfully withdrawn Rs {withdraw_amount}!")
            # only after withdraw we can calculate the is_suspended value
            # 1. d.
            if person.amount < 500:
                person.is_suspended = 1
            return 0
    
    print("Invalid bank account number!")
    return -1

# 1. f. Send money
def send_money(src_bank_no, dest_bank_no, amount):
    src_person = None
    dest_person = None
    
    for person in person_details:
        if person.bank_no == src_bank_no:
            src_person = person
        if person.bank_no == dest_bank_no:
            dest_person = person
    
    if src_person is None:
        print("Source Bank Account no. is Invalid!")
        return -1
    if src_person.is_suspended == 1:
        print("Sorry, src bank account has been suspended!")
        return -1
    if dest_person is None:
        print("Destination Bank Account no. is Invalid!")
        return -1
    if dest_person.is_suspended == 1:
        print("Sorry, dest bank account has been suspended!")
        return -1
    
    if withdraw(src_bank_no, amount) == 0:
        deposit(dest_bank_no, amount)
        print("Successfully the transaction has been completed!")
        return 0
    else:
        print("Transaction has failed!")
        return -1

# helper function
def print_person(person):
    print(f"{person.name} \t {person.sex} \t {person.phone_no} \t {person.age} \t {person.bank_no} \t {person.amount}")

# helper function
def print_all():
    for person in person_details:
        print_person(person)

# 1. g.
def print_unsuspended_person():
    for person in person_details:
        if person.is_suspended == 0:
            print_person(person)

# helper function
def initially_persons():
    names = ["Sam", "Alan", "Alex", "Rose", "Violet"]
    sex = ['M', 'M', 'M', 'F', 'F']
    amounts = [30000, 20000, 40000, 50000, 10000]
    age = [25, 26, 27, 32, 24]
    phone_no = [8178921232, 8178921233, 8178921235, 8178921237, 8178921239]

    for name, s, amount, a, ph in zip(names, sex, amounts, age, phone_no):
        create_person(name, s, amount, a, ph)


initially_persons()

while True:
    print("Menu Driven Program: Enter your choice!")
    print("1. Create a New Person")
    print("2. Deposit a Amount to a Bank no.")
    print("3. Withdraw a Amount from a Bank no.")
    print("4. Send Money from account 'A' to account 'B'")
    print("5. Print All!")
    print("6. Print Only Unsuspended Accounts")
    print("7. Exit")
    choice = int(input())
    
    if choice == 1:
        name = input("\nEnter person name: ")
        sex = input("\nEnter person sex (M | F | O): ")
        age = int(input("\nEnter person age: "))
        phone_no = int(input("\nEnter mobile no.: "))
        amount = float(input("\nEnter person initially amount (>= 500): "))
        create_person(name, sex, amount, age, phone_no)
    elif choice == 2:
        bank_no = int(input("\nEnter person bank no.: "))
        amount = float(input("\nEnter person amount: "))
        deposit(bank_no, amount)
    elif choice == 3:
        bank_no = int(input("\nEnter person bank no.: "))
        amount = float(input("\nEnter person amount: "))
        withdraw(bank_no, amount)
    elif choice == 4:
        src_bank_no = int(input("\nEnter src person bank no.: "))
        dest_bank_no = int(input("\nEnter dest person bank no.: "))
        amount = float(input("\nEnter person amount: "))
        send_money(src_bank_no, dest_bank_no, amount)
    elif choice == 5:
        print("Name \t Sex \t Phone_no \t Age \t Bank_no \t Amount")
        print_all()
    elif choice == 6:
        print("Name \t Sex \t Phone_no \t Age \t Bank_no \t Amount")
        print_unsuspended_person()
    elif choice == 7:
        print("Thank You!!")
        break
    else:
        print("Invalid Choice!")
    
