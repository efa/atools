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

#ifndef ATOOLS_TABLEZOOMHANDLER_H
#define ATOOLS_TABLEZOOMHANDLER_H

#include <QObject>

class QAction;
class QAbstractItemView;
class QWidget;

namespace atools {
namespace gui {

/* Maintains font size/zoom functionality for table or tree widgets. Supports save and restore */
class ItemViewZoomHandler :
  public QObject
{
  Q_OBJECT

public:
  /* Will not support any zooming but set the initial cell and font size
   * if constructed with tableview parameter only. Otherwise font size can be changed using the given
   * actions*/
  ItemViewZoomHandler(QAbstractItemView *itemView, QAction *actionZoomIn = nullptr, QAction *actionZoomOut =
                        nullptr, QAction *actionZoomDefault = nullptr, QString settingsKeyStr = QString());
  virtual ~ItemViewZoomHandler();

  /* Use zoom methods for direct changes instead actions */
  void zoomTableView(int value);
  void zoomIn();
  void zoomOut();
  void zoomDefault();

  /* Bypasses all in/out/default methods and increases/decreases the size. */
  void zoomPercent(int percent);

  /* Section height will be font height plus this value */
  int getSectionToFontSize() const
  {
    return sectionToFontSize;
  }

  void setSectionToFontSize(int value)
  {
    sectionToFontSize = value;
  }

  /* Minimum font size in pixel */
  int getMinFontSize() const
  {
    return minFontSize;
  }

  void setMinFontSize(int value)
  {
    minFontSize = value;
  }

  /* Maximum font size in pixel */
  int getMaxFontSize() const
  {
    return maxFontSize;
  }

  void setMaxFontSize(int value)
  {
    maxFontSize = value;
  }

private:
  /* Change font size and store in settings */

  /* Update action status (enabled/disabled) */
  void enableDisableZoomActions();

  /* Init table row height according to font size (smaller than default) */
  void initTableViewZoom();

  /* Change font size and adjust row height accordingly */
  void setTableViewFontSize(float pointSize);

private:
  float defaultTableViewFontPointSize;

  int sectionToFontSize = 2;
  int minFontSize = 7;
  int maxFontSize = 16;

  QAbstractItemView *itemView;
  QAction *actionZoomIn, *actionZoomOut, *actionZoomDefault;
  QString settingsKey;
};

} // namespace gui
} // namespace atools

#endif // ATOOLS_TABLEZOOMHANDLER_H
