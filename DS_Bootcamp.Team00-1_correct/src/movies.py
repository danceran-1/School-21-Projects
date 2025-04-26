import re

class Movies:
    """
    Analyzing data from movies.csv
    """
    def __init__(self, path_to_the_file):
        
        self.file_path = path_to_the_file

    def get_secnod_colum(self,years):
        
        split = [i for i in str(years).split("(")  ]
        output = []

        for i in range(len(split)):
                if split[i][0:4].isdigit():
                    output.append(split[i][0:4])

        return output

    def split_csv_line(self,line):
        """Функция разделяет строку CSV, не учитывая запятые внутри кавычек."""
        result = []
        current = ""
        inside_quotes = False

        for char in line:
            if char == '"':
                inside_quotes = not inside_quotes  
            elif char == "," and not inside_quotes:
                result.append(current)
                
                current = ""  
            else:
                current += char 

        result.append(current)  
        
        return result

    
    
    def separate(self,lines,n):
        years = []
        for line in lines:

            columns = self.split_csv_line(line)
            years.append(columns[n])

        return years

    def read_file(self,file_path):
        lines = []
        
        try:
            with open(file_path, "r", encoding="utf-8") as file:
                next(file)
                
                lines = [line.strip() for line in file.readlines()]
                
        except Exception as e:
            print(f"Ошибка: {e}")
        
        return lines
    
    def list_to_dict(self,list_for_dict,n):
        release_years = {}
        count = 0
        for i in list_for_dict:
            if i in release_years:
                release_years[i] +=1
            else:
                release_years[i] = 1

        release_years = dict(sorted(release_years.items(), key=lambda item: item[1],reverse=n))
        return release_years

    def dist_by_release(self):
        """
        The method returns a dict or an OrderedDict where the keys are years and the values are counts. 
        You need to extract years from the titles. Sort it by counts descendingly.
        """
        lines = self.read_file(self.file_path)

        years = self.separate(lines,1)
        list_for_dict = self.get_secnod_colum(years)
        release_years = self.list_to_dict(list_for_dict,True)
       
        return release_years

    def get_third_colum(self,third_colum):

        return str(third_colum).split(",")

    def get_geners(self,third_colum):

        genres = []
        for item in (third_colum):
            genres.extend([i for i in item.replace("'", "").replace('"',"").split("|")])
        return genres

    def dist_by_genres(self):
        """
        The method returns a dict where the keys are genres and the values are counts.
     Sort it by counts descendingly.
        """
        lines = self.read_file(self.file_path)
        years = self.separate(lines,2)
        list_ready = self.get_geners(years)
        genres = self.list_to_dict(list_ready,True)

        return genres
    
    def title(self,list_ready):

        output = []
        for word in list_ready:
            clean_word = re.sub(r'\s*\(.*?\)\s*', '', word).strip()
            if clean_word:
                output.append(clean_word)
        return output

    def most_genres(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and 
        the values are the number of genres of the movie. Sort it by numbers descendingly.
        """
        
        read = []

        lines = self.read_file(self.file_path)
        list_ready = self.separate(lines,1)

        output = self.title(list_ready)
        
        for i in self.separate(lines,2):
            read.append(len(i.split("|")))
        
        movies = dict(self.from_two_list_to_dict(output,read))
        sorted_movies = dict(sorted(movies.items(), key=lambda item: item[1], reverse=True))

        top_n = dict(list(sorted_movies.items())[:n])
    
        return top_n

    def from_two_list_to_dict(self,output,read): 

        pairs = zip(output, read)
        movies = dict(pairs)
        movies = list(movies.items()) 

        return movies  

    def wirte1(self,char):

        with open("your_file.txt", "w", encoding="utf-8") as file:
            for i in char:
                file.write(str(i)+"  ")

    def wirte2(self,char):

        with open("your_file.txt", "a", encoding="utf-8") as file:
            for i in char:
                file.write(i+"  ")
    
    def wirte(self,char):

        with open("your_file.txt", "w", encoding="utf-8") as file:
            for key, value in char.items():
                file.write(f"{key}\t{value}\n")

    def wirte3(self,char):

        with open("a.txt", "w", encoding="utf-8") as file:
            for key, value in char.items():
                file.write(f"{key}\t{value}\n")
    

def main():

    file_path = "../materials/movies.csv"
    out = Movies(file_path)
    (out.dist_by_release())
    (out.dist_by_genres())
    print(out.most_genres(20))





if __name__ == '__main__':

    main()

    
