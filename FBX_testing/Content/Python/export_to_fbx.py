"""Exporting to FBX helpers."""
import unreal

def export_sequencer_to_fbx(map_asset_path, sequencer_asset_path, output_file):
    """Export animated data from sequencer to fbx file.

    Args:
        map_asset_path (str): Path of the level to load.
        sequencer_asset_path (str): Path of the sequencer to export.
        output_file (str): file to output to.
    """
    # Load the map, get the world
    world = unreal.EditorLoadingAndSavingUtils.load_map(map_asset_path)
	# Load the sequence asset
    sequence = unreal.load_asset(sequencer_asset_path, unreal.LevelSequence)
	# Set Options
    export_options = unreal.FbxExportOption()
    export_options.ascii = True
    export_options.level_of_detail = False
    bindings = sequence.get_bindings()
    # Export
    unreal.SequencerTools.export_fbx(world, sequence, bindings, export_options, output_file)


def export_level_to_fbx(level_name, output_file):
    """Export an entire level to a static FBX.
    
    Args:
        level_name (str): Name of the level to export.
        output_file (str): file to output to.
    """
    # Get registry of assets
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    levels = asset_registry.get_assets_by_class("World")
    # Find level matching name
    level_to_export = None
    for level in levels:
        if level.asset_name == level_name:
            level_to_export = level.get_asset()
    if not level_to_export:
        return
    # Create export task
    export_task = unreal.AssetExportTask()
    export_task.object = level_to_export
    export_task.filename = output_file
    export_task.automated = True
    # Populate export options.
    export_options = unreal.FbxExportOption()
    export_options.ascii = True
    export_options.level_of_detail = False
    export_task.options = export_options
    export_task.prompt = False
    export_task.exporter = unreal.LevelExporterFBX()
    # Export
    unreal.ExporterFBX.run_asset_export_task(export_task)


def export_assets_from_level_to_fbx(level, output_file):
    """WIP export each asset to a separate file, not yet working."""
    output_file = "C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output_level{0}.fbx"
    level_actors = unreal.EditorLevelLibrary.get_all_level_actors()
    i = 0
    for actor in level_actors:
        export_task = unreal.AssetExportTask()
        export_task.object = actor
        export_task.filename = output_file.format(i)
        export_task.automated = True
        export_task.prompt = False
        if type(actor) == unreal.StaticMeshActor:
            # for some reason this keeps crashin :(
            export_task.exporter = unreal.StaticMeshExporterFBX() 
    
        exporter = unreal.Exporter.run_asset_export_task(export_task)
        i += 1