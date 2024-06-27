#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the ASCII art of a given Linux distribution name
void printAsciiArt(const char *distroName) {

    if (strncmp(distroName, "ubuntu",3) == 0) {
        // Add ASCII art for Ubuntu here
    printf("         __                __       \n");
    printf("  __  __/ /_  __  ______  / /___  __\n");
    printf(" / / / / __ \\/ / / / __ \\/ __/ / / /\n");
    printf("/ /_/ / /_/ / /_/ / / / / /_/ /_/ / \n");
    printf("\\__,_/_.___/\\__,_/_/ /_/\\__/\\__,_/  \n");
    } else if (strncmp(distroName, "fedora",3) == 0) {
        // Add ASCII art for Fedora here
            printf("   ____         __                \n");
    printf("  / __/__  ____/ /___  _________ _\n");
    printf(" / /_/ _ \\/ __  / __ \\/ ___/ __ `/\n");
    printf("/ __/  __/ /_/ / /_/ / /  / /_/ / \n");
    printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
    } else if (strncmp(distroName, "debian",3) == 0) {
        // Add ASCII art for Debian here
            printf("       __     __    _           \n");
    printf("  ____/ /__  / /_  (_)___ _____ \n");
    printf(" / __  / _ \\/ __ \\/ / __ `/ __ \\\n");
    printf("/ /_/ /  __/ /_/ / / /_/ / / / /\n");
    printf("\\__,_/\\___/_.___/_/\\__,_/_/ /_/ \n");
    } else if (strncmp(distroName, "pop",3) == 0) {
        // Add ASCII art for Pop!_OS here
            printf("                                    \n");
    printf("    ____  ____  ____  _ ____  _____\n");
    printf("   / __ \\/ __ \\/ __ \\(_) __ \\/ ___/\n");
    printf("  / /_/ / /_/ / /_/ / / /_/ (__  ) \n");
    printf(" / .___/\\____/ .___(_)/____/____/  \n");
    printf("/_/         /_/                  \n");
    } else if (strncmp(distroName, "arch",3) == 0) {
        // Add ASCII art for Arch here
            printf("                   __  \n");
    printf("  ____ ___________/ /_ \n");
    printf(" / __ `/ ___/ ___/ __ \\\n");
    printf("/ /_/ / /  / /__/ / / /\n");
    printf("\\__,_/_/   \\___/_/ /_/ \n");
    } else {
            printf("    __               ____     __       __  \n");
    printf("   / /_  _________  / __/__  / /______/ /_ \n");
    printf("  / __ \\/ ___/_  / / /_/ _ \\/ __/ ___/ __ \\\n");
    printf(" / /_/ / /    / /_/ __/  __/ /_/ /__/ / / /\n");
    printf("/_.___/_/    /___/_/  \\___/\\__/\\___/_/ /_/  \n");
    }

}

// /proc/cpuinfo
char *cpu_stat(void){
    char *cp;
    FILE *fp2;
    char *line = NULL;
    size_t n = 0;
    fp2 = fopen("/proc/cpuinfo","r");
    if(fp2 == NULL){
        perror("Error opening /proc/cpuinfo");
        return NULL;
    }
    while(getline(&line,&n,fp2) != -1){
        if(strncmp(line,"model name :",10) == 0){
            cp = line + 13;
            break;
        }
    }

    fclose(fp2);
    return cp;
}

char *read_distro_name(){
    char *dt;
    FILE *fp;
    char *line = NULL;
    size_t n = 0;
    fp = fopen("/etc/os-release","r");
    if(fp == NULL){
        perror("Error opening /etc/os-release");
        return NULL;
    }
    while(getline(&line,&n,fp) != -1){
        if(strncmp(line,"ID=",3) == 0){
            dt = line+3;
            break;
        }
    }

    fclose(fp);
    return dt;
}




int main(){
    struct utsname uname_pointer;
	uname(&uname_pointer);                   ;
	//printAsciiArt();
    char *distro_name = read_distro_name();
    char *username = getenv("USER");
    char *shell_name = getenv("SHELL");
    char *cpu_name = cpu_stat();
    printAsciiArt(distro_name);
    printf("\n├────────────────\n\n");
    printf(" DISTRO: %s",distro_name);
    printf(" USER: %s\n",username);
    printf(" HOST: %s\n", uname_pointer.nodename);
    printf(" KERNEL: %s\n", uname_pointer.release);
    printf("# SHELL: %s\n",shell_name);
    char *de = getenv("XDG_CURRENT_DESKTOP");
    printf(" DE/WM: %s\n", de);
    printf("󰍛 CPU: %s",cpu_name);
    //printf("󰍹 GPU: %s",cpu_name);

    printf("\n├────────────────\n");
    printf("> berzifetch - built by spirizeon\n");
    return 0;
}
