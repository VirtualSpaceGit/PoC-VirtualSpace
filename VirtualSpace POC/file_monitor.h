#ifndef FILE_MONITOR_H
#define FILE_MONITOR_H

#include <string>
#include <filesystem>

class FileMonitor {
public:
    FileMonitor(const std::string& fileName);
    void startMonitoring();

private:
    std::string fileName;
    std::string currentContent;
    std::filesystem::file_time_type lastWriteTime;

    void readFileContent();
    void createFileWithContent(const std::string& content);
    bool fileExists() const;
    std::filesystem::file_time_type getFileWriteTime() const;
    void monitorFile();
};

#endif // FILE_MONITOR_H
