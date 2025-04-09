import sys


def main():
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

    if len(sys.argv) != 2:
        sys.exit(0)

    company_name = sys.argv[1].strip("'\"")
    company_name = company_name.capitalize()

    if company_name in COMPANIES:
        ticker = COMPANIES[company_name]
        stock_price = STOCKS.get(ticker, "Unknown ticker")
        print(stock_price)
    else:
        print("Unknown company")


if __name__ == '__main__':
    main()
