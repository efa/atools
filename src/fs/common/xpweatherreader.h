/*****************************************************************************
* Copyright 2015-2017 Alexander Barthel albar965@mailbox.org
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef ATOOLS_XPWEATHERREADER_H
#define ATOOLS_XPWEATHERREADER_H

#include "fs/sc/simconnecttypes.h"

#include <QDateTime>
#include <QHash>
#include <QObject>
#include <QSet>
#include <functional>

class QFileSystemWatcher;

namespace atools {
namespace fs {
namespace common {

/*
 * Reads the X-Plane METAR.rwx the watches the file for changes.
 */
class XpWeatherReader
  : public QObject
{
  Q_OBJECT

public:
  explicit XpWeatherReader(QObject *parent);
  virtual ~XpWeatherReader();

  /* Get METAR for airport ICAO or empty string if file or airport is not available */
  QString getMetar(const QString& ident);

  /* Get all ICAO codes that have a weather station */
  QSet<QString> getMetarAirportIdents() const
  {
    return metars.keys().toSet();
  }

  /* Read METAR.rwx and watch the file if needed */
  void readWeatherFile(const QString& file);

  /* Remove METARs and stop watching the file */
  void clear();

  /* Get station and/or nearest METAR */
  atools::fs::sc::MetarResult getXplaneMetar(const QString& station, const atools::geo::Pos& pos);

  /* Set to a function that returns the coordinates for an airport ident. Needed to find the nearest. */
  void setFetchAirportCoords(const std::function<atools::geo::Pos(const QString&)>& value);

signals:
  void weatherUpdated();

private:
  void read();
  void deleteFsWatcher();
  void createFsWatcher();
  void pathChanged(const QString& path);
  void buildXplaneAirportIndex();

  /* Simple index to allow a full search for nearest */
  typedef std::pair<atools::geo::Pos, QString> XpCoordIdxEntryType;
  QVector<XpCoordIdxEntryType> xpAirportCoordinates;

  std::function<atools::geo::Pos(const QString&)> fetchAirportCoords;
  QHash<QString, QString> metars;
  QString weatherFile;
  QDateTime weatherFileTimestamp;
  QFileSystemWatcher *fsWatcher = nullptr;

};

} // namespace common
} // namespace fs
} // namespace atools

#endif // ATOOLS_XPWEATHERREADER_H
