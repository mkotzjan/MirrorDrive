TEMPLATE = subdirs
SUBDIRS += MirrorDrive \
    MirrorDriveTest \
    MirrorDriveLib

MirrorDrive.depends = MirrorDriveLib
MirrorDriveTest.depends = MirrorDriveLib
