#!/usr/bin/env python3
import os

venv_name = 'danceran'
current_directory = os.path.dirname(os.path.abspath(__file__))
print(current_directory)

venv_path = os.path.join(current_directory, venv_name) 
tru_path = os.path.abspath(venv_path) 
try:
    os.system(f'python3 -m venv {venv_path}')
    print(f"Ваше текущее виртуальное окружение - {tru_path}")
except Exception as e:
    print(f"Произошла ошибка: {e}")
