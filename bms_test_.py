import unittest
import stream_bms_data

class test_bms_stream(unittest.TestCase):
    def test_to_check_format(self):
        self.assertTrue(stream_bms_data.isSuportedFormat('list') == False)
    
    def test_to_check_BMS_allowed_range(self):
        self.assertTrue(stream_bms_data.get_min_max_range({} ) == "BMS_Allowed_Range is not defined")

    def test_print_to_consol_negative(self):
        self.assertTrue(stream_bms_data.print_to_consol({}, 'json') == "Sensor readings are Empty" )

    def test_print_to_consol_positive(self):
        self.assertTrue(stream_bms_data.print_to_consol({'temperature': 44, 'soc': 70, 'charge_rate': 0}, 'json') )

if __name__ == '__main__':
    unittest.main()
    min_max_range = get_min_max_range(BMS_allowed_range)
    fields = get_bms_fields(BMS_allowed_range)
    plugin_sensor_stream(min_max_range, stream_limit, fields)
    
