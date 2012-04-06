import subprocess

cmd = subprocess.Popen(["sleep 3; ls"], 
    cwd="/tmp", 
    shell=True, executable="/bin/bash",
    stdout=subprocess.PIPE
    )
print cmd.communicate()[0]

