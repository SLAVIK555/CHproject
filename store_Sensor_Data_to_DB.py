from clickhouse_driver import Client
import json

client = Client('localhost', password='12345678')

# Function to save param to DB Table
def param_ptime_Data_Handler(jsonData, FVNPnum):
	#Parse Data 
	json_Dict = json.loads(jsonData)
	param = json_Dict['param']
	ptime = json_Dict['ptime']
	
	#Push into DB Table
	ptQuery = '%s %s %s %d %s %f %s' % ('INSERT INTO num_' FVNPnum ' (param, ptime) VALUES (' param ', ' ptime ')')
	#pQuery = '%s %d %s' % ('INSERT INTO num_0 (param) VALUES (' param ')')
	client.execute(ptQuery)


# Function to save ptime to DB Table
#def ptime_Humidity_Data_Handler(jsonData):
#	#Parse Data 
#	json_Dict = json.loads(jsonData)
#	ptime = json_Dict['ptime']
#	
#	#Push into DB Table
#	tQuery = '%s %d %s' % ('INSERT INTO num_0 (ptime) VALUES (' ptime ')')
#	client.execute(tQuery)


#===============================================================
# Master Function to Select DB Funtion based on MQTT Topic

def sensor_Data_Handler(Topic, jsonData, FVNPnum):
	param_ptime_Data_Handler(jsonData, FVNPnum)
#	if Topic == "Home/MQTT/param":
#		param_Data_Handler(jsonData)
#	elif Topic == "Home/MQTT/ptime":
#		ptime_Data_Handler(jsonData)	


