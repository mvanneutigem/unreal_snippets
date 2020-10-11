
import unreal

'''
	Summary:
		This is an example of how to export fbx with animation  information with sequencer.  In this example we load a map and corresponding level sequence,
		grab all of the bindings from that sequence, set some export options, then export the fbx file.
		To save less you need to only choose those bindings you want to export. 
		Open the Python interactive console and do similarly as below:
			import sequencer_fbx_examples
			sequencer_fbx_examples.export_fbx("/Game/Maps/FbxTest","/Game/FbxTest", "D:\\FBX_Test.fbx")
		
	Params:
	    map_asset_path - String that points to the map that conatains the possessables contained in the Movie Scene sequence.
		sequencer_asset_path - String that points to the Movie Scene sequence asset.
		output_file - String that shows the full path of the created fbx file.
'''
def export_sequencer_to_fbx(map_asset_path, sequencer_asset_path, output_file):
    # this works :)
    # Load the map, get the world
    world = unreal.EditorLoadingAndSavingUtils.load_map(map_asset_path)
	# Load the sequence asset
    sequence = unreal.load_asset(sequencer_asset_path, unreal.LevelSequence)
	# Set Options
    export_options = unreal.FbxExportOption()
    export_options.ascii = True
    export_options.level_of_detail = False
    # Get Bindings
    bindings = sequence.get_bindings()
    # Export
    unreal.SequencerTools.export_fbx(world, sequence, bindings, export_options, output_file)
    return

def export_level(level, output_file):
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
            export_task.exporter = unreal.StaticMeshExporterFBX() # for some reason this keeps crashin :(
    
        exporter = unreal.Exporter.run_asset_export_task(export_task)
        i += 1

def test_sequencer_export():
    path = "/Game/levels/Primitives.Primitives"
    sequencer_path = "/Game/sequences/primitives_sequence.primitives_sequence"
    output_path = "C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output.fbx"
    export_sequencer_to_fbx(path, sequencer_path, output_path)


def export_level_to_obj(level_name="Primitives"):
    # this works but not for brushes~! :)
    level_name = "Primitives"
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    levels = asset_registry.get_assets_by_class("World")

    level_to_export = None
    for level in levels:
        if level.asset_name == level_name:
            level_to_export = level.get_asset()

    if not level_to_export:
        return

    export_task = unreal.AssetExportTask()
    export_task.object = level_to_export
    export_task.filename = "C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output_level_headless.fbx"
    export_task.automated = True

    export_options = unreal.FbxExportOption()
    export_options.ascii = True
    export_options.level_of_detail = False
    export_task.options = export_options
    export_task.prompt = False
    export_task.exporter = unreal.LevelExporterFBX()#unreal.LevelExporterLOD()

    unreal.ExporterFBX.run_asset_export_task(export_task)#unreal.Exporter.run_asset_export_task(export_task)

export_level_to_obj()