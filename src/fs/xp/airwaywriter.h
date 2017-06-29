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

#ifndef ATOOLS_FS_XP_AWYWRITER_H
#define ATOOLS_FS_XP_AWYWRITER_H

#include "fs/xp/writer.h"

namespace atools {

namespace sql {
class SqlDatabase;
class SqlQuery;
}

namespace fs {
namespace xp {

class AirwayWriter :
  public atools::fs::xp::Writer
{
public:
  AirwayWriter(atools::sql::SqlDatabase& sqlDb);
  virtual ~AirwayWriter();

  virtual void write(const QStringList& line, int curFileId);

private:
  void initQueries();
  void deInitQueries();

  int curAirwayId = 0;
  atools::sql::SqlQuery *insertAirwayQuery = nullptr;

};

} // namespace xp
} // namespace fs
} // namespace atools

#endif // ATOOLS_FS_XP_AWYWRITER_H
