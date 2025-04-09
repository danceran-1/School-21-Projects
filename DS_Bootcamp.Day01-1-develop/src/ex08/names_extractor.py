import sys

def extract_names(file_path):
    try:
        with open(file_path, 'r') as file:
            emails = file.readlines()
    except FileNotFoundError:
        print(f"Error: The file {file_path} does not exist.")
        sys.exit(1)

    employees = []
    
    for email in emails:
      
        email = email.strip()  
        if '@' not in email:
            continue  
        
       
        local_part = email.split('@')[0] 
        name, surname = local_part.split('.')  

       
        name = name.capitalize()
        surname = surname.capitalize()

        employees.append((name, surname, email))

    
    with open('employees.tsv', 'w') as output_file:
        for name, surname, email in employees:
            output_file.write(f"{name}\t{surname}\t{email}\n")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 names_extractor.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    extract_names(file_path)
