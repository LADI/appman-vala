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



Building
---------------

When you have all dependencies installed simply run the install.sh script,
which will interactively ask you for your requirements, set the environment
variables accordingly and run *make*.

``$ make``  
``$ sudo make install``


Usage
-----

Once you have installed RapidLauncher you can start it with the
'rapidlauncher' command or by using the included .desktop file.

You probably want to bind the ``rapidlauncher`` command to a keyboard
shortcut.

