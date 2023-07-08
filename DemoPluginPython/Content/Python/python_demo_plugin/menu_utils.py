"""Menu utilities."""
import os    
import unreal


COMMAND = """
import unreal; 
unreal.EditorUtilitySubsystem().spawn_and_register_tab(
    unreal.EditorAssetLibrary.load_asset('{0}')
);
"""


def create_submenu(menu_name, section, submenu_name, submenu_label):
    """Create new submenu.
    
    Args:
        menu_name (str): name of menu to add submenu to.
        section (str): name of section to add.
        submenu_name (str): name of the submenu.
        submenu_label (str): label of the submenu.
    Returns:
        unreal.Menu: created submenu.
    """
    menus = unreal.ToolMenus.get()

    menu = menus.find_menu(menu_name)
    if not menu:
        return

    custom_menu = menu.add_sub_menu(
        menu.get_name(), 
        section, 
        submenu_name, 
        submenu_label, 
        tool_tip="Launch Py tool demo"
    )
    return custom_menu


def create_widget_menu_entry(
    widget, 
    menu_name, 
    button_type
):
    """Create menu entry.
    
    Args:
        widget (str): path of the widget to create a menu entry for.
        menu_name (str): name of the menu to add widget to.
        button_type (unreal.MultiBlockType): menu entry type.
    """
    menus = unreal.ToolMenus.get()

    menu = menus.find_menu(menu_name)
    if not menu:
        return
    
    name = os.path.basename(widget)
    entry = unreal.ToolMenuEntry(
        name=name,
        type=button_type,
    )
    entry.set_label(name)


    entry.set_string_command(
        unreal.ToolMenuStringCommandType.PYTHON, 
        unreal.Name(""), 
        string=COMMAND.format(widget)
    )
    menu.add_menu_entry("Items", entry)
