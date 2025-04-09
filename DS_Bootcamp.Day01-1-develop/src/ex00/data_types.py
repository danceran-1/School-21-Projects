def data_types():   
    variables = [10, "privet", 10.5, True, [], {}, (), {1, 2, 3}]
    types = [type(var).__name__ for var in  variables]

    print(f"[{', '.join(map(str, types))}]")


if __name__ == '__main__':
    data_types()
