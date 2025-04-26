import movies

class Ratings:
    """
    Analyzing data from ratings.csv
    """
    def __init__(self, path_to_the_file,file_path_movie):
        """
        Put here any fields that you think you will need.
        """
        self.file_path = path_to_the_file

        self.file_path_movie = file_path_movie


        self.Movies = self.Movies(path_to_the_file,file_path_movie)

        self.Users = self.Users(path_to_the_file,file_path_movie)

    class Movies:  

        def __init__(self, file_path,file_path_movie):

            self.file_path = file_path
            self.file_path_movie = file_path_movie

            self.a = movies.Movies(self.file_path)

            lines = self.a.read_file(self.file_path_movie)
            self.id = self.a.separate(lines,1)

            second_colum = self.a.separate(lines,1)
            self.title = self.a.title(second_colum)
            
        def dist_by_year(self):
            """ The method returns a dict where the keys are years and the values are counts. 
                Sort it by years ascendingly. You need to extract years from timestamps.
            """
 
            lines = self.a.read_file(self.file_path_movie)
            years = self.a.separate(lines,1)

            list_for_dict = self.a.get_secnod_colum(years)
            ratings_by_year = self.a.list_to_dict(list_for_dict,False)

            return ratings_by_year
        
        def dist_by_rating(self):
            """ The method returns a dict where the keys are ratings and the values are counts.
                Sort it by ratings ascendingly.
            """
            lines = self.a.read_file(self.file_path)
            years = self.a.separate(lines,2)

            ratings_distribution = self.a.list_to_dict(years,False)

            return ratings_distribution
        
        def top_by_num_of_ratings(self, n):
            """
            The method returns top-n movies by the number of ratings. 
            It is a dict where the keys are movie titles and the values are numbers.
     Sort it by numbers descendingly.
            """
            lines = self.a.read_file(self.file_path_movie)
            second_colum = self.a.separate(lines,1)
            title = self.a.title(second_colum)

            id_mov = self.a.separate(lines,0)
            dict_title_id_mov = dict(self.a.from_two_list_to_dict(title,id_mov))


            lines = self.a.read_file(self.file_path)
            self.id = self.a.separate(lines,1)

           
        
            self.release_years = {}
            for i in self.id:
                if i in self.release_years:
                    self.release_years[i] +=1
                else:
                    self.release_years[i] = 1

            id_to_title = {v: k for k, v in dict_title_id_mov.items()}
            top_movies = {id_to_title[movie_id]: count for movie_id, count in self.release_years.items() if movie_id in id_to_title}
            top_movies = dict(sorted(top_movies.items(), key=lambda item: item[1],reverse=True))
            

            top_movies = list(top_movies.items())

            

            return dict(top_movies[:n])
        
        def split_rating(self,rating,id):

            dict = {}
            for i in range(len(id)):

                if id[i] not in dict:
                    dict[id[i]] = (rating[i])+ " "
                else:
                    dict[id[i]] += rating[i] + " "

            return dict

        def sort_dcit(self,dict):

            sort_dict = {}
            for film_id, ratings_str in dict.items():

                ratings = list(map(float, ratings_str.split()))  
                sort_dict[film_id] = sorted(ratings)
            return sort_dict
        
        def median_main(self,rating,id,variant):
            
            keys_id = {}
            dict = self.split_rating(rating,id)
            lines = self.a.read_file(self.file_path_movie)
            id_mov = self.a.separate(lines, 0)
            sort_dict = self.sort_dcit(dict)
            spisok = list(sort_dict.values())
            keys = list(sort_dict.keys())

         

            for i in range(len(spisok)):
    
                    n = len(spisok[i])

                    if n == 1:
                        keys_id[keys[i]] = spisok[i]

                    if n % 2 != 0:
                        keys_id[keys[i]] = spisok[i][n // 2]

                    else:
                        mid1 = spisok[i][n // 2]
                        mid2 = spisok[i][n // 2-1]
                        keys_id[keys[i]] = (mid1 + mid2) / 2
           
            if variant == 0:
               
                out = self.switch_to_title(id_mov,dict,2)
            else:
                out = keys_id
            return out

        def median(self):

            lines = self.a.read_file(self.file_path)
            rating = self.a.separate(lines, 2)
            idishnik = self.a.separate(lines,1)

            mediana = self.median_main(rating,idishnik,0)
            
            return mediana
            # return last_dcit

        def switch_to_title(self,id_mov,dicti,n):
             
            unity = dict(self.a.from_two_list_to_dict(id_mov,self.title))

            new_dict = {}

            for movie_id, title in unity.items():
                
                if movie_id in dicti:
                    new_dict[title] = dicti[movie_id]

            
            finaly = {}
            new_dict = self.sort_dcit(new_dict)
            spisok = list(new_dict.values())
            keys = list(new_dict.keys())
            if n == 1:
            

                for film_id, ratings_str in new_dict.items():

                    ratings = list(map(float, ratings_str)) 
                    finaly[film_id] = round(sum(ratings) / len(ratings),2)

            elif n==2:
                for i in range(len(spisok)):
    
                    n = len(spisok[i])

                    if n == 1:
                        finaly[keys[i]] = spisok[i]

                    if n % 2 != 0:
                        finaly[keys[i]] = spisok[i][n // 2]

                    else:
                        mid1 = spisok[i][n // 2]
                        mid2 = spisok[i][n // 2-1]
                        finaly[keys[i]] = (mid1 + mid2) / 2
            else:
           
                avg_values = self.average_list(spisok)
                idi = []
                for i in self.id:
                    if i not in idi:
                        idi.append(i)
                
                for i, j in zip(keys, range(len(avg_values))):
                
                    if len(spisok[j]) > 1:  
                        variance = sum((x - float(avg_values[j])) ** 2 for x in spisok[j]) / (len(spisok[j]) - 1)
                    else:
                        variance = 0 

                    finaly[i] = round(variance, 2) 
                
                

            return finaly
        
        def average_main(self,rating,id,n):

            dicti = self.split_rating(rating,id)
            
            average_ratings = {}
            for film_id, ratings_str in dicti.items():

                ratings = list(map(float, ratings_str.split()))  
                average_ratings[film_id] = round(sum(ratings) / len(ratings),2)

            self.a.wirte(dicti)
            
            lines = self.a.read_file(self.file_path_movie)
            id_mov = self.a.separate(lines, 0)
    
            if n==0:
               
                out = self.switch_to_title(id_mov,dicti,1)
            else:
                out = average_ratings
    
            return out

        def average(self):

            lines = self.a.read_file(self.file_path)
            rating = self.a.separate(lines, 2)
            
            idishnik = self.a.separate(lines,1)

            average_ratings = self.average_main(rating,idishnik,0)
            
            return average_ratings
            # return last_dict

        def top_by_ratings(self, n, metric=None):
            """
            The method returns top-n movies by the average or median of the ratings.
            It is a dict where the keys are movie titles and the values are metric values.
            Sort it by metric descendingly.
            The values should be rounded to 2 decimals.
            """
            

            if metric is None:
                metric = self.average()  

            movie_ratings = metric()  
            
            top_movies = dict(sorted(movie_ratings.items(), key=lambda x: x[1], reverse=True))


            return dict(list(top_movies.items())[:n])
        
            


        def variance_main(self,rating,id,n,variant):

            dicti = self.split_rating(rating,id)
            sort_dict  = self.sort_dcit(dicti)
            values = list(sort_dict.values())

            avg_values = self.average_list(values)
            if variant==1:
                variance_mov = self.find_variance(avg_values,values,id)

            else:

                lines = self.a.read_file(self.file_path_movie)
                id_mov = self.a.separate(lines, 0)

                variance_mov = self.switch_to_title(id_mov,dicti,3)

            sorted_variance = dict(sorted(variance_mov.items(), key=lambda item: item[1], reverse=True))
            top_n_variance = dict(list(sorted_variance.items())[:n])


          
            return top_n_variance

        def top_controversial(self, n):
            """
            The method returns top-n movies by the variance of the ratings.
            It is a dict where the keys are movie titles and the values are the variances.
          Sort it by variance descendingly.
            The values should be rounded to 2 decimals.
            """
            lines = self.a.read_file(self.file_path)
            rating = self.a.separate(lines, 2)

            id = self.id

            top_n_variance = self.variance_main(rating,id,n,0)
            
            return top_n_variance
            
         
           

        
        def find_variance(self, avg_values, values,id):
            top_movies = {}

            idi = []
            for i in id:
                if i not in idi:
                    idi.append(i)
            
            for i, j in zip(idi, range(len(avg_values))):
             
                if len(values[j]) > 1:  
                    variance = sum((x - float(avg_values[j])) ** 2 for x in values[j]) / (len(values[j]) - 1)
                else:
                    variance = 0 

                top_movies[i] = round(variance, 2) 
            
            return top_movies

        
        def average_list(self, values):
            out = []
            for i in values:
                if len(i) > 0: 
                    out.append(sum(i) / len(i))
                else:
                    out.append(0)  

            return out

         
            
    class Users(Movies):
        """
        In this class, three methods should work. 
        The 1st returns the distribution of users by the number of ratings made by them.
        The 2nd returns the distribution of users by average or median ratings made by them.
        The 3rd returns top-n users with the biggest variance of their ratings.
     Inherit from the class Movies. Several methods are similar to the methods from it.
        """
        def __init__(self, file_path, file_path_movie):
            super().__init__(file_path, file_path_movie)

        def count_users(self):

            lines = self.a.read_file(self.file_path)
            users_id = self.a.separate(lines, 0)
            rating = self.a.separate(lines,2)

            dict_user_rating = self.split_rating(rating,users_id)

            self.a.wirte3(dict_user_rating)

            out_dict = {}

            for film_id, ratings_str in dict_user_rating.items():
                
               
                ratings = list(ratings_str.split())
                out_dict[film_id] = len(ratings)

           
            out_dict = dict(sorted(out_dict.items(), key=lambda item: item[1], reverse=True))
            
           
            return out_dict
           
        def average_or_median_users(self, n, metric=None):
            

            if metric is None:
                metric = self.average_uers  

            movie_ratings = metric()  
            
            top_movies = dict(sorted(movie_ratings.items(), key=lambda x: x[1], reverse=True))

            return dict(list(top_movies.items())[:n])
        
        def average_uers(self):

            lines = self.a.read_file(self.file_path)
            users_id = self.a.separate(lines, 0)
            rating = self.a.separate(lines,2)

            average_ratings = super().average_main(rating,users_id,1)


        
            return average_ratings
        
        def median_users(self):

            lines = self.a.read_file(self.file_path)
            users_id = self.a.separate(lines, 0)
            rating = self.a.separate(lines,2)

            meidan_ratings = super().median_main(rating,users_id,1)

            return meidan_ratings
        
        def variance_users(self,n):
            
            lines = self.a.read_file(self.file_path)
            users_id = self.a.separate(lines, 0)
            rating = self.a.separate(lines,2)

            variance_out = super().variance_main(rating,users_id,n,1)

            return variance_out

        
def main():


    file_path = "../materials/ratings.csv"
    file_path_movie = "../materials/movies.csv"

    out = Ratings(file_path,file_path_movie)
    # (out.Movies.dist_by_year())
    # (out.Movies.dist_by_rating())

    
    (out.Movies.top_by_num_of_ratings(10))
   
    (out.Movies.top_by_ratings(2000,metric=out.Movies.median))

    # #Использоватль вместе с top_by_num_of_ratings
    print(out.Movies.top_controversial(100))

    (out.Users.count_users())
    
    ((out.Users.average_or_median_users(500,metric=out.Users.median_users)))

    ((out.Users.variance_users(10)))



if __name__ == '__main__':

    main()
