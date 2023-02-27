#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/utsname.h>

int get_os_info(std::string& os_info) {
    std::ifstream os_release("/etc/os-release");
    if (os_release.is_open()) {
        std::string line;
        std::string os_name;
        std::string os_version;
        while (getline(os_release, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "PRETTY_NAME")
                    os_name = value;
                else if (key == "VERSION")
                    os_version = value;
            }
        }
        os_release.close();
        os_info = " : " + os_name + "\n";
        os_info += "ﲶ : " + os_version + "\n";
    }
    return 0;
}

int get_kernel_info(std::string& kernel_info) {
    struct utsname buf;
    if (uname(&buf) == 0) {
        kernel_info = " : " + std::string(buf.release) + "\n";
    }
    return 0;
}

int get_distro_info(std::string& distro_info) {
    std::ifstream lsb_release("/etc/lsb-release");
    if (lsb_release.is_open()) {
        std::string line;
        std::string distro_name;
        while (getline(lsb_release, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "DISTRIB_DESCRIPTION")
                    distro_name = value;
            }
        }
        lsb_release.close();
        if (!distro_name.empty())
            distro_info = "華: " + distro_name + "\n";
    }
    return 0;
}

int get_pkg_info(std::string& pkg_info) {
    std::ifstream pkg_count("/var/db/pkg/count");
    if (pkg_count.is_open()) {
        std::string line;
        int count;
        if (getline(pkg_count, line)) {
            count = std::stoi(line);
            pkg_info = " : " + std::to_string(count) + " (pkg)\n";
        }
        pkg_count.close();
    }
    return 0;
}

int get_ui_info(std::string& ui_info) {
    std::string wm_name = std::getenv("XDG_CURRENT_DESKTOP");
    std::string de_name = std::getenv("XDG_SESSION_DESKTOP");
    if (!wm_name.empty())
        ui_info = "类: " + wm_name + "\n";
    else if (!de_name.empty())
        ui_info = "类: " + de_name + "\n";
    return 0;
}

int get_shell_info(std::string& shell_info) {
    std::string shell_name = std::getenv("SHELL");
    if (!shell_name.empty()) {
        size_t pos = shell_name.rfind('/');
        if (pos != std::string::npos)
            shell_name = shell_name.substr(pos+1);
        shell_info = " : " + shell_name + "\n";
    }
    return 0;
}

int get_memory_info(std::string& memory_info) {
    std::ifstream meminfo("/proc/meminfo");
    if (meminfo.is_open()) {
        std::string line;
        int mem_total = 0, mem_free = 0;
        while (getline(meminfo, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':') && std::getline(iss, value)) {
                if (key == "MemTotal")
                    mem_total = std::stoi(value) / 1024;
                else if (key == "MemFree")
                    mem_free = std::stoi(value) / 1024;
            }
        }
        meminfo.close();
        memory_info = "e: " + std::to_string(mem_total - mem_free) + "MiB / " +
                      std::to_string(mem_total) + "MiB (" +
                      std::to_string((mem_total - mem_free) * 100 / mem_total) + "%)\n";
    }
    return 0;
}

int main() {
    std::string os_info, kernel_info, distro_info, pkg_info, ui_info, shell_info, memory_info;
    get_os_info(os_info);
    get_kernel_info(kernel_info);
    get_distro_info(distro_info);
    get_pkg_info(pkg_info);
    get_ui_info(ui_info);
    get_shell_info(shell_info);
    get_memory_info(memory_info);

    std::cout << "        #####           " << shell_info;
    std::cout << "       #######          ------------\n";
    std::cout << "       ##O#O##          " << os_info;
    std::cout << "       #######          " << kernel_info;
    std::cout << "     ###########        " << pkg_info;
    std::cout << "    #############       " << ui_info;
    std::cout << "   ###############      " << memory_info;
    std::cout << "   ################     \n";
    std::cout << "  #################\n";
    std::cout << "#####################\n";
    std::cout << "#####################\n";
    std::cout << "  #################\n";

    return 0;
}

