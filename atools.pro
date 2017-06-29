#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T13:16:57
#
#-------------------------------------------------

QT       += sql xml core widgets network
QT       -= gui

CONFIG += c++11

INCLUDEPATH += $$PWD/src

unix {
  DEFINES += GIT_REVISION_ATOOLS='\\"$$system(git rev-parse --short HEAD)\\"'

  # Enable to allow scenery database loading on Linux or macOS
  #DEFINES+=DEBUG_FS_PATHS
}

win32 {
  DEFINES += GIT_REVISION_ATOOLS='\\"$$system('C:\\Git\\bin\\git' rev-parse --short HEAD)\\"'
  DEFINES += _USE_MATH_DEFINES
  DEFINES += NOMINMAX

  SIMCONNECT="C:\Program Files (x86)\Microsoft Games\Microsoft Flight Simulator X SDK"
  INCLUDEPATH += "C:\Program Files (x86)\Microsoft Games\Microsoft Flight Simulator X SDK\SDK\Core Utilities Kit\SimConnect SDK\inc"
  LIBS += "C:\Program Files (x86)\Microsoft Games\Microsoft Flight Simulator X SDK\SDK\Core Utilities Kit\SimConnect SDK\lib\SimConnect.lib"
}

TARGET = atools
TEMPLATE = lib
CONFIG += staticlib

HEADERS += src/atools.h \
    src/exception.h \
    src/fs/ap/airportloader.h \
    src/fs/bgl/ap/airport.h \
    src/fs/bgl/ap/approach.h \
    src/fs/bgl/ap/approachleg.h \
    src/fs/bgl/ap/approachtypes.h \
    src/fs/bgl/ap/apron2.h \
    src/fs/bgl/ap/apron.h \
    src/fs/bgl/ap/com.h \
    src/fs/bgl/ap/del/deleteairport.h \
    src/fs/bgl/ap/del/deletecom.h \
    src/fs/bgl/ap/del/deleterunway.h \
    src/fs/bgl/ap/del/deletestart.h \
    src/fs/bgl/ap/fence.h \
    src/fs/bgl/ap/helipad.h \
    src/fs/bgl/ap/jetway.h \
    src/fs/bgl/ap/parking.h \
    src/fs/bgl/ap/rw/runwayapplights.h \
    src/fs/bgl/ap/rw/runwayend.h \
    src/fs/bgl/ap/rw/runway.h \
    src/fs/bgl/ap/rw/runwayvasi.h \
    src/fs/bgl/ap/start.h \
    src/fs/bgl/ap/taxipath.h \
    src/fs/bgl/ap/taxipoint.h \
    src/fs/bgl/ap/transition.h \
    src/fs/bgl/bglbase.h \
    src/fs/bgl/bglfile.h \
    src/fs/bgl/bglposition.h \
    src/fs/bgl/boundary.h \
    src/fs/bgl/converter.h \
    src/fs/bgl/header.h \
    src/fs/bgl/nav/dme.h \
    src/fs/bgl/nav/glideslope.h \
    src/fs/bgl/nav/ils.h \
    src/fs/bgl/nav/ilsvor.h \
    src/fs/bgl/nav/localizer.h \
    src/fs/bgl/nav/marker.h \
    src/fs/bgl/nav/navbase.h \
    src/fs/bgl/nav/ndb.h \
    src/fs/bgl/nav/vor.h \
    src/fs/bgl/nav/waypoint.h \
    src/fs/bgl/nl/namelistentry.h \
    src/fs/bgl/nl/namelist.h \
    src/fs/bgl/record.h \
    src/fs/bgl/recordtypes.h \
    src/fs/bgl/section.h \
    src/fs/bgl/sectiontype.h \
    src/fs/bgl/subsection.h \
    src/fs/bgl/util.h \
    src/fs/db/airportindex.h \
    src/fs/db/ap/airportwriter.h \
    src/fs/db/ap/approachlegwriter.h \
    src/fs/db/ap/approachwriter.h \
    src/fs/db/ap/apronlightwriter.h \
    src/fs/db/ap/apronwriter.h \
    src/fs/db/ap/comwriter.h \
    src/fs/db/ap/deleteairportwriter.h \
    src/fs/db/ap/deleteprocessor.h \
    src/fs/db/ap/fencewriter.h \
    src/fs/db/ap/helipadwriter.h \
    src/fs/db/ap/legbasewriter.h \
    src/fs/db/ap/parkingwriter.h \
    src/fs/db/ap/rw/runwayendwriter.h \
    src/fs/db/ap/rw/runwaywriter.h \
    src/fs/db/ap/startwriter.h \
    src/fs/db/ap/taxipathwriter.h \
    src/fs/db/ap/transitionlegwriter.h \
    src/fs/db/ap/transitionwriter.h \
    src/fs/db/datawriter.h \
    src/fs/db/meta/bglfilewriter.h \
    src/fs/db/meta/sceneryareawriter.h \
    src/fs/db/nav/ilswriter.h \
    src/fs/db/nav/markerwriter.h \
    src/fs/db/nav/ndbwriter.h \
    src/fs/db/nav/vorwriter.h \
    src/fs/db/nav/waypointwriter.h \
    src/fs/db/runwayindex.h \
    src/fs/db/writerbasebasic.h \
    src/fs/db/writerbase.h \
    src/fs/fspaths.h \
    src/fs/lb/logbookentryfilter.h \
    src/fs/lb/logbookentry.h \
    src/fs/lb/logbook.h \
    src/fs/lb/logbookloader.h \
    src/fs/lb/types.h \
    src/fs/navdatabase.h \
    src/fs/pln/flightplanentry.h \
    src/fs/pln/flightplan.h \
    src/fs/scenery/fileresolver.h \
    src/fs/scenery/sceneryarea.h \
    src/fs/scenery/scenerycfg.h \
    src/geo/calculations.h \
    src/geo/pos.h \
    src/geo/rect.h \
    src/gui/dialog.h \
    src/gui/errorhandler.h \
    src/gui/translator.h \
    src/io/binarystream.h \
    src/io/fileroller.h \
    src/logging/loggingconfig.h \
    src/logging/logginghandler.h \
    src/logging/loggingutil.h \
    src/settings/settings.h \
    src/sql/sqldatabase.h \
    src/sql/sqlexception.h \
    src/sql/sqlexport.h \
    src/sql/sqlquery.h \
    src/sql/sqlscript.h \
    src/sql/sqlutil.h \
    src/gui/widgetstate.h \
    src/gui/helphandler.h \
    src/geo/linestring.h \
    src/gui/actiontextsaver.h \
    src/fs/bgl/nav/airwaywaypoint.h \
    src/fs/db/airwayresolver.h \
    src/fs/db/routeedgewriter.h \
    src/fs/sc/simconnectdata.h \
    src/fs/sc/simconnectreply.h \
    src/fs/sc/simconnecttypes.h \
    src/sql/sqlrecord.h \
    src/util/heap.h \
    src/util/htmlbuilder.h \
    src/gui/filehistoryhandler.h \
    src/gui/mapposhistory.h \
    src/fs/db/databasemeta.h \
    src/zip/zipwriter.h \
    src/zip/zipreader.h \
    src/gui/application.h \
    src/util/version.h \
    src/fs/bgl/boundarysegment.h \
    src/fs/bgl/nav/airwaysegment.h \
    src/fs/bgl/ap/apronedgelight.h \
    src/fs/navdatabaseprogress.h \
    src/fs/navdatabaseoptions.h \
    src/io/inireader.h \
    src/fs/db/nav/boundarywriter.h \
    src/fs/db/nav/airwaysegmentwriter.h \
    src/fs/navdatabaseerrors.h \
    src/fs/sc/simconnecthandler.h \
    src/fs/sc/simconnectdatabase.h \
    src/fs/sc/simconnectdummy.h \
    src/fs/sc/simconnectaircraft.h \
    src/fs/sc/simconnectuseraircraft.h \
    src/fs/sc/datareaderthread.h \
    src/fs/sc/weatherrequest.h \
    src/gui/widgetutil.h \
    src/fs/weather/metar.h \
    src/util/timedcache.h \
    src/fs/weather/metarparser.h \
    src/util/paintercontextsaver.h \
    src/fs/db/ap/airportfilewriter.h \
    src/geo/line.h \
    src/gui/itemviewzoomhandler.h \
    src/gui/griddelegate.h \
    src/dtm/globereader.h \
    src/fs/bgl/nav/tacan.h \
    src/fs/db/nav/tacanwriter.h \
    src/fs/util/tacanfrequencies.h \
    src/fs/util/morsecode.h \
    src/gui/palettesettings.h \
    src/gui/actionstatesaver.h \
    src/win/activationcontext.h \
    src/fs/sc/simconnectapi.h \
    src/fs/scenery/addonpackage.h \
    src/fs/scenery/addoncomponent.h \
    src/fs/progresshandler.h \
    src/fs/xp/xplanedatareader.h \
    src/fs/xp/navwriter.h \
    src/fs/xp/fixwriter.h \
    src/fs/xp/writer.h \
    src/fs/xp/xplaneconstants.h \
    src/fs/xp/airwaywriter.h

SOURCES += src/atools.cpp \
    src/exception.cpp \
    src/fs/ap/airportloader.cpp \
    src/fs/bgl/ap/airport.cpp \
    src/fs/bgl/ap/approach.cpp \
    src/fs/bgl/ap/approachleg.cpp \
    src/fs/bgl/ap/approachtypes.cpp \
    src/fs/bgl/ap/apron2.cpp \
    src/fs/bgl/ap/apron.cpp \
    src/fs/bgl/ap/com.cpp \
    src/fs/bgl/ap/del/deleteairport.cpp \
    src/fs/bgl/ap/del/deletecom.cpp \
    src/fs/bgl/ap/del/deleterunway.cpp \
    src/fs/bgl/ap/del/deletestart.cpp \
    src/fs/bgl/ap/fence.cpp \
    src/fs/bgl/ap/helipad.cpp \
    src/fs/bgl/ap/jetway.cpp \
    src/fs/bgl/ap/parking.cpp \
    src/fs/bgl/ap/rw/runwayapplights.cpp \
    src/fs/bgl/ap/rw/runway.cpp \
    src/fs/bgl/ap/rw/runwayend.cpp \
    src/fs/bgl/ap/rw/runwayvasi.cpp \
    src/fs/bgl/ap/start.cpp \
    src/fs/bgl/ap/taxipath.cpp \
    src/fs/bgl/ap/taxipoint.cpp \
    src/fs/bgl/ap/transition.cpp \
    src/fs/bgl/bglbase.cpp \
    src/fs/bgl/bglfile.cpp \
    src/fs/bgl/bglposition.cpp \
    src/fs/bgl/boundary.cpp \
    src/fs/bgl/converter.cpp \
    src/fs/bgl/header.cpp \
    src/fs/bgl/nav/dme.cpp \
    src/fs/bgl/nav/glideslope.cpp \
    src/fs/bgl/nav/ils.cpp \
    src/fs/bgl/nav/ilsvor.cpp \
    src/fs/bgl/nav/localizer.cpp \
    src/fs/bgl/nav/marker.cpp \
    src/fs/bgl/nav/navbase.cpp \
    src/fs/bgl/nav/ndb.cpp \
    src/fs/bgl/nav/vor.cpp \
    src/fs/bgl/nav/waypoint.cpp \
    src/fs/bgl/nl/namelist.cpp \
    src/fs/bgl/nl/namelistentry.cpp \
    src/fs/bgl/record.cpp \
    src/fs/bgl/recordtypes.cpp \
    src/fs/bgl/section.cpp \
    src/fs/bgl/sectiontype.cpp \
    src/fs/bgl/subsection.cpp \
    src/fs/bgl/util.cpp \
    src/fs/db/airportindex.cpp \
    src/fs/db/ap/airportwriter.cpp \
    src/fs/db/ap/approachlegwriter.cpp \
    src/fs/db/ap/approachwriter.cpp \
    src/fs/db/ap/apronlightwriter.cpp \
    src/fs/db/ap/apronwriter.cpp \
    src/fs/db/ap/comwriter.cpp \
    src/fs/db/ap/deleteairportwriter.cpp \
    src/fs/db/ap/deleteprocessor.cpp \
    src/fs/db/ap/fencewriter.cpp \
    src/fs/db/ap/helipadwriter.cpp \
    src/fs/db/ap/legbasewriter.cpp \
    src/fs/db/ap/parkingwriter.cpp \
    src/fs/db/ap/rw/runwayendwriter.cpp \
    src/fs/db/ap/rw/runwaywriter.cpp \
    src/fs/db/ap/startwriter.cpp \
    src/fs/db/ap/taxipathwriter.cpp \
    src/fs/db/ap/transitionlegwriter.cpp \
    src/fs/db/ap/transitionwriter.cpp \
    src/fs/db/datawriter.cpp \
    src/fs/db/meta/bglfilewriter.cpp \
    src/fs/db/meta/sceneryareawriter.cpp \
    src/fs/db/nav/ilswriter.cpp \
    src/fs/db/nav/markerwriter.cpp \
    src/fs/db/nav/ndbwriter.cpp \
    src/fs/db/nav/vorwriter.cpp \
    src/fs/db/nav/waypointwriter.cpp \
    src/fs/db/runwayindex.cpp \
    src/fs/db/writerbasebasic.cpp \
    src/fs/fspaths.cpp \
    src/fs/lb/logbook.cpp \
    src/fs/lb/logbookentry.cpp \
    src/fs/lb/logbookentryfilter.cpp \
    src/fs/lb/logbookloader.cpp \
    src/fs/lb/types.cpp \
    src/fs/navdatabase.cpp \
    src/fs/pln/flightplan.cpp \
    src/fs/pln/flightplanentry.cpp \
    src/fs/scenery/fileresolver.cpp \
    src/fs/scenery/sceneryarea.cpp \
    src/fs/scenery/scenerycfg.cpp \
    src/geo/calculations.cpp \
    src/geo/pos.cpp \
    src/geo/rect.cpp \
    src/gui/dialog.cpp \
    src/gui/errorhandler.cpp \
    src/gui/translator.cpp \
    src/io/binarystream.cpp \
    src/io/fileroller.cpp \
    src/logging/loggingconfig.cpp \
    src/logging/logginghandler.cpp \
    src/logging/loggingutil.cpp \
    src/settings/settings.cpp \
    src/sql/sqldatabase.cpp \
    src/sql/sqlexception.cpp \
    src/sql/sqlexport.cpp \
    src/sql/sqlquery.cpp \
    src/sql/sqlscript.cpp \
    src/sql/sqlutil.cpp \
    src/gui/widgetstate.cpp \
    src/gui/helphandler.cpp \
    src/geo/linestring.cpp \
    src/gui/actiontextsaver.cpp \
    src/fs/db/airwayresolver.cpp \
    src/fs/db/routeedgewriter.cpp \
    src/fs/sc/simconnectdata.cpp \
    src/fs/sc/simconnectreply.cpp \
    src/sql/sqlrecord.cpp \
    src/util/heap.cpp \
    src/util/htmlbuilder.cpp \
    src/gui/filehistoryhandler.cpp \
    src/gui/mapposhistory.cpp \
    src/fs/db/databasemeta.cpp \
    src/zip/zip.cpp \
    src/gui/application.cpp \
    src/util/version.cpp \
    src/fs/bgl/boundarysegment.cpp \
    src/fs/bgl/nav/airwaywaypoint.cpp \
    src/fs/bgl/ap/apronedgelight.cpp \
    src/fs/navdatabaseprogress.cpp \
    src/fs/navdatabaseoptions.cpp \
    src/io/inireader.cpp \
    src/fs/db/nav/boundarywriter.cpp \
    src/fs/db/nav/airwaysegmentwriter.cpp \
    src/fs/navdatabaseerrors.cpp \
    src/fs/sc/simconnecthandler.cpp \
    src/fs/sc/simconnectdatabase.cpp \
    src/fs/sc/simconnectdummy.cpp \
    src/fs/sc/simconnectaircraft.cpp \
    src/fs/sc/simconnectuseraircraft.cpp \
    src/fs/sc/datareaderthread.cpp \
    src/fs/sc/weatherrequest.cpp \
    src/gui/widgetutil.cpp \
    src/fs/weather/metar.cpp \
    src/util/timedcache.cpp \
    src/fs/weather/metarparser.cpp \
    src/fs/bgl/nav/airwaysegment.cpp \
    src/util/paintercontextsaver.cpp \
    src/fs/db/ap/airportfilewriter.cpp \
    src/geo/line.cpp \
    src/gui/itemviewzoomhandler.cpp \
    src/gui/griddelegate.cpp \
    src/dtm/globereader.cpp \
    src/fs/bgl/nav/tacan.cpp \
    src/fs/db/nav/tacanwriter.cpp \
    src/fs/util/tacanfrequencies.cpp \
    src/fs/util/morsecode.cpp \
    src/gui/palettesettings.cpp \
    src/gui/actionstatesaver.cpp \
    src/win/activationcontext.cpp \
    src/fs/sc/simconnectapi.cpp \
    src/fs/scenery/addonpackage.cpp \
    src/fs/scenery/addoncomponent.cpp \
    src/fs/progresshandler.cpp \
    src/fs/xp/xplanedatareader.cpp \
    src/fs/xp/navwriter.cpp \
    src/fs/xp/fixwriter.cpp \
    src/fs/xp/writer.cpp \
    src/fs/xp/xplaneconstants.cpp \
    src/fs/xp/airwaywriter.cpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    LICENSE.txt \
    README.txt \
    uncrustify.cfg \
    CHANGELOG.txt \
    BUILD.txt \
    resources/sql/fs/db/README.txt

RESOURCES += \
    atools.qrc
