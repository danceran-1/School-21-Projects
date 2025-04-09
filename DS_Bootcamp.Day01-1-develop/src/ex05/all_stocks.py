import sys


def dictionary():

    COMPANIES = {
        'Apple': 'AAPL',
        'Microsoft': 'MSFT',
        'Netflix': 'NFLX',
        'Tesla': 'TSLA',
        'Nokia': 'NOK'
    }
    STOCKS = {
        'AAPL': 287.73,
        'MSFT': 173.79,
        'NFLX': 416.90,
        'TSLA': 724.88,
        'NOK': 3.37
    }
    baza(STOCKS, COMPANIES)


def baza(STOCKS, COMPANIES):
    
    if len(sys.argv) != 2:
        sys.exit(0)
        
    user_input = sys.argv[1]

    user_input = user_input.strip("'\"")

    if ',' not in user_input:
        sys.exit()

    if ',,' in user_input:
        sys.exit()
    names = user_input.split(',')
    names = [name.strip() for name in names]
    if '' in names:
        sys.exit()
    count = user_input.count(',')

    if count >= len(names):
        sys.exit()

    for z in names:
        company_found = False
        ticker_found = False

        for k, f in COMPANIES.items():
            if z.lower() == k.lower():
                print(f"{k} stock price is {STOCKS[f]}")
                company_found = True
            if z.lower() == f.lower():
                print(f"{f} is a ticker symbol for {k}")
                ticker_found = True

        if not company_found and not ticker_found:
            print(
                f"{z.capitalize()} is an unknown company or an unknown ticker symbol")


if __name__ == '__main__':
    dictionary()
