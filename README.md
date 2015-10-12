
# Autodesk® Maya 2016 - Developer Kit.

Autodesk® Maya® provides a rich and powerful API that can be used to automate repetitive tasks, 
and to extend the core functionality of Maya. This functionality includes customization of 3D 
modeling, animation, visual effects, rendering, and many other areas. C++, Python, and .NET are 
supported. The Software Development Kit (SDK) provides extensive functionality and provides code 
samples and documentation to help get you started developing with the Maya API.


## Download the latest version from Autodesk Exchange
The current release fo the devkit is the version released at the time of the Maya 2016 Service Pack 1.
It contains some new API added for Core Profile which doesn’t break the Maya API compatibility, and 
additional VP2 and Core Profile examples.


Maya 2016+
* [Linux](https://apps.exchange.autodesk.com/MAYA/en/Detail/Index?id=appstore.exchange.autodesk.com%3aautodeskmaya2016developerkit_linux%3aen)
* [OSX](https://apps.exchange.autodesk.com/MAYA/en/Detail/Index?id=appstore.exchange.autodesk.com:autodeskmaya2016developerkit_macos:en)
* [Windows](https://apps.exchange.autodesk.com/MAYA/en/Detail/Index?id=appstore.exchange.autodesk.com:autodeskmaya2016developerkit_windows64:en)


#### Boost for Alembic

The Boost compressed files for Alembic is not posted on this repo due to its size being over the 
GitHub limit of 100Mb. However you can download Boost 1.55.0 from [here](http://www.boost.org/users/history/version_1_55_0.html).

The boost.zip file was located in devkit/Alembic/include/AlembicPrivate


### Understands which devkit for which release
You can use any devkit version for writing plug-in for any version of Maya of the same Major release, 
i.e. any 2016 devkit version for any Maya 2016 release.
However, if you are using an older devkit release than the Maya version you are targeting, make sure to 
not use any new introduced API which does not exist in older Maya release. Otherwise, the plug-in will
not work.


## Past Releases

#### Maya 2016
You can still get the devkit released at the time Maya 2016 was release [here](https://github.com/autodesk-adn/Maya-devkit/releases/tag/2016)

  * Boost for Alembic
    The Boost compressed files for Alembic is not posted on this repo due to its size being over the 
    GitHub limit of 100Mb. However you can download Boost 1.55.0 from [here](http://www.boost.org/users/history/version_1_55_0.html).
    The boost.zip file was located in devkit/Alembic/include/AlembicPrivate


#### Before Maya 2016
Older Devkit versions were released with the Maya distributions.


--------

## License

This devkits are licensed under the terms of the [AUTODESK LICENSE AND SERVICES AGREEMENT](Autodesk EULA.pdf).

Licensees of Autodesk® Maya® may license this Maya development kit as part of the Licensed Materials as defined in and pursuant
to the attached License and Services Agreement (“LSA”).  If you are not a licensee of Autodesk® Maya® you may not license or use
this software.  Note that Section 1.11 of the LSA permits you to use API Information and development materials for your own internal 
development purposes, and Section 10.2.1 of the LSA permits you to reproduce and distribute certain defined Redistributable 
Components together with your application provided that you strictly comply with the restrictions set forth in Section 10.2.1(a)-(i).

