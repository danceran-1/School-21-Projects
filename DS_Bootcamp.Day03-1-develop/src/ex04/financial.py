import requests
from bs4 import BeautifulSoup

import sys
import subprocess
import pstats
import os

def get_financial_data(ticker, field):
    url = f"https://finance.yahoo.com/quote/{ticker}/financials/"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
    }
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        if response.status_code == 302:
            redirect_location = response.headers.get('Location')
            raise Exception(f"Редирект на {redirect_location}. Проверьте правильность тикера {ticker}.")
        response.raise_for_status()

    except requests.exceptions.RequestException  as e:
        raise Exception(f"Ошибка при подключении к {url}: {e}")
    except requests.HTTPError  as e:
        raise Exception(f"Ошибка HTTP при запросе {url}: {e}")

    soup = BeautifulSoup(response.text, 'html.parser')
    return find(soup, field)

def find(soup,field):
    rows = soup.find('div', {'class': 'row lv-0 yf-t22klz'})


    if not rows:
        raise Exception("Финансовая таблица не найдена на странице.")

    row = rows.find_all('div', {'class': 'column'})

    if not row:
        raise Exception(f"Поле '{field}' не найдено.")

    return out(row, field)


def out(row,field):
    values = []
    for col in row:

        text = col.get_text().strip()
        if text == field:
            continue

        values.append(text)

    return (field,*values)

def cumulative():

    file_out = "pstats-cumulative.txt"
    file_proof = "profiling-tottime.proof"
    file_in = "profiling-tottime.txt"

    try:
        subprocess.run(
            ["python", "-m", "cProfile", "-o", "profiling-tottime.proof", "financial.py",'MSFT',"Total Revenue"],
            check=True
        )
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при выполнении профилирования: {e}")
    

    try:
        stats = pstats.Stats(file_proof)
        

    
        with open(file_out, "w") as f:
            stats.stream = f
            stats.sort_stats("cumulative").print_stats(5)
            

    except Exception as e:
        print(f"Ошибка при анализе профилирования: {e}")
    finally:
        if os.path.exists(file_proof):
            os.remove(file_proof)



if __name__ == "__main__":

    if len(sys.argv) > 1 and sys.argv[1] == "profile":
        cumulative()
        exit()

    elif len(sys.argv) == 3:
        ticker = sys.argv[1]
        field = sys.argv[2]
    else:
        print("Использование:\n"
              "Для выполнения: python financial.py <TICKER> <FIELD>\n"
              "Для профилирования: python financial.py profile")

    try:
        result = get_financial_data(ticker, field)
        print(result)
    except Exception as e:
        print(e)

