# Данные

import numpy as np

# Найдем выборочную дисперсию (деление на n-1)
import statistics
stringi = "4.0 5.0 4.0 5.0 5.0"
numbers = [float(i) for i in stringi.split()]

variance = statistics.variance(numbers)  # Выборочная дисперсия

# Округлим до 2 знаков
round(variance, 2)
print(variance)



# numbers = [4.0, 0.5, 4.5, 5.0, 0.5, 0.5, 3.5, 4.0, 4.0, 4.0, 0.5, 4.0, 4.5, 4.0, 4.0, 4.5, 3.5, 0.5, 4.0, 4.0, 0.5, 0.5, 4.0, 0.5, 4.5, 0.5, 5.0]

# average = sum(numbers) / len(numbers)
# print(average)

# numbers = [4.0,1.0,0.5]

# # Calculate the median
# median_value = np.median(numbers)
# print(median_value)