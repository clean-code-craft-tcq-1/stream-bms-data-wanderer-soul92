import random
import json

stream_limit = 15

BMS_allowed_range = {'temperature': {'min': 0, 'max': 45},
                    'soc': {'min': 20, 'max': 80},
                    'charge_rate': {'min': 0, 'max': 0.8}}

allowed_format = ['json']


def isSuportedFormat(format):
    if format in allowed_format:
        return True
    else :
        return False

def get_min_max_range(BMS_allowed_range):
    if len(BMS_allowed_range) > 0 :
        min_max_range = []
        for key, value in BMS_allowed_range.items():
            min_value = BMS_allowed_range[key]['min']
            max_value = BMS_allowed_range[key]['max']
            var = (min_value, max_value)
            min_max_range.append(var)
        return min_max_range
    else :
       return "BMS_Allowed_Range is not defined"

def get_bms_fields(BMS_allowed_range):
    fields = []
    for key in BMS_allowed_range.keys():
        field = key
        fields.append(field)
    return(fields)

def plugin_sensor_stream(min_max_range, stream_limit, fields):
    if stream_limit > 0: 
        for i in range (0,stream_limit):
            sensor_output = generate_stream_data (min_max_range, fields )
            print_to_consol(sensor_output, allowed_format )
        return True
    else :
        return "Stream_limit is not defined"


def generate_stream_data(min_max_range, fields ):
    j = 0
    timeseries = {}
    for field in fields :
        value = random.randint(min_max_range[j][0], int(min_max_range[j][1]))
        timeseries[field] = value
        j = j+1
    return timeseries

def print_to_consol(sensor_output, allowed_format):
    if len(sensor_output) > 0:
        allowed_format_object = json.dumps(sensor_output, indent = 4)  
        print(allowed_format_object) 
        return True
    else :
        return "Sensor readings are Empty"



def plugin_sensor_stream(min_max_range, stream_limit, fields):
    if streamlimit > 0: 
        for i in range (0,stream_limit):
            sensor_output = generate_stream_data (min_max_range, fields )
            print_to_consol(sensor_output)
            return true
    else :
        return "Stream_limit is not defined"


def generate_stream_data(min_max_range, fields ):
    j = 0
    timeseries = {}
    for field in fields :
        value = random.randint(min_max_range[j][0], int(min_max_range[j][1]))
        timeseries[field] = value
        j = j+1
    return timeseries

def print_to_consol(sensor_output, allowed_format):
    if len(sensor_output) > 0:
        allowed_format_object = json.dumps(sensor_output, indent = 4)  
        print(allowed_format_object) 
        return True
    else :
        return "Sensor readings are Empty"

