
to install:
Linux and generic 
just extract the archive into "/usr/share/celestia " or "/usr/local/share/celestia"
or copy ( extras)it to where you installed celestia "/usr/share/celestia " or "/usr/local/share/celestia"

Windows ( XP,Vista,Windows 7 )--
-----------------------------------
 same as above but C:\\Program Files\celestia  or C:\\Celestia 
for vista and windows 7 I would suggest installing Celestia in " C:\\Celestia 
and install as Administrator 
----------------------------------
Mac 
extract to or "copy/paste" 
/Users/<username>/Library/Application Support/CelestiaResources
or 
/Applications/Celestia.app/Contents/Resources/CelestiaResources/

this file unzips to 
.
|-- extras
|   `-- JohnVV
|       |-- MarsNormal.ssc
|       `-- textures
|           |-- hires
|           |   `-- MarsNormal.png
|           |-- lores
|           |   `-- MarsNormal.png
|           `-- medres
|               `-- MarsNormal.png
`-- ReadMe.2k.4k.8k.MarsNormal.txt

----- INSTALL NOTES -----

if using my 2k,4k,8k mars add on you can uncomment the line in the Mars.ssc 
   /*   NormalMap "MarsNormal.png"   */ 
and use that ssc instead on the MarsNormal.ssc in this add on 

or not - it's up to you 
----------------------------


the Original Topo data is from MOLA  meg128 (128/ppd  )

http://pds-geosciences.wustl.edu/missions/mgs/megdr.html

the 16  megt tiles were then processed using ISIS3 and G'Mic 
http://gmic.sourceforge.net/gimp.shtml ( the replacement for "GREYCstoration')
to remove most of the "stripping " caused by the spline fill in the original data .

