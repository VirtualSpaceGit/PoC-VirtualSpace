#include "file_monitor.h"
#include <cstdio>
#include <filesystem>
#include <cstdlib>
#include <thread>
#include <chrono>

FileMonitor::FileMonitor(const std::string& fileName) : fileName(fileName) {
    if (fileExists()) {
        readFileContent();
        lastWriteTime = getFileWriteTime();
    } else {
        fprintf(stderr, "Error: %s does not exist. Please create the file with the desired content first.\n", fileName.c_str());
        exit(1);
    }
}

void FileMonitor::readFileContent() {
    FILE* fp = fopen(fileName.c_str(), "r");
    if (!fp) return;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    currentContent.resize(size);
    fread(&currentContent[0], 1, size, fp);
    fclose(fp);
}

void FileMonitor::createFileWithContent(const std::string& content) {
    FILE* fp = fopen(fileName.c_str(), "w");
    if (!fp) return;
    fwrite(content.c_str(), 1, content.size(), fp);
    fclose(fp);
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
            printf("File %s deleted. Restoring...\n", fileName.c_str());
            createFileWithContent(currentContent);
            lastWriteTime = getFileWriteTime();
            printf("File restored.\n");
        } else {
            auto currentWriteTime = getFileWriteTime();
            if (currentWriteTime != lastWriteTime) {
                printf("File %s modified. Updating content...\n", fileName.c_str());
                readFileContent();
                lastWriteTime = currentWriteTime;
                printf("File content updated.\n");
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void FileMonitor::startMonitoring() {
    monitorFile();
}
