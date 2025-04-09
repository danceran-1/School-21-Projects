class Research:
    def file_reader(self):
        with open("../../materials/data.csv", "r") as file:
            lines = [line.strip() for line in file.readlines()]
            return lines

if __name__ == '__main__':
    out = Research()
    lines = out.file_reader()
    print(*lines,sep="\n")

