#configuration
CONFIG +=  shared qpa no_mocdepend release qt_framework
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = x86_64
} else {
    QT_ARCH = x86_64
    QMAKE_DEFAULT_LIBDIRS = /lib /usr/lib
    QMAKE_DEFAULT_INCDIRS = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1 /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/7.3.0/include /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/usr/include
}
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config no-pkg-config c++11 c++14 c++1z accessibility opengl shared qpa reduce_exports getaddrinfo ipv6ifname getifaddrs png freetype harfbuzz system-zlib nis cups iconv ssl securetransport corewlan concurrent audio-backend release qt_framework

#versioning
QT_VERSION = 5.6.1
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 6
QT_PATCH_VERSION = 1

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

QT_EDITION = OpenSource

QT_COMPILER_STDCXX = 199711
QT_APPLE_CLANG_MAJOR_VERSION = 7
QT_APPLE_CLANG_MINOR_VERSION = 3
