#pragma once

//only dev machines need filesystem
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    #include <filesystem>
#endif

/**
 * FFilesystem was created, because C++17 <filesystem> is not available on XCode 10
 * and we don't want to add boost only for <filesystem> 
 */

namespace FFilesystem
{
    struct Path
    {
        Path(const std::string& path)
            :path_(path)
        {
        }
        
        Path(const char* path)
        :path_(path)
        {
        }

        const Path& operator/(const Path& path)
        {
            path_ += "/";
            path_ += path.String();
            return *this;
        }

        const Path& operator/(const std::string& path)
        {
            path_ += "/";
            path_ += path;
            return *this;
        }
        
        const Path& operator/(const char* path)
        {
            path_ += "/";
            path_ += path;
            return *this;
        }
        

        const std::string& String() const
        {
            return path_;
        }

    private:
        std::string path_;
    };

    Path CurrentPath()
    {
        //Android and ios not tested
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        //readlink
            //dirname
        char cwd[FILENAME_MAX];
        if(!getcwd(cwd, FILENAME_MAX))
        {
            std::cerr << "Failed to get current working directory" << std::endl;
            return "";
        }
        
        return cwd;
#else
        return std::filesystem::current_path().string().c_str();
#endif
    }

    bool IsDirectory(const Path& path)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        struct stat st;
        return stat(path.String().c_str(), &st) == 0 ? S_ISDIR(st.st_mode) : false;
#else
        return std::filesystem::is_directory(std::filesystem::path(path.String()));
#endif
    }

    bool IsRegularFile(const Path& path)
    {
        //ios and android is untestet
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        struct stat st;
        return stat(path.String().c_str(), &st) == 0 ? S_ISREG(st.st_mode) : false;
#else
        return std::filesystem::is_regular_file(std::filesystem::path(path.String()));
#endif
    }
};

