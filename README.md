# SleiTec-cocos2dx-playground-
Simple fun examples/elements for cocos2d-x.


Feel free to suggest optimizations, corrections, ask and more.
I won't be putting up whole cocos2d-x projects only working code snippets + feature presentation.


FFilesystem

I've added a simplified C++17 std::filesystem version, which I'm currently using for my cocos2d-x
project.

I primarily use it to check if paths exist which is easier to use than anything else.

The main reason for it's existence is that std::filesystem was still not added to XCode 10.x
therefore it uses std::filesystem internally for all other platforms and platform
specific stuff for osx only.

Currently only supports filesystem::path and its operations
IsRegularFile, IsDirectory and GetCurrentWorkingDirectory, CreateDirectory I might add
additional functionality to it if necessary until apple supports <filesystem> themself.
  
Seems like the current Android NDK also doesn't support <filesystem>.

Intersting additional features would tmp OS path.
