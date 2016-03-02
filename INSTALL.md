Installation Instructions
=========================

GTK+ 3
------

To install RapidLauncher you will need to have GTK+ 3 and its Vala
bindings installed.

On Ubuntu (12.04) these packages are called:

* ``gir1.2-gtk-3.0``
* ``libgtk-3-dev``




Vala
----

Since *RapidLauncher* is written in Vala you also need the Vala compiler
(valac) and it's dependencies.

You will need at least version 0.16 to compile successfully, but the newer
the better.

On Ubuntu (12.04) theses packages are called:

* ``valac-0.16``
* ``valac-0.16-vapi``
* ``libvala-0.16-0``

If you use Ubuntu you can add a Vala ppa to always get the lastest
Vala compiler:

``ppa:vala-team/ppa``



Building (easy)
---------------

When you have all dependencies installed simply run the install.sh script,
which will interactively ask you for your requirements, set the environment
variables accordingly and run *make*.

``$ sudo ./install.sh``  
``$ sudo make install``

Building
--------

The building process respects several environment parameters.  
You can set *RCKTL_BUILD_DEBUG* to create a debug build or
*RCKTL_BUILD_RELEASE* to create an performance optimized build.  

If you use Ubuntu Unity (the default Ubuntu Desktop Environment, not something
like *XFCE*/*KDE*/*LXDE*) you will need the *appindicator* library in order
to display an icon in the message area.  
You will also have to set the *RCKTL_FEATURE_APPINDICATOR* environment
variable to use *appindicator*.  
*RapidLauncher* also supports threaded builds. You can tell make to build
with multiple threads with *-j* tag.
(Or set it in *MAKEFLAGS* environment variable)  
Make supports setting the *DESTDIR* environment variable to specify a
(absolut) path that gets prepended to every installed file.

Example:

``$ export RCKTL_BUILD_DEBUG=``  
``$ export RCKTL_BUILD_RELEASE=1``  
``$ export RCKTL_FEATURE_APPINDICATOR=``  
``$ make -j4``  
``$ make install``  


Usage
-----

Once you have installed RapidLauncher you can start it with the
'rapidlauncher' command or by using the included .desktop file.

You probably want to bind the ``rapidlauncher`` command to a keyboard
shortcut.

