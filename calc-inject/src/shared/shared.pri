# set QTBIN
TEMPNAME = $${QMAKE_QMAKE}
QTBIN = $$dirname(TEMPNAME)

win32-msvc* {
    # support windows xp
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
    # generating pdb in release mode
    # QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINGO
    # QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /DEBUG
}

# get platform
L2_PLATFORM=$$(L2_PLATFORM)
isEmpty(TOPIKM_PLATFORM){
    L2_PLATFORM=unknown
    win32 {
        L2_PLATFORM=win32
        win32-g++ {
            L2_PLATFORM=win32-mingw
        }
        win32-msvc2013 {
            L2_PLATFORM=win32-msvc2013
        }
        win32-msvc2015 {
            L2_PLATFORM=win32-msvc2015
        }
    }
    macx {
        L2_PLATFORM=macx
    }
    linux {
        L2_PLATFORM=linux$$QMAKE_HOST.arch
    }
}
# sdk path
L2_SDKPATH=$$DIST_DIR/$${L2_PLATFORM}

# include headers
INCLUDEPATH += $${L2_SDKPATH}/include

# support c++11
CONFIG += c++11

# debug suffix
CONFIG += debug_and_release
CONFIG(debug, debug | release) {
    DESTDIR = $${L2_SDKPATH}/debug/bin
    win32 {
        DEBUG_SUFFIX = d
    }
    macx {
        DEBUG_SUFFIX = _debug
    }
} else {
    DESTDIR = $${L2_SDKPATH}/release/bin
    DEBUG_SUFFIX =
}

# libs
LIBS += -L$$DESTDIR
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}

