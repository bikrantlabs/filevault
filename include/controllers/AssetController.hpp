#pragma once
#include <string>
#include <vector>
enum FileTypes { IMAGE, TEXT, CODE, ADOBE, DOCUMENTS, VIDEO, AUDIO, OTHER };

typedef struct File {
  std::string id;
  std::string name;
  std::string description;
  int size;
  bool isTrashed;
  FileTypes fileType;
} File;

class AssetController {
public:
  std::vector<File> getFilesByCategory(std::string categoryId);
  File getFile(std::string fileId);
};
