#!/usr/bin/env python3
import sys
import subprocess
import os
import shutil

def main():
    if hasattr(sys, 'base_prefix') and sys.base_prefix != sys.prefix:
        print("Скрипт запущен в виртуальном окружении.")
    else:
        raise EnvironmentError("Скрипт не запущен в виртуальном окружении.")
    install()
    archive_venv()


def install():
    try:
        with open('requirements.txt', 'w') as file:
            file.write('beautifulsoup4\n')
            file.write('pytest\n')
    except FileNotFoundError as e:
        print(f"Error: {e}")
    subprocess.check_call([sys.executable, "-m", "pip", "install","-r", 'requirements.txt'])
    os.remove('requirements.txt')
    file_add()

def file_add():
    try:
        result = subprocess.run(['pip', 'freeze'], capture_output=True, text=True)
        with open('requirements.txt', 'w') as file:
            file.write(result.stdout)
    except FileNotFoundError as e:
        print(f"Error: {e}")
        
def archive_venv():
    venv_path = os.getcwd()
    shutil.make_archive('venv_archive', 'zip', venv_path)
    




if __name__ == "__main__":
    try:
        main()
    except EnvironmentError as e:
        print(f"Error: {e}")
    except Exception as e:
         print(f"Произошла непредвиденная ошибка: {e}")