#Minecraft Server Tools

A set of tools for maintaining and interfacing with Minecraft server instances.

###Note
Basic design is not yet complete. Until basic design is complete, public pull requests will be *DISCARDED*.

##Goals/Features

* minecraftd
  * Watchdog daemon
    * Monitor running server instances for problems
	* Notify Administrators and Clients of problems
	* Restart failed instances automatically if applicable
  * Instance management
	* Create, delete, and edit server instances
    * Start/stop/restart individual or multiple instances
	* Stream instance I/O to authenticated connections
	* Each instance runs in a separate thread/process
	* Each instance is sandboxed in a chroot jail or similar
  * Communicates with User Interfaces (UIs) over Unix sockets and TCP/IP
	* Traffic over TCP/IP is encrypted
  * User and Group facilities with permissions system
    * Administration
	  * SuperAdmin (root)
	    * Manages minecraftd itself, users, groups, permissions, all instances, etc. (Unlimited access)
		* Requires machine level access to use (IE: Physical access, SSH terminal, etc.)
		* Machine-level user account must be 'root' or have administrative access (IE: Access through sudo)
		* Should only be used for initial configuration and disaster recovery
	  * Group: Admin
	    * Manage most of minecraftd and all instances
		* root may customize some permissions given to this group
	  * Group: Bot
	    * For automatic/triggered management
	    * Severely limited access to minecraftd, no access to instances' I/O streams
	    * Example: Automatic creation of instances triggered by purchase of a new instance
	  * Custom Groups
	    * Customized groups with customized permissions can be added by members of Admin and by root
		* Allows for customized delegation of responsibilities to fit operating entities' needs.
	  * Administrative users
	    * May be explicitly given or explicitly denied individual permissions
		* Unconfigured permissions are implicitly denied
	* Client
	  * Can only see and manage instances they own
	  * No access to minecraftd itself
	  * May register staff accounts for Client's staff
	  * May create staff groups and assign Client-level permissions as desired to fit Client's needs
	  * Staff accounts, staff groups are stored in the Client's account information directly.
* minecraftctl
  * Console-based User Interface to minecraftd
    * communicates with minecraftd over Unix sockets or TCP/IP
  * One-shot mode to allow single commands to, and scripting of minecraftd
  * Interactive/Shell mode to act as a command shell for minecraftd
* MinecraftWebAdmin
  * Web-based Graphical User Interface to minecraftd
  * Written in HTML5/CSS/jQuery, PHP if necessary
  