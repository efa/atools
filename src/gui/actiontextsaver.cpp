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

#include "actiontextsaver.h"

#include <QAction>

namespace atools {
namespace gui {

ActionTextSaver::ActionTextSaver(QList<QAction *> actions)
{
  for(QAction *action : actions)
    texts.insert(action, action->text());
}

ActionTextSaver::~ActionTextSaver()
{
  for(QHash<QAction *, QString>::iterator it = texts.begin(); it != texts.end(); ++it)
    it.key()->setText(it.value());
}

} // namespace gui
} // namespace atools
