import subprocess
import os
class Color:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    RESET = '\033[0m'

def command(caption, arg):
    output = subprocess.run(arg, capture_output=True, text=True).stdout
    print(f"{caption}: {output}", end="")

os_dump = subprocess.run(["lsb_release", "-a"], capture_output=True, text=True).stdout
lines = os_dump.split('\n')
for line in lines:
    if line.startswith('Distributor ID:'):
        os_art = line.split(':')[1].strip()
    if line.startswith('Description:'):
        os_name = line.split(':')[1].strip()
        break

# ASCII art
print(Color.CYAN)
os.system(f"pyfiglet -f slant {os_art}")
print(Color.RESET)
print(f"├────────────────")

print(Color.YELLOW)
# OS stats
print(f" Distro: {os_name}")

command(f" USER", "whoami")
command(f" HOST", "hostname")
command(f" KERNEL", ["uname", "-sr"])

# CPU stats
cpustat = subprocess.run("lscpu", capture_output=True, text=True).stdout
cpustat = cpustat.split('\n')
for line in cpustat:
    if 'Model name' in line:
        cpu_name = line.split(':')[1].strip()
        break
print(f"󰍛 CPU: {cpu_name}")

# GPU stats
gpustat = subprocess.run("lspci", capture_output=True, text=True).stdout
gpustat = gpustat.split('\n')
gpucounter = 0
for line in gpustat:
    if 'VGA compatible controller' in line:
        gpu_name = line.split(':')[2].strip()
        gpucounter += 1
        print(f"󰍹 GPU {gpucounter}: {gpu_name}")

# Shell
shell = os.getenv('SHELL')
print(f" SHELL: {shell}")

# Uptime
upstat = subprocess.run("uptime", capture_output=True, text=True).stdout
upstat = upstat.split()
uptime = upstat[2]
uptime = uptime.split(',')[0]
print(f"󰅐 UPTIME: {uptime}")

DE_dump = os.getenv('XDG_CURRENT_DESKTOP')
DE = DE_dump.split(':')
DE = DE[1]
print(f" DE/WM: {DE}")
print(Color.RESET)
print(f"├────────────────")
