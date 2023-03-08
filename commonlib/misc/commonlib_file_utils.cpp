#include <sstream>
#include <memory>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_file_utils.h>

namespace mcdane {
namespace commonlib {

#ifdef __ANDROID__
std::string readTextFromAssets(AAssetManager *assetManager, const std::string &fileName)
{
    AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_BUFFER);
    off_t len = AAsset_getLength(asset);
    LOG_INFO << "len=" << len << LOG_END;
    std::unique_ptr<char> buffer(new char[len]);
    AAsset_read(asset, buffer.get(), len);
    return std::string(buffer.get(), len);
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
    if (pathParts.size() == 0) {
        return "";
    }

    std::ostringstream oss;
    std::string separator = getFileSeparator();
    auto it = pathParts.begin();

    oss << *it;
    for (++it; it != pathParts.end(); ++it) {
        oss << separator << *it;
    }

    return oss.str();
}

std::string constructPath(const std::string& dir,
                          const std::vector<std::string>& path)
{
    std::ostringstream oss;
    std::string separator = getFileSeparator();

    oss << dir;
    for (auto it = path.cbegin(); it != path.cend(); ++it)
    {
        oss << separator << *it;
    }

    return oss.str();
}


} // end of namespace commonlib
} // end of namespace mcdane

