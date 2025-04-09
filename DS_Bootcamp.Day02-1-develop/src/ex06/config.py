# config.py
import os

file_path = os.path.join("..","..", "materials", "data.csv")
num_of_steps = 3
TELEGRAM_BOT_TOKEN  = "7778436241:AAHFbfXdrCJdqPyQb6zTr1X2aYZf0W93ZcA"
TELEGRAM_CHAT_ID = "-1002212407513"


report_template = """
Отчет
В результате подбрасывания монеты мы сделали {observations} наблюдений: {tails} из них выпала решка и {heads} голов.
Вероятности составляют {tail_percent:.2f}% и {head_percent:.2f}% соответственно. Наш
прогнозируем, что в следующих {steps} наблюдениях у нас будет: {predicted_tails} хвост и {predicted_heads} голов.
"""
