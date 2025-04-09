import logging
from random import randint

import config
import requests

logging.basicConfig(
    filename='analytics.log',
    level=logging.DEBUG,  
    format='%(asctime)s %(message)s',  
    datefmt='%Y-%m-%d %H:%M:%S',
)


class Research :

    def __init__(self,file_path,has_header):
        self.file_path = file_path
        self.has_header = has_header
        logging.debug(f"Инициализация Research file_path={file_path}, has_header={has_header}")

    def file_reader(self):
        try:
            logging.debug("Чтение файла..")
            with open(self.file_path, "r") as file:
                
                lines_for_out = []
                lines = [line.strip() for line in file.readlines()]
                for i in lines:
                    if i.replace(",", "").isalpha():
                        continue
                    lines_for_out.append(i)
                self.has_header = False
            for line in lines[1:]:
                
                values = line.split(",")
                if len(values) != 2 or not all(value in {"0", "1"} for value in values):
                    raise ValueError("Invalid data format. Each line must contain two values, either '0' or '1', separated by a comma.")
            logging.debug("Файл был успешно прочитан")
            return lines_for_out
        except FileNotFoundError:
            logging.error(f"Файл {self.file_path} не найден.")
            raise FileNotFoundError(f"The file '{self.file_path}' was not found.")
        
    def send_telegram_message(self, message):
        
        url = f"https://api.telegram.org/bot{config.TELEGRAM_BOT_TOKEN}/sendMessage"
        payload = {
            "chat_id": config.TELEGRAM_CHAT_ID,
            "text": message
        }
        try:
            response = requests.post(url, json=payload)
            response.raise_for_status() 
            logging.info("Сообщение успешно отправлено в Telegram.")
        except requests.exceptions.RequestException as e:
            logging.error(f"Ошибка при отправке сообщения в Telegram: {e}")
            raise

    def generate_report(self, data):
            if data:
                self.send_telegram_message("Отчет был успешно создан")
                logging.info(f"Отчет успешно создан:")
            else:
                self.send_telegram_message("Отчет не был создан из-за ошибки")
                logging.error(f"Ошибка при создании отчета:")
            

        
        
    class Calculations:

        def __init__(self,data):
            self.data = data
            logging.debug(f"Иницализация информации  {data}")

        def counts(self):
            counter = 0
            chet = 0
            for i in self.data:
                values = i.split(",")
                if values[0] == "1":
                    counter +=1
                else:
                    chet +=1
            out = [counter,chet]
            logging.debug(f"Подсчет количества голов и хвостов {out}")
            return out
        def fractions(counts):
            sum = counts[0] + counts[1]
            head_procent = counts[0]*100/sum
            tail_procent = counts[1]*100/sum
            out = [head_procent , tail_procent]
            logging.debug(f"Подсчет процентов голов и хвостов {out}")
            return out
        
    class Analytics(Calculations):
        def __init__(self, data):
            super().__init__(data)
            logging.debug(f"Наследования от родительского класса")
        def predict_random(self,n):
            mini_list = []
          
            
            for i in range(n):
                if randint(0,1) == 0:
                    mini_list.append([0, 1])
                else:
                    mini_list.append([1, 0])
            logging.debug(f"Возврат списков предсказаных наблюдений  {mini_list}")
            return mini_list
        
        def predict_last(self):
            if self.data:
                logging.debug(f"Вывод последнего элемента из file_reader(){self.data[-1] }")
                return self.data[-1] 
            else:
                logging.debug(f"Файл пустой")
                return None  
        
        def save_file(self, data, filename, extension='txt'):
            try:
                with open(f"{filename}.{extension}", 'w') as file:
                    file.write(data)
                logging.debug("Данные успешно сохранены.")
            except Exception as e:
                logging.error(f"Ошибка при сохранении файла: {e}")
                raise ValueError(f"An error occurred while saving the file: {e}")






