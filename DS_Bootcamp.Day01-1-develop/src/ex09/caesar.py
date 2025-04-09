import sys


def encode(alphabet_list, names, cdvig):

    spis = []

    for j in names:
        for k in j:
            if k in alphabet_list:
                index = alphabet_list.index(k)
                new_index = (index + cdvig) % len(alphabet_list)
                next_letter = alphabet_list[new_index]
                spis.append(next_letter)
            else:
                spis.append(k)

    print(''.join(spis))


def decode(alphabet_list, names, cdvig):
    listik = []
    for j in names:
        for k in j:
            if k in alphabet_list:
                index = alphabet_list.index(k)
                new_index = (index - cdvig) % len(alphabet_list)
                next_letter = alphabet_list[new_index]
                listik.append(next_letter)
            else:
                listik.append(k)

    print(''.join(listik))


def main():

    if len(sys.argv) != 4:
        raise ValueError(
            "Usage: python3 caesar.py <encode/decode> '<text>' <shift>")

    user_input = sys.argv[2]
    if any('\u0400' <= char <= '\u04FF' for char in user_input):
        raise ValueError("The script does not support your language.")

    cdvig = int(sys.argv[3])

    user_input = user_input.strip("'\"")
    names = user_input.split(',')
    names = [name.strip() for name in names]
    alphabet = "a b c d e f g h i j k l m n o p q r s t u v w x y z"
    alphabet_list = alphabet.split()
    task = sys.argv[1]
    if task == "encode":
        encode(alphabet_list, names, cdvig)
    elif task == "decode":
        decode(alphabet_list, names, cdvig)
    else:
        raise ValueError(
            "Incorrect task. Use 'encode' or 'decode'.")


if __name__ == '__main__':
    main()
