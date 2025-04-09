def read():
    count = 0
    with open("../../materials/ds.csv", "r") as file:
        lines = file.readlines()
        for line in lines:
            for char in line:
                if char == '"':
                    count += 1
                if count % 2 == 0:
                    if char == ",":
                        char = "\t"
                wirte(char)


def wirte(char):
    with open("ds.tsv", "a") as file:
        file.write(char)


if __name__ == '__main__':
    read()
