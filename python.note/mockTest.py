# -*- coding: utf-8 -*-

from fileremove import rm
import mock
import unittest

class RmTestCase(unittest.TestCase):
    # Mock an item where it is used, not where it came from
    @mock.patch('fileremove.os.path')
    @mock.patch('fileremove.os')
    def test_rm(self, mock_os, mock_path):
        # set up the mock
        mock_path.isfile.return_value = False
        
        rm("any path")
        
        # test that the remove call was NOT called.
        self.assertFalse(mock_os.remove.called, "Invokes the remove method when it's not a file.")
        
        # make the file 'exist'
        mock_path.isfile.return_value = True
        rm("any path")
        
        mock_os.remove.assert_called_with("any path")

if __name__ == '__main__':
    unittest.main()
