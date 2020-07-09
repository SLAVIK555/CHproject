import  subprocess
from clickhouse_driver import Client

from sys import argv

fvnpnum, topic = argv

client = Client('localhost', password='12345678')

client.execute('DROP TABLE IF EXISTS num_' + fvnpnum)

client.execute('CREATE TABLE IF NOT EXISTS num_0 (param UInt64, ptime Float64) ENGINE = Memory')

subprocess.Popen(['python3', 'mqtt_Listen_Sensor_Data.py', fvnpnum, topic])#Отвечает считывание данных из mqtt и запись из в базу данных

#Дропаем таблицу в начале, а не в конце, так как она может понадобиться другим процессам
