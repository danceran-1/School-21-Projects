import sys
from random import randint


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
                    if i.replace(",", "").isalpha():
                        continue
                    lines_for_out.append(i)
                self.has_header = False
            for line in lines[1:]:
                
                values = line.split(",")
                if len(values) != 2 or not all(value in {"0", "1"} for value in values):
                    raise ValueError("Invalid data format. Each line must contain two values, either '0' or '1', separated by a comma.")
            return lines_for_out
        except FileNotFoundError:
            raise FileNotFoundError(f"The file '{self.file_path}' was not found.")
        
        
    class Calculations:

        def __init__(self,data):
            self.data = data

        def counts(self):
            counter = 0
            chet = 0
            for i in self.data:
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
        
    class Analytics(Calculations):

        def __init__(self, data):
            super().__init__(data)
            
        def predict_random(self,n):
            mini_list = []
          
            
            for i in range(n):
                if randint(0,1) == 0:
                    mini_list.append([0, 1])
                else:
                    mini_list.append([1, 0])
            return mini_list
        
        def predict_last(self):
            return self.data[-1] if self.data else None





if __name__ == '__main__':
    if len(sys.argv)!=2:
        sys.exit(1)
    file_path = sys.argv[1]
    try:

        has_header = True
        out = Research(file_path,has_header)
        data = out.file_reader()
        analytics = Research.Analytics(data)
        
        result = [list(map(int, line.split(','))) for line in data]
        a = Research.Calculations(data)
        counts = a.counts()
        fractions = Research.Calculations.fractions(counts)
        predict = analytics.predict_random(3)
        last = analytics.predict_last()
        

        print(result)
        print(*counts)
        print(*fractions)
        print(predict)
        print([last])
    except FileNotFoundError as e:
        print(f"Error: {e}")
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

