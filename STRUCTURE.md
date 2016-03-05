# Structure of the library

The library is strctured in several classes, the three most simple classes are:
* *Constants.vala* : Contains some constant values
* *Printer.vala* : Has some utility functions to print messages
* *App.vala* : Contains the details of an application (name, icon path, etc.) obtained from its .desktop file.

The other classes are:
* *ApplicationHandler.vala* : Retrieve the .desktop files and create a list of applications (App objects).
* *IconManager.vala* : Tries to find the icon for the current theme, if it fails it will search inside the folders of the other themes.
* *IconTheme.vala* : Enumerates all the directories of the specified theme.
* *IconDirectory.vala* : Analyzes all the icons inside a directory.