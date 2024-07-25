# POC-VirtualSpace 🛠️

[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## A Proof of Concept (PoC) for VirtualSpace

Welcome to the PoC for VirtualSpace, a dynamic file monitoring and restoration system. 📂✨

---

## Overview

VirtualSpace is designed to ensure the integrity and availability of your important data. This Proof of Concept (PoC) serves as a demonstration of our main product, VirtualSpace, highlighting our ability to monitor, dynamically update, and restore files.

## Features

- **File Monitoring**: Continuously monitors a specified file for changes and deletions.
- **Dynamic Content Update**: Automatically updates the stored content when the file is modified.
- **File Restoration**: Restores the file with the most recent content if it is deleted.

## How It Works

The core functionality is encapsulated in the `FileMonitor` class, which performs the following tasks:
1. **Initial Setup**: Checks if the target file exists and reads its content.
2. **Monitoring Loop**: Continuously monitors the file:
   - If the file is deleted, it restores it with the last known content.
   - If the file is modified, it updates the stored content to reflect the changes.

## Playing Around with It 🧪

Feel free to edit `virtualspace.txt` with any content you like. The program will:
- Detect changes and update its internal record.
- Restore the file with the latest content if it's deleted.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Thank you for checking out our PoC for VirtualSpace! We look forward to your feedback and contributions. 🚀
