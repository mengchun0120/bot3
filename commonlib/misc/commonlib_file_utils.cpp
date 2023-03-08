#include <sstream>
#include <memory>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>

namespace mcdane {
namespace commonlib {

#ifdef __ANDROID__
bool readTextFromAssets(std::string &str,
                        AAssetManager *assetManager,
                        const std::string &fileName)
{
    AAsset* asset = AAssetManager_open(assetManager,
                                       fileName.c_str(),
                                       AASSET_MODE_BUFFER);
    if (!asset)
    {
        LOG_ERROR << "Failed to open assets " << fileName << LOG_END;
        return false;
    }

    off_t len = AAsset_getLength(asset);
    std::unique_ptr<char> buffer(new char[len]);

    AAsset_read(asset, buffer.get(), len);
    str.assign(buffer.get(), len);

    return true;
}
#endif

std::string getFileSeparator()
{
#ifdef _WIN32
    return "\\";
#elif __linux__
    return "/";
#endif
}

std::string readTextFile(const std::string &fileName)
{
    std::ifstream in(fileName);

    if (!in)
    {
        THROW_EXCEPT(FileException, "Failed to open file " + fileName);
    }

    std::stringstream ss;
    ss << in.rdbuf();

    if (in.bad())
    {
        THROW_EXCEPT(FileException, "Failed to read file " + fileName);
    }

    return ss.str();
}

std::string constructPath(std::initializer_list<std::string> pathParts)
{
    return constructPath(std::vector<std::string>(pathParts));
}

std::string constructPath(const std::string &dir,
                          const std::vector<std::string> &path)
{
    std::vector<std::string> tmpPath;
    tmpPath.push_back(dir);
    tmpPath.insert(tmpPath.end(), path.begin(), path.end());
    return constructPath(tmpPath);
}

std::string constructPath(const std::vector<std::string> &path)
{
    if (path.size() == 0) {
        return "";
    }

    std::ostringstream oss;
    std::string separator = getFileSeparator();
    bool empty = true;

    for (auto it = path.begin(); it != path.end(); ++it) {
        if (it->empty())
        {
            continue;
        }

        if (!empty)
        {
            oss << separator;
        }

        oss << *it;
        empty = false;
    }

    return oss.str();
}

} // end of namespace commonlib
} // end of namespace mcdane
