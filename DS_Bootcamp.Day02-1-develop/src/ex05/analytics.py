
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
        
        def save_file(self, data, filename, extension='txt'):
            try:
                with open(f"{filename}.{extension}", 'w') as file:
                    file.write(data)
            except Exception as e:
                raise ValueError(f"An error occurred while saving the file: {e}")






