#include "file_monitor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

FileMonitor::FileMonitor(const std::string& fileName) : fileName(fileName) {
    if (fileExists()) {
        readFileContent();
        lastWriteTime = getFileWriteTime();
    }
    else {
        std::cerr << "Error: " << fileName << " does not exist. Please create the file with the desired content first." << std::endl;
        std::exit(1);
    }
}

void FileMonitor::readFileContent() {
    std::ifstream inFile(fileName);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    currentContent = buffer.str();
    inFile.close();
}

void FileMonitor::createFileWithContent(const std::string& content) {
    std::ofstream outFile(fileName);
    outFile << content;
    outFile.close();
}

bool FileMonitor::fileExists() const {
    return std::filesystem::exists(fileName);
}

std::filesystem::file_time_type FileMonitor::getFileWriteTime() const {
    return std::filesystem::last_write_time(fileName);
}

void FileMonitor::monitorFile() {
    while (true) {
        if (!fileExists()) {
            std::cout << "File " << fileName << " deleted. Restoring..." << std::endl;
            createFileWithContent(currentContent);
            lastWriteTime = getFileWriteTime();
            std::cout << "File restored." << std::endl;
        }
        else {
            auto currentWriteTime = getFileWriteTime();
            if (currentWriteTime != lastWriteTime) {
                std::cout << "File " << fileName << " modified. Updating content..." << std::endl;
                readFileContent();
                lastWriteTime = currentWriteTime;
                std::cout << "File content updated." << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void FileMonitor::startMonitoring() {
    monitorFile();
}
