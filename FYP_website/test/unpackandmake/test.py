import os, subprocess

os.popen('unzip Code.zip')
#os.popen('sh ./cmd.sh', cwd = './Code')
#os.popen('cp ./p.bc ../', cwd = './Code')
#subprocess.Popen('unzip Code.zip', cwd = '.', shell=True)
os.popen('cp ./cmd.sh ./Code')
p = subprocess.Popen('./cmd.sh', cwd = './Code', shell=True)
retcode = p.wait()
subprocess.Popen('cp ./p.bc ../', cwd = './Code', shell=True)
