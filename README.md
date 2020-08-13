# ch-merger
Tool for merging Clone Hero scores from different savefiles.

Features:
* Merging scores, FC and percentage separately
* Summing play count
* Support for multiple files

## How to use
1. Open Command Prompt (Windows) or Terminal (Linux)
2. Navigate to `ch-merger`'s folder using command `cd "[path to folder]"`
3. Type `ch-merger.exe` (Windows) or `./ch-merger` (Linux), followed by space-separated paths to `scores.bin`
4. If there were no errors, the program should create a file called `scores_merged.bin` - replace original `scores.bin` with this file

## Where to find `scores.bin`
* Windows: `C:\Users\[user name]\AppData\LocalLow\srylain Inc_\Clone Hero`
* Linux: `/home/[user name]/.config/unity3d/srylain Inc_/Clone Hero`
