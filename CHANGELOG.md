# master

* upgrade Android project files
* update CI script
* impl lib's header can now be exported
* optimize external ZFModule build logic and script
* reduce recursive header include to improve compile time

# 0.1.0 (20180218)

* first commit
* main platforms and issues/TODOs
    * ZFProjCreator
        * convenient only for creating new projects,
          no future plan on modifying or migrating existing projects
    * iOS
        * Cocoapods : should work perfectly now, one step to use, no annoying config
        * XCode : work but still annoying to setup C++ library envs
    * Android
        * Android Studio : work but still annoying to setup C++ library envs
    * Qt
        * QtCreator : work but still annoying to setup C++ library envs

