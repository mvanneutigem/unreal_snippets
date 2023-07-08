"""This script will run on unreal startup."""
import unreal
from python_demo_plugin import menu_utils
from python_demo_plugin import BP_functions # expose BP functions

if __name__ == "__main__":
    menu_utils.create_widget_menu_entry(
        '/DemoPluginPython/demo_widget',
        "LevelEditor.LevelEditorToolBar.PlayToolBar",
        unreal.MultiBlockType.TOOL_BAR_BUTTON
    )
