#pragma once
// Define reserved filenames for both Windows and Linux/Unix
#include <set>
#include <string>
#include <vector>

#define ID_LENGTH 6
const std::string CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const std::string ROOT_CONFIG_PATH = "../config.json";
const std::set<std::string> RESERVED_FILENAMES = {
    "CON",  "PRN",  "AUX",  "NUL",  "COM1", "COM2", "COM3", "COM4",
    "COM5", "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3",
    "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", ".",    ".."};
// Define forbidden characters for all OS
const std::vector<char> FORBIDDEN_CHARS = {'/',  '<', '>', ':', '"',
                                           '\\', '|', '?', '*'};
const std::vector<std::string> imageType = {"png", "jpeg", "jpg"};
const std::vector<std::string> videoType = {"mkv", "mp4", "avi", "mov"};
const std::vector<std::string> documentType = {"pdf", "doc", "docx", "ppt",
                                               "pptx"};
const std::vector<std::string> codeType = {"cpp", "h", "java", "py", "js"};
const std::vector<std::string> adobeType = {"psd", "ai", "indd"};
const std::vector<std::string> audioType = {"mp3", "wav", "flac", "aac"};
const std::vector<std::string> textType = {"txt", "md", "rtf"};