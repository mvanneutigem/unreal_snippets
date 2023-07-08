# unreal_snippets

For my own use, some unreal snippets for future reference.

My local install directory: 
C:\unreal\UE_4.24\Engine\Binaries\Win64

Executing commands from commandline:
UE4Editor "\path\to\project\project.uproject" -ExecCmds="some command; quit;" -buildmachine -stdout -unattended -nopause -nosplash

Executing python scripts from commandline:
UE4Editor  "\path\to\project\project.uproject" -run=pythonscript -script="\path\to\somescript.py" -stdout -nosplash -buildmachine