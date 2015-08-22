#Minecraft Server Tools

A set of tools for maintaining and interfacing with Minecraft server instances.

###Goals/Features

Below is a basic list of features. Each module's detailed design will be documented separately in a `docs` sub-directory within it's directory.
These `docs` directories will also contain the manuals (manpages, user-guides, etc).

* minecraftd
  * Watchdog daemon
    * Monitor running server instances for problems
	* Notify Administrators and connected UIs of problems
	* Restart failed instances automatically if applicable
  * Instance management
	* Create, delete, and edit server instances
    * Start/stop/restart individual or multiple instances
	* Stream instance I/O to authenticated connections
	* Each instance runs in a separate thread/process
	* Each instance is sandboxed in a chroot jail or similar
  * May communicate via message queues for local UIs
  * May communicate with local or remote User Interfaces (UIs) over Unix sockets and/or TCP/IP
	* Network traffic shall be encrypted, something akin to SSH's encryption
	* Incoming connections must be authenticated and authorized against a system account before daemon will respond to requests.
* minecraftctl
  * Console-based User Interface to minecraftd
  * One-shot mode to allow single commands to, and scripting of minecraftd
  * Interactive/Shell mode to act as a command shell for minecraftd
  * Invoking user must be root, minecraftd's system account, or member of minecraftd's system group
* MinecraftWebAdmin
  * Web-based Graphical User Interface to minecraftd
  * Written in HTML5/CSS/jQuery/CGI
    * avoid using server-side interpreted languages for performance reasons
  * Provides cetralized management of remote and local minecraftd instances
  * User and Group facilities with permissions system
    * Administration
	  * SuperAdmin (root)
	    * Manages minecraftd itself, users, groups, permissions, all instances, etc. (Unlimited access)
		* Requires machine level access to use (IE: Physical access, SSH terminal, etc.)
		* Machine-level user account must be 'root' or have administrative access (IE: Access through sudo, be in minecraftd's system group)
		* Should only be used for initial configuration and disaster recovery
	  * Group: Admin
	    * Manage and configure MinecraftWebAdmin
	    * Manage most of minecraftd and all instances
		* root may customize some permissions given to this group
	  * Group: Bot
	    * For automatic/triggered management
	    * Severely limited access to minecraftd, no access to instances' I/O streams
	    * Example: Automatic creation of instances and client accounts triggered by purchase of a new instance
	  * Custom Groups
	    * Customized groups with customized permissions can be added by members of Admin and by root
		* Allows for customized delegation of responsibilities to fit operating entities' needs.
	  * Administrative users
	    * May be assigned to groups
	    * May be explicitly given or explicitly denied individual permissions
		* Unconfigured permissions are implicitly denied
		* Explicitly set individual permissions over-ride group permissions
    * Client accounts
      * Can only see and manage instances they own
      * No access to minecraftd itself
      * May register staff accounts for Client's staff
      * May create staff groups and assign Client-level permissions as desired to fit Client's needs
      * Staff accounts, staff groups are stored in the Client's account information directly.

###Building from source

Generally speaking, this is not possible yet...
