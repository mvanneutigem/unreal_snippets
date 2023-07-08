"""Expose py functions to BP."""
import unreal


def create_level_sequence(shotname):
    """Create a level sequence.
    
    Args:
        shotname (str): what to name the level sequence.

    Returns:
        bool: true
    """
    print(shotname)
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    level_sequence = unreal.AssetTools.create_asset(
        asset_tools, 
        asset_name = shotname,
        package_path = "/Game/", 
        asset_class = unreal.LevelSequence, 
        factory = unreal.LevelSequenceFactoryNew()
    )
    return True

    
@unreal.uclass()
class PythonBPFunctionLibrary(unreal.BlueprintFunctionLibrary):

    @unreal.ufunction(static=True, params=[str], ret=bool, meta=dict(Category="Python functions"))
    def bp_create_levelsequence(shotname="String",):
        """Create levelsequence through python."""
        return create_level_sequence(shotname)
