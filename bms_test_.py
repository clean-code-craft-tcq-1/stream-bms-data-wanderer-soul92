import unittest
import stream_bms_data

class test_bms_stream(unittest.TestCase):
    def test_to_check_format(self):
        self.assertTrue(stream_bms_data.isSuportedFormat('list') == False)
    
    def test_to_check_BMS_allowed_range(self):
        self.assertTrue(stream_bms_data.get_min_max_range({} ) == "BMS_Allowed_Range is not defined")

    def test_print_to_consol_negative(self):
        self.assertTrue(stream_bms_data.print_to_consol({}, 'json') == "Sensor readings are Empty" )

if __name__ == '__main__':
    min_max_range = stream_bms_data.get_min_max_range(stream_bms_data.BMS_allowed_range)
    fields = stream_bms_data.get_bms_fields(stream_bms_data.BMS_allowed_range)
    stream_bms_data.plugin_sensor_stream(min_max_range, stream_bms_data.stream_limit, fields)
    #print("confirm_test_cases")
    
    unittest.main()
    
    
