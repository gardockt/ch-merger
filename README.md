# ch-merger
[Download (Linux/Windows)](https://github.com/gardockt/ch-merger/releases)  
[Download (Mac - unofficial build)](https://github.com/gardockt/ch-merger/files/5179884/ch-merger.gz)

Tool for merging Clone Hero scores from different savefiles.

Features:
* Merging scores, FC and percentage separately
* Adding up play count
* Support for multiple files

## How to use
1. Open Command Prompt (Windows) or Terminal (Linux/Mac)
2. Navigate to `ch-merger`'s folder using command `cd "[path to folder]"`
3. Run the program followed by space-separated paths to savefiles (for example `./ch-merger scores.bin.1 scores.bin.2`)
4. If there were no errors, the program should create a file called `scores_merged.bin` - replace original `scores.bin` with this file

## Where to find `scores.bin`
* Windows: `C:\Users\[username]\AppData\LocalLow\srylain Inc_\Clone Hero`
* Linux: `~/.config/unity3d/srylain Inc_/Clone Hero`
* Mac: `~/Library/Application Support/com.srylain.CloneHero`
