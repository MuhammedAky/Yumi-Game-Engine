#include <yumi/file.hpp>

namespace yumi {
    std::string ReadFile(const char* file_path) {
        std::ifstream file(file_path, std::ios::binary);
        std::string contents;
        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        file.close();
        return contents;
    }
}