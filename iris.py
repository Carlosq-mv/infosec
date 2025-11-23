VALID_THRESHOLD = 0.32

class IrisAuthSystem():
    def __init__(self):
        self.db: dict[str, str] = {}

    def enroll_user(self, name: str, iris_code: str):
        self.db[name] = iris_code.strip()

    def recognize_user(self, name:str, iris_code: str):
        iris_code = iris_code.strip()

        # name in database, compute hamming distance
        if name not in self.db:
            print(f"Can't recognize user. {name} not in database.")
            return False

        distance = self.hamming_distance(self.db[name], iris_code)
        
        return distance <= VALID_THRESHOLD, distance

    def hamming_distance(self, hex1: str, hex2: str) -> float:
        # convert hex to an int
        num1 = int(hex1, 16)
        num2 = int(hex2, 16)
        
        # XOR the two binary bits (get # of non-matching bits)
        z = num1 ^ num2

        return z.bit_count() / (len(hex1) * 4)

def main():
    iris_auth = IrisAuthSystem()

    while True:
        print("\n======= Iris Authentication System =======")
        print("Please Choose One of The Following Options\n")
        print("(1) Enroll (add/update an iris code)")
        print("(2) Recognize (authenticate a person)")
        print("(0) Exit")
        print("=====================================")

        option = input("Your choice: ").strip()

        if not option.isdigit():
            print("Choose a valid option.")
            continue

        option_num = int(option)

        if option_num == 0:
            print("Exiting program. Goodbye!")
            break

        elif option_num == 1:
            print("Enter name & iris code in this format: <name:iris_code> (e.g. 'Carlos:9DF8B811')")

            user_input = input().strip()
            name_and_hex = user_input.split(":")

            if len(name_and_hex) != 2:
                print("Invalid format. Please use name:hexcode")
                continue

            name, iris_code = name_and_hex[0], name_and_hex[1]

            iris_auth.enroll_user(name, iris_code)
            print(f"Enrolled {name} successfully.")

        elif option_num == 2:
            name = input("Enter name: ").strip()
            iris_code = input(f"Enter iris code (hex) for {name}: ").strip()

            result, distance = iris_auth.recognize_user(name, iris_code)

            if result:
                print(f"Hamming distance {distance} ... ACCESS GRANTED")
            else:
                print(f"Hamming distance {distance} ... ACCESS DENIED")

        else:
            print("Choose a valid option.")

main()
