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

#include "fs/xp/navwriter.h"

#include "geo/pos.h"
#include "geo/calculations.h"
#include "sql/sqlutil.h"

using atools::sql::SqlQuery;
using atools::sql::SqlUtil;

namespace atools {
namespace fs {
namespace xp {

// 4  36.692211111    3.217516667      131    11030    25    232.655   AG DAAG DA 23 ILS-cat-III
// 6  36.710150000    3.249166667      131    11030    25 300232.655   AG DAAG DA 23 GS
// 12  36.710150000    3.249166667      131    11030    25      0.000   AG DAAG DA HOUARI BOUMEDIENE DME-ILS
enum FieldIndex
{
  ROWCODE = 0,
  LATY = 1,
  LONX = 2,
  ALT = 3,
  FREQ = 4,
  RANGE = 5,
  HDG = 6,
  MAGVAR = HDG,
  IDENT = 7,
  AIRPORT = 8,
  REGION = 9,
  RW = 10,
  NAME = 11
};

NavWriter::NavWriter(atools::sql::SqlDatabase& sqlDb)
  : Writer(sqlDb)
{
  initQueries();
}

atools::fs::xp::NavWriter::~NavWriter()
{
  deInitQueries();
}

void NavWriter::writeVor(const QStringList& line, int curFileId, bool dmeOnly)
{
  int range = line.at(RANGE).toInt();
  QString type;
  QString rangeType;
  if(range < 30)
    rangeType = "T";
  else if(range < 50)
    rangeType = "L";
  else
    rangeType = "H";

  QString suffix = line.last();
  if(suffix == "VOR" || suffix == "DME" || suffix == "VOR-DME" || suffix == "VOR/DME")
    type = rangeType;
  else if(suffix == "VORTAC")
    type = "VT" + rangeType;
  else if(suffix == "TACAN")
    type = "TC";

  bool hasDme = suffix == "DME" || suffix == "VORTAC" || suffix == "VOR-DME" || suffix == "VOR/DME";

  insertVorQuery->bindValue(":vor_id", ++curVorId);
  insertVorQuery->bindValue(":file_id", curFileId);
  insertVorQuery->bindValue(":ident", line.at(IDENT));
  insertVorQuery->bindValue(":name", line.mid(RW, line.size() - 11).join(" "));
  insertVorQuery->bindValue(":region", line.at(REGION));
  insertVorQuery->bindValue(":type", type);
  insertVorQuery->bindValue(":frequency", line.at(FREQ).toInt() * 10);
  insertVorQuery->bindValue(":range", range);
  insertVorQuery->bindValue(":mag_var", line.at(MAGVAR).toFloat());
  insertVorQuery->bindValue(":dme_only", dmeOnly);

  if(hasDme)
  {
    insertVorQuery->bindValue(":dme_altitude", line.at(ALT).toInt());
    insertVorQuery->bindValue(":dme_lonx", line.at(LONX).toFloat());
    insertVorQuery->bindValue(":dme_laty", line.at(LATY).toFloat());
  }
  else
  {
    insertVorQuery->bindValue(":dme_altitude", QVariant(QVariant::Int));
    insertVorQuery->bindValue(":dme_lonx", QVariant(QVariant::Double));
    insertVorQuery->bindValue(":dme_laty", QVariant(QVariant::Double));
  }

  insertVorQuery->bindValue(":altitude", line.at(ALT).toInt());
  insertVorQuery->bindValue(":lonx", line.at(LONX).toFloat());
  insertVorQuery->bindValue(":laty", line.at(LATY).toFloat());

  insertVorQuery->exec();
}

void NavWriter::writeNdb(const QStringList& line, int curFileId)
{
  int range = line.at(RANGE).toInt();

  QString type;
  if(range < 24)
    type = "CP";
  else if(range < 40)
    type = "MH";
  else if(range < 70)
    type = "H";
  else
    type = "HF";

  insertNdbQuery->bindValue(":ndb_id", ++curNdbId);
  insertNdbQuery->bindValue(":file_id", curFileId);
  insertNdbQuery->bindValue(":ident", line.at(IDENT));
  insertNdbQuery->bindValue(":name", line.mid(RW, line.size() - 11).join(" "));
  insertNdbQuery->bindValue(":region", line.at(REGION));
  insertNdbQuery->bindValue(":type", type);
  insertNdbQuery->bindValue(":frequency", line.at(FREQ).toInt() * 100);
  insertNdbQuery->bindValue(":range", range);
  insertNdbQuery->bindValue(":mag_var", 0);
  // TODO airport code insertNdbQuery->bindValue(":ident", line.at(7));
  insertNdbQuery->bindValue(":altitude", line.at(ALT).toInt());
  insertNdbQuery->bindValue(":lonx", line.at(LONX).toFloat());
  insertNdbQuery->bindValue(":laty", line.at(LATY).toFloat());

  insertNdbQuery->exec();
}

void NavWriter::writeMarker(const QStringList& line, int curFileId, RowCode rowCode)
{
  QString type;
  if(rowCode == OM)
    type = "OUTER";
  else if(rowCode == MM)
    type = "MIDDLE";
  else if(rowCode == IM)
    type = "INNER";

  insertMarkerQuery->bindValue(":marker_id", ++curMarkerId);
  insertMarkerQuery->bindValue(":file_id", curFileId);
  insertMarkerQuery->bindValue(":region", line.at(REGION));
  insertMarkerQuery->bindValue(":type", type);
  insertMarkerQuery->bindValue(":heading", line.at(HDG).toFloat());
  insertMarkerQuery->bindValue(":altitude", line.at(ALT).toInt());
  insertMarkerQuery->bindValue(":lonx", line.at(LONX).toFloat());
  insertMarkerQuery->bindValue(":laty", line.at(LATY).toFloat());

  insertMarkerQuery->exec();
}

void NavWriter::finshIls()
{
  if(writingIls)
  {
    insertIlsQuery->exec();
    writingIls = false;
  }
}

void NavWriter::writeIls(const QStringList& line, int curFileId, RowCode rowCode)
{
  Q_UNUSED(curFileId);

  if(rowCode == LOC_ONLY || rowCode == LOC)
  {
    if(writingIls)
      throw atools::Exception("Recursive ILS write");

    insertIlsQuery->bindValue(":ils_id", ++curIlsId);
    insertIlsQuery->bindValue(":frequency", line.at(FREQ).toInt() * 10);
    insertIlsQuery->bindValue(":range", line.at(RANGE).toInt());
    insertIlsQuery->bindValue(":loc_heading", line.at(HDG).toFloat());
    insertIlsQuery->bindValue(":ident", line.at(IDENT));
    insertIlsQuery->bindValue(":loc_airport_ident", line.at(AIRPORT));
    insertIlsQuery->bindValue(":region", line.at(REGION));
    insertIlsQuery->bindValue(":loc_runway_name", line.at(RW));
    insertIlsQuery->bindValue(":name", line.mid(NAME).join(" ").toUpper());

    insertIlsQuery->bindValue(":altitude", line.at(ALT).toInt());
    insertIlsQuery->bindValue(":lonx", line.at(LONX).toFloat());
    insertIlsQuery->bindValue(":laty", line.at(LATY).toFloat());

    insertIlsQuery->bindValue(":mag_var", 0);
    insertIlsQuery->bindValue(":loc_width", FEATHER_WIDTH);
    insertIlsQuery->bindValue(":has_backcourse", 0);

    int length = atools::geo::nmToMeter(FEATHER_LEN_NM);
    atools::geo::Pos pos(line.at(LONX).toFloat(), line.at(LATY).toFloat());
    // Calculate the display of the ILS feather
    float ilsHeading = atools::geo::normalizeCourse(atools::geo::opposedCourseDeg(line.at(HDG).toFloat()));
    atools::geo::Pos p1 = pos.endpoint(length, ilsHeading - FEATHER_WIDTH / 2.f).normalize();
    atools::geo::Pos p2 = pos.endpoint(length, ilsHeading + FEATHER_WIDTH / 2.f).normalize();
    float featherWidth = p1.distanceMeterTo(p2);
    atools::geo::Pos pmid = pos.endpoint(length - featherWidth / 2, ilsHeading).normalize();

    insertIlsQuery->bindValue(":end1_lonx", p1.getLonX());
    insertIlsQuery->bindValue(":end1_laty", p1.getLatY());
    insertIlsQuery->bindValue(":end_mid_lonx", pmid.getLonX());
    insertIlsQuery->bindValue(":end_mid_laty", pmid.getLatY());
    insertIlsQuery->bindValue(":end2_lonx", p2.getLonX());
    insertIlsQuery->bindValue(":end2_laty", p2.getLatY());
  }
  else if(rowCode == GS)
  {
    insertIlsQuery->bindValue(":gs_range", line.at(RANGE).toInt());
    insertIlsQuery->bindValue(":gs_pitch", std::floor((line.at(HDG).toFloat() / 1000.f) / 100.f));
    insertIlsQuery->bindValue(":gs_altitude", line.at(ALT).toInt());
    insertIlsQuery->bindValue(":gs_lonx", line.at(LONX).toFloat());
    insertIlsQuery->bindValue(":gs_laty", line.at(LATY).toFloat());
  }
  else if(rowCode == DME)
  {
    insertIlsQuery->bindValue(":dme_range", line.at(RANGE).toInt());
    insertIlsQuery->bindValue(":dme_altitude", line.at(ALT).toInt());
    insertIlsQuery->bindValue(":dme_lonx", line.at(LONX).toFloat());
    insertIlsQuery->bindValue(":dme_laty", line.at(LATY).toFloat());
  }

  writingIls = true;
}

void NavWriter::write(const QStringList& line, int curFileId)
{
  // lat lon
  // ("28.000708333", "-83.423330556", "KNOST", "ENRT", "K7")

  RowCode rowCode = static_cast<RowCode>(line.at(ROWCODE).toInt());

  // Glideslope records must come later in the file than their associated localizer
  // LTP/FTP records must come later in the file than their associated FPAP
  // Paired DME records must come later in the file than their associated VOR or TACAN
  switch(rowCode)
  {
    // 2 NDB (Non-Directional Beacon) Includes NDB component of Locator Outer Markers (LOM)
    case NDB:
      finshIls();
      writeNdb(line, curFileId);
      break;

    // 3 VOR (including VOR-DME and VORTACs) Includes VORs, VOR-DMEs, TACANs and VORTACs
    case VOR:
      finshIls();
      writeVor(line, curFileId, false);
      break;

    // 4 Localizer component of an ILS (Instrument Landing System)
    case LOC:
      finshIls();
      writeIls(line, curFileId, rowCode);
      break;

    // 5 Localizer component of a localizer-only approach Includes for LDAs and SDFs
    case LOC_ONLY:
      finshIls();
      writeIls(line, curFileId, rowCode);
      break;

    // 6 Glideslope component of an ILS Frequency shown is paired frequency, notthe DME channel
    case GS:
      writeIls(line, curFileId, rowCode);
      break;

    // 7 Outer markers (OM) for an ILS Includes outer maker component of LOMs
    case OM:
    // 8 Middle markers (MM) for an ILS
    case MM:
    // 9 Inner markers (IM) for an ILS
    case IM:
      finshIls();
      writeMarker(line, curFileId, rowCode);
      break;

    // 12 DME, including the DME component of an ILS, VORTAC or VOR-DME Paired frequency display suppressed on X-Plane’s charts
    case DME:
      if(line.last() == "DME-ILS")
        writeIls(line, curFileId, rowCode);
      break;

    // 13 Stand-alone DME, or the DME component of an NDB-DME Paired frequency will be displayed on X-Plane’s charts
    case DME_ONLY:
      if(line.last() == "DME-ILS")
        writeIls(line, curFileId, rowCode);
      else
      {
        finshIls();
        writeVor(line, true, curFileId);
      }
      break;

    case atools::fs::xp::SBAS_GBAS_FINAL:
    case atools::fs::xp::GBAS:
    case atools::fs::xp::SBAS_GBAS_TRESHOLD:
      finshIls();

      // 14 Final approach path alignment point of an SBAS or GBAS approach path Will not appear in X-Plane’s charts
      // 15 GBAS differential ground station of a GLS Will not appear in X-Plane’s charts
      // 16 Landing threshold point or fictitious threshold point of an SBAS/GBAS approach Will not appear in X-Plane’s charts
  }
}

void NavWriter::initQueries()
{
  deInitQueries();

  atools::sql::SqlUtil util(&db);

  insertVorQuery = new SqlQuery(db);
  insertVorQuery->prepare(util.buildInsertStatement("vor", QString(), {"airport_id", "channel"}));

  insertNdbQuery = new SqlQuery(db);
  insertNdbQuery->prepare(util.buildInsertStatement("ndb", QString(), {"airport_id"}));

  insertMarkerQuery = new SqlQuery(db);
  insertMarkerQuery->prepare(util.buildInsertStatement("marker", QString(), {"ident"}));

  insertIlsQuery = new SqlQuery(db);
  insertIlsQuery->prepare(util.buildInsertStatement("ils", QString(), {"loc_runway_end_id"}));
}

void NavWriter::deInitQueries()
{
  delete insertVorQuery;
  insertVorQuery = nullptr;

  delete insertNdbQuery;
  insertNdbQuery = nullptr;

  delete insertMarkerQuery;
  insertMarkerQuery = nullptr;

  delete insertIlsQuery;
  insertIlsQuery = nullptr;
}

} // namespace xp
} // namespace fs
} // namespace atools
