import sys


def get_first_paragraph(email, employees_file):
    try:
        with open(employees_file, 'r') as file:
            employees = file.readlines()
           
    except FileNotFoundError:
        print(f"Error: The file {employees_file} does not exist.")
        sys.exit(1)

    local_part = email.split('@')[0]
    _, surname = local_part.split('.')
    surname = surname.capitalize()

    for line in employees:
        name, last_name, _ = line.strip().split('\t')
        if last_name == surname:
            print(surname)
            print(f"Dear {name},\nWelcome to our team. We are sure that it will be a pleasure to work with you.")
            return
        else:
            print(f"{surname} is not found in the employee list.")
            return

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 letter_starter.py <email> <employees_file>")
        sys.exit(1)

    email = sys.argv[1]
    employees_file = sys.argv[2]
    get_first_paragraph(email, employees_file)
