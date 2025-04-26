import pytest
from movies import Movies
from ratings import Ratings


@pytest.fixture
def movie_file():
    return "mov_test.csv"

@pytest.fixture
def movie_instance(movie_file):
    instance = Movies(movie_file)
    instance.read_file(movie_file)  
    return instance

def test_dist_by_release(movie_instance):
    """Тест метода dist_by_release"""
    result = movie_instance.dist_by_release()
    expected_result = {
        '1995': 15,
        '2010': 5, 
        '2009': 4,
        '2008': 1, 
        '1997': 1, 
        '2002': 1
    }
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_dist_by_genres(movie_instance):
    """Тест метода dist_by_genres"""
    result = movie_instance.dist_by_genres()
    expected_result = {
        'Comedy': 11, 'Drama': 11, 'Adventure': 9, 'Romance': 9,
        'Action': 6, 'Children': 4, 'Animation': 3, 'Fantasy': 3,
        'Thriller': 3, 'Crime': 2, 'Horror': 2, 'Sci-Fi': 2,
        'War': 1, 'Musical': 1, 'Western': 1
    }
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_most_genres(movie_instance):
    """Тест метода most_genres"""
    result = movie_instance.most_genres(25)
    expected_result = {
        'Toy Story': 5, 'Robin Hood': 5, 'Stingray Sam': 4, 'Jumanji': 3,
        'Waiting to Exhale': 3, 'Heat': 3, 'GoldenEye': 3,
        'American President, The': 3, 'Balto': 3, 'Cutthroat Island': 3,
        'Sky Crawlers, The': 3, 'Nightmare on Elm Street, A': 3,
        'Cemetery Junction': 3, 'Grumpier Old Men': 2, 'Sabrina': 2,
        'Tom and Huck': 2, 'Dracula: Dead and Loving It': 2, 'Four Lions': 2,
        "St Trinian's 2: The Legend of Fritton's Gold": 2, '12 Angry Men': 2,
        'Lovers & Leavers': 2, 'Merantau': 2, 'Blue Valentine': 2,
        'Father of the Bride Part II': 1, 'Sudden Death': 1
    }
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

@pytest.fixture
def rating_file():
    return "rat_test.csv"

@pytest.fixture
def rating_instance(rating_file, movie_file):
    return Ratings.Movies(rating_file, movie_file)

def test_dist_by_year(rating_instance):
    """Тест метода dist_by_year"""
    result = rating_instance.dist_by_year()
    expected_result = {
        '1995': 15,
        '2010': 5,
        '2009': 4,
        '2008': 1,
        '1997': 1,
        '2002': 1
    }
    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_dist_by_rating(rating_instance):
    """Тест метода dist_by_rating"""
    result = rating_instance.dist_by_rating()
    
    print(result)
    expected_result = {'1.0': 1, '0.5': 1, '3.0': 5, '4.0': 10, '5.0': 13}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_top_by_num_of_ratings(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.top_by_num_of_ratings(10)  
    
    expected_result = {
        "Toy Story": 3,
        "Heat": 2,
        "Grumpier Old Men": 1
        
    }

    assert result == expected_result, f"Expected {expected_result}, but got {result}"


def test_top_by_ratings_average(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.average()  
    print(result)
    expected_result = {'Toy Story': 1.83, 'Grumpier Old Men': 5.0, 'Heat': 4.0}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_top_by_ratings_median(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.median()  
    print(result)
    expected_result = {'Toy Story': 1.0, 'Grumpier Old Men': 5.0, 'Heat': 4.0}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_top_controversial(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    rating_instance.top_by_num_of_ratings(10)
    result = rating_instance.top_controversial(10)  
    print(result)
    expected_result = {'Toy Story': 3.58, 'Grumpier Old Men': 0, 'Heat': 0.0}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

@pytest.fixture
def rating_instance(rating_file, movie_file):
    return Ratings.Users(rating_file, movie_file)

def test_count_users(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.count_users()  
    print(result)
    expected_result = {'1':30}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_average_uers(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.average_uers()  
    print(result)
    expected_result = {'1':4.05}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_median_uers(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.median_users()  
    print(result)
    expected_result = {'1':4.0}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"

def test_variance_users(rating_instance):
    """Тест метода top_by_num_of_ratings"""
    
    result = rating_instance.variance_users(10)  
    print(result)
    expected_result = {'1':3.5}

    assert result == expected_result, f"Expected {expected_result}, but got {result}"
