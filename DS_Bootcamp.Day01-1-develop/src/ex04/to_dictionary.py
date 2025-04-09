def tupli():
    list_of_tuples = [
        ('Russia', '25'),
        ('France', '132'),
        ('Germany', '132'),
        ('Spain', '178'),
        ('Italy', '162'),
        ('Portugal', '17'),
        ('Finland', '3'),
        ('Hungary', '2'),
        ('The Netherlands', '28'),
        ('The USA', '610'),
        ('The United Kingdom', '95'),
        ('China', '83'),
        ('Iran', '76'),
        ('Turkey', '65'),
        ('Belgium', '34'),
        ('Canada', '28'),
        ('Switzerland', '26'),
        ('Brazil', '25'),
        ('Austria', '14'),
        ('Israel', '12')
    ]
    tup_to_dict(list_of_tuples)


def tup_to_dict(list_of_tuples):
    dicit = {}
    key = 0

    for i in list_of_tuples:
        for j in i:

            if j.replace(" ", "").isalpha():
                value = j
            else:
                if j in dicit.keys():
                    key = j+"+a"
                else:
                    key = j
        dicit[key] = value
    for i, j in dicit.items():
        print(f"'{i.replace('+a', '')}':'{j}'")


if __name__ == '__main__':
    tupli()
