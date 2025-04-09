# config.py
import os

num_of_steps = 3
file_path = os.path.join("..","..", "materials", "data.csv")

report_template = """
Отчет
В результате подбрасывания монеты мы сделали {observations} наблюдений: {tails} из них выпала решка и {heads} голов.
Вероятности составляют {tail_percent:.2f}% и {head_percent:.2f}% соответственно. Наш
прогнозируем, что в следующих {steps} наблюдениях у нас будет: {predicted_tails} хвост и {predicted_heads} голов.
"""
