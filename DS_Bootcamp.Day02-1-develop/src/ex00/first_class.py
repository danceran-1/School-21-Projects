class Must_read:
    with open("../../materials/data.csv", "r") as file:
        lines = [line.strip() for line in file.readlines()]
        print(*lines,sep="\n")

if __name__ == '__main__':
    out = Must_read()

