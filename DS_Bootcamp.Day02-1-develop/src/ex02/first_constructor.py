import sys

class Research :

    def __init__(self,file_path):
        self.file_path = file_path

    def file_reader(self):
        try:
            with open(self.file_path, "r") as file:
                lines = [line.strip() for line in file.readlines()]

            for line in lines[1:]:
                values = line.split(",")
                if len(values) != 2 or not all(value in {"0", "1"} for value in values):
                    raise ValueError("Invalid data format. Each line must contain two values, either '0' or '1', separated by a comma.")
            return lines
        except FileNotFoundError:
            raise FileNotFoundError(f"The file '{self.file_path}' was not found.")


if __name__ == '__main__':
    if len(sys.argv)!=2:
        sys.exit(1)
    file_path = sys.argv[1]
    try:


        out = Research(file_path)
        lines = out.file_reader()
        
        print(*lines,sep="\n")
    except FileNotFoundError as e:
        print(f"Error: {e}")
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

