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
    base(COMPANIES, STOCKS)


def base(COMPANIES, STOCKS):
    
    if len(sys.argv) != 2:
        sys.exit()    
    name = sys.argv[1].lower()
    check(name, STOCKS)
    for i, j in STOCKS.items():
        if i.lower() == name:
            for k, f in COMPANIES.items():
                if f.lower() == name:
                    print(k, j)


def check(name, STOKS):
    count = 0

    for i in STOKS:
        if i.lower() == name:
            count += 1

    if count < 1:
        print("Unknown ticker")
        return


if __name__ == '__main__':
    dictionary()
