#include "file_monitor.h"

int main() {
    FileMonitor fileMonitor("virtualspace.txt");
    fileMonitor.startMonitoring();
    return 0;
}