Contributing to Minecraft Server Tools
======================================

Standards Followed
------------------

This project follows the Linux Coding Style. Please read CODINGSTYLE for
details. Pull requests failing to follow these guidelines *will* be denied.

This project follows Semantic Versioning 2.0.0. Please read SEMVER.md for
details.

Pull Requests
-------------

Before submitting a pull request, make sure that the project still builds
successfully and does not break previously working code. Obviously untested code
*will* be denied.

If you implement a feature, please be sure to comment in your pull request about
what feature you implemented and summarizing the strengths and weaknesses of
your approach. If the feature you implemented isn't already listed as a goal in
README.md, explain why you think your feature should be added. If it implements
a requested feature on the Issue Tracker, also include "Implements x" where x is
the issue id. It is not neccessary for a feature request to be approved or even
exist on the Issue Tracker before submitting a pull request for it.

If you change existing code, and the change is not bug fix, please be sure to 
comment in your pull request why you feel that change was needed, or what 
benefits it provides.

If your change fixes a bug that is not open on the Issue Tracker, open a bug
report on the Issue Tracker before submitting your pull request. It is not
required, but it would be appreciated if you comment on your issue with the
id of your pull request after submitting it.

If your change fixes an open issue in the Issue Tracker, include in the request
"Fixes x" where x is the issue id. If the fix is non-trivial, include a summary
of how it fixes the issue.

Essentially, this all boils down to "You need to convince me that your changes
should be merged."

Branches Accepting Pull Requests:

* devel


Bug Reports
-----------

Before submitting a bug report, search in both open and closed issues for your
or similar issues, as your issue may already be known or even fixed.

When submitting a report, use a short, descriptive title. Generic titles will
make it harder for others to find your report if they're experiencing the same
problem, which will likely cause duplicate entries.

Describe your problem with as much detail as possible, and provide log files
and console output whenever possible. If the tool you're using has a GUI,
screenshots and/or videos of the bug occuring are not required, but would be
appreciated; as they are considered part of "console output".

Details given shall include which tool(s) you're experiencing the problem with
and its version, along with the version of *minecraftd*. If applicable, these
details should also include the version(s) of the Minecraft Server run by the
affected instance(s), whether or not the affected instances are modded or are
a mix of modded and vanilla, and the full version(s) of MinecraftForge and/or
the names and versions of the Mod Packs used in modded instances that are
affected.
