import sys



class Research :

    def __init__(self,file_path,has_header):
        self.file_path = file_path
        self.has_header = has_header

    def file_reader(self):
        try:
            with open(self.file_path, "r") as file:
                lines_for_out = []
                lines = [line.strip() for line in file.readlines()]
                for i in lines:
                    if self.has_header:
                        if i.replace(",", "").isalpha():
                            continue
                    lines_for_out.append(i)
                
            for line in lines[1:]:
                
                values = line.split(",")
                if len(values) != 2 or not all(value in {"0", "1"} for value in values):
                    raise ValueError("Invalid data format. Each line must contain two values, either '0' or '1', separated by a comma.")
            return lines_for_out
        except FileNotFoundError:
            raise FileNotFoundError(f"The file '{self.file_path}' was not found.")
        
        
    class Calculations:
        def counts(data):
            counter = 0
            chet = 0
            for i in data:
                values = i.split(",")
                if values[0] == "1":
                    counter +=1
                else:
                    chet +=1
            out = [counter,chet]
            return out
        def fractions(counts):
            sum = counts[0] + counts[1]
            head_procent = counts[0]*100/sum
            tail_procent = counts[1]*100/sum
            out = [head_procent , tail_procent]
            return out

if __name__ == '__main__':
    if len(sys.argv)!=2:
        sys.exit(1)
    file_path = sys.argv[1]
    try:

        has_header = True
        out = Research(file_path,has_header)
        data = out.file_reader()

        result = [list(map(int, line.split(','))) for line in data]
        counts = Research.Calculations.counts(data)
        fractions = Research.Calculations.fractions(counts)

        print(result)
        print(*counts)
        print(*fractions)
    except FileNotFoundError as e:
        print(f"Error: {e}")
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

