Simple password manager written in C++

How to use:
passgen command will ask you for service (for what password is), encryption key you want to use for that password (idea is to be same one for every password), your username and will generate 30 characters long random password. Passwords are stored encrypted in directory named PassFold in your HOME directory.
	
	Usage: passgen

passread command will ask you for your encryption key, then it will print your username and copy your password unencrypted to X primary clipboard (can be accessed with mouse middle click or Shift+Insert). After pasting password, it will be removed from X primary clipboard
	
	Usage: passread <service name>

How to install:
There are two ways to install it, globally, on whole system and locally, just for your user

To install globally, run make install as root user.

To install for your user only, run make user-install, and set your PATH variable to $HOME/bin/:$PATH

These two installation can both be done on one system, but it will run the version that is first in $PATH

Dependencies:
	-xclip

All passwords are kept in $HOME/PassFold

Android implementation https://github.com/hwrnr/AndroidPassManager. Password currently aren't synchronised, but you can sync them manually or by some other program by synchronising $HOME/PassFold on your PC and InternalSDCard/Passwords on Android device.
