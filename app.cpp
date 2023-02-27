#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

// Função para imprimir informações do sistema operacional
int get_os_info(std::string& os_info) {
    std::ifstream os_release("/etc/os-release");
    std::string line;
    std::string name, version;
    while (getline(os_release, line)) {
        std::istringstream iss(line);
        std::string key, value;
        getline(iss, key, '=');
        getline(iss, value);
        if (key == "PRETTY_NAME") {
            name = value;
        } else if (key == "VERSION_ID") {
            version = value;
        }
    }
    os_release.close();
    os_info = "OS: " + name + " " + version + "\n";
    return 0;
}

// Função para imprimir informações do processador
int get_cpu_info(std::string& cpu_info) {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::string model_name;
    int num_cores = 0;
    while (getline(cpuinfo, line)) {
        std::istringstream iss(line);
        std::string key, value;
        getline(iss, key, ':');
        getline(iss, value);
        if (key == "model name") {
            model_name = value;
        } else if (key == "cpu cores") {
            num_cores = atoi(value.c_str());
        }
    }
    cpuinfo.close();
    cpu_info = "CPU: " + model_name + " (" + std::to_string(num_cores) + " cores)\n";
    return 0;
}

// Função para imprimir informações da memória RAM
int get_memory_info(std::string& memory_info) {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    int total_memory = 0;
    while (getline(meminfo, line)) {
        std::istringstream iss(line);
        std::string key, value;
        getline(iss, key, ':');
        getline(iss, value);
        if (key == "MemTotal") {
            total_memory = atoi(value.c_str()) / 1024;
            break;
        }
    }
    meminfo.close();
    memory_info = "Memory: " + std::to_string(total_memory) + " MB\n";
    return 0;
}

// Função principal
int main() {
    std::string os_info, cpu_info, memory_info;
    get_os_info(os_info);
    get_cpu_info(cpu_info);
    get_memory_info(memory_info);
    std::cout << os_info << cpu_info << memory_info;
    return 0;
}

