TEMPLATE = subdirs

SUBDIRS += \
    calc-hook-process \
    main
    
main.file = main/calc-inject.pro

CONFIG += ordered
