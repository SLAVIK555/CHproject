import  subprocess
from clickhouse_driver import Client

client = Client('localhost', password='12345678')

client.execute('DROP TABLE IF EXISTS num_0')

client.execute('CREATE TABLE IF NOT EXISTS num_0 (param UInt64, ptime Float64) ENGINE = Memory')

subprocess.Popen(['python3', 'mqtt_Listen_Sensor_Data.py'])#Отвечает считывание данных из mqtt и запись из в базу данных

#Дропаем таблицу в начале, а не в конце, так как она может понадобиться другим процессам
