"""Python test for the FBX exporter.
This file has to be named wiht the test_ prefix to be picked up in unreal.
"""
import os
import unittest

import export_to_fbx

class test_fbx_export(unittest.TestCase):

    def test_sequencer_export(self):
        """Test exporting from the sequencer to an fbx file."""
        path = "/Game/levels/Primitives.Primitives"
        sequencer_path = "/Game/sequences/primitives_sequence.primitives_sequence"
        output_path = "C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output_sequencer_test.fbx"
        export_to_fbx.export_sequencer_to_fbx(path, sequencer_path, output_path)
        print(output_path)
        self.assertTrue(os.path.isfile(output_path))

    def test_level_export(self):
        """Test exporting a level to an fbx file."""
        level_name = "Primitives"
        output_path = "C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output_level_test.fbx"
        export_to_fbx.export_level_to_fbx(level_name, output_path)
        print(output_path)
        self.assertTrue(os.path.isfile(output_path))

    def runTest(self):
        print("running tests...")
        self.test_sequencer_export()
        self.test_level_export()

obj = test_fbx_export()
obj.runTest()