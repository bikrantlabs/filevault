#pragma once
// Define reserved filenames for both Windows and Linux/Unix
#include <set>
#include <string>
#include <vector>
const std::set<std::string> RESERVED_FILENAMES = {
    "CON",  "PRN",  "AUX",  "NUL",  "COM1", "COM2", "COM3", "COM4",
    "COM5", "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3",
    "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", ".",    ".."};
// Define forbidden characters for all OS
const std::vector<char> FORBIDDEN_CHARS = {'/',  '<', '>', ':', '"',
                                           '\\', '|', '?', '*'};
