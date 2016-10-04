# Overview #

A simple C/C++ malware scanner for Windows that I made a long time ago for my college assignment. It was originally created with Visual Studio 2008, but I have upgraded the project with Visual Studio 2015. The GUI part was created with MFC. The archive operation was created using [zlib](http://www.zlib.net/) and [minizip](http://www.winimage.com/zLibDll/minizip.html).

# Screenshots #

Splash screen with background memory scanning

![flatav_splash2.png](http://i62.tinypic.com/30njd5v.jpg)

Main Window

![flatav_maindlg.png](http://i63.tinypic.com/65ygyd.jpg)

# Features #

* A malware scanner with graphical user interface
* Scan files and folders
* Scan archive files (only ZIP is supported)
* Scan memory process and start-up items on application start
* If malware is caught, options are given for user to delete or move the malware
* Separate tool to build malware signature database (whitelist is supported)

# Missing features #

* No real-time protection
* No automatic update feature
* Limited archive type scanning


# Build #

### Requirements ###

* Visual Studio 2015 with MFC library
* [ShellFolderTree](https://github.com/s101d1/ShellFolderTree) component.

### How to Build ###

* Open the **FlatAntivirus.sln**.
* There are 3 projects inside:
    * FlatAVGUI: main GUI application. It depends on the libflatav project.
    * FVDTool: tool for creating signature database. It depends on the libflatav project.
    * libflatav: AV core engine in form of DLL file.
* Set FlatAVGUI as start-up project.
* Select the build configuration: Debug/DebugU/Release/ReleaseU (the one with suffix "U" is unicode build).
* Build the solution.
* If libflatav build is success, **libflatav.dll** file will be created in output folder Debug/DebugU/Release/ReleaseU (depends on the configuration) and copied to respective output folder of FVDTool and FlatAVGUI, and FlatAV_Setup folder.
* If FlatAVGUI build is success, **FlatAVGUI.exe** will be created in output folder and copied to FlatAV_Setup folder.


# Run #

* Copy **main.fvd** from FlatAVGUI folder to the output folder (it needs to be in same folder with FlatAVGUI.exe, unless you run the FlatAVGUI directly from Visual Studio). If main.fvd doesn't exist, you have to build it with FVDTool (read **Create Signature Database** section).
* Build and register **ShellCtl.dll** from **ShellFolderTree** project. You can put the DLL in any folder as long as the DLL has been registered properly.
* Run the FlatAVGUI.exe.


# Create Signature Database #

* The FlatAV signature database file is main.fvd file.
* The FVD file is assembled from .hdb, .cdb, .xdb, .sdb, .wdb files using FvdTool.
* Those files can be created manually using text editor. Read fvd_note.txt inside the fvd_samples folder to understand the FVD format.
* Copy FvdTool.exe and libflatav.dll into fvd_samples folder.
* Open command prompt on fvd_samples folder and run command: `FvdTool -b`
* It will build and create main.fvd in the same folder.


# Create Installer #

* Inside FlatAV_Setup you will find Inno Setup Script file **FlatAVSetup.iss** and FlatAV subfolder that contains the required files.
* If solution build is success, all required binary files will be copied into FlatAV folder except these files that require manual copy: 
    * **main.fvd**
    * **ShellCtl.dll** from **ShellFolderTree** project
    * **VC++ redist package x86 (vc_redist.x86)**. You can download it from [microsoft site](http://support.microsoft.com/kb/2019667). Make sure you download one that match with your Visual Studio version.
* Open FlatAVSetup.iss with [Inno Setup compiler](http://www.jrsoftware.org/isinfo.php) and modify VC++ redist package part accordingly (function VCRedistNeedsInstall).
* Compile FlatAVSetup.iss.
* If success, **FlatAVsetup.exe** will be created in current folder.
* **Note: make sure you build the solution with Release/ReleaseU configuration.**
