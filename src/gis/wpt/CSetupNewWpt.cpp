/**********************************************************************************************
    Copyright (C) 2014 Oliver Eichler oliver.eichler@gmx.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#include "GeoMath.h"
#include "gis/WptIcons.h"
#include "gis/wpt/CSetupNewWpt.h"
#include "helpers/CPositionDialog.h"
#include "helpers/CWptIconDialog.h"
#include "units/IUnit.h"

#include <QtWidgets>


CSetupNewWpt::CSetupNewWpt(QPointF &pt, QString &icon, QString &name, QWidget *parent)
    : QDialog(parent)
    , pt(pt)
    , icon(icon)
    , name(name)
{
    QPointF focus;

    setupUi(this);
    toolIcon->setObjectName(icon);
    toolIcon->setIcon(getWptIconByName(icon, focus));

    QString pos;
    GPS_Math_Deg_To_Str(pt.x(), pt.y(), pos);
    linePosition->setText(pos);
    labelWarning->hide();

    lineName->setText(name);

    connect(linePosition, SIGNAL(textEdited(QString)), this, SLOT(slotEditPosition(QString)));
    connect(lineName, SIGNAL(textEdited(QString)), this, SLOT(slotEditName(QString)));
    connect(toolIcon, SIGNAL(clicked()), this, SLOT(slotChangeIcon()));

    checkInput();
}

CSetupNewWpt::~CSetupNewWpt()
{
}


void CSetupNewWpt::accept()
{
    CPositionDialog::getPosition(pt, linePosition->text());
    icon = toolIcon->objectName();
    name = lineName->text();

    QDialog::accept();
}

void CSetupNewWpt::reject()
{
    pt = NOPOINTF;
    name.clear();
    icon.clear();

    QDialog::reject();
}

void CSetupNewWpt::slotEditPosition(const QString& str)
{
    if(CPositionDialog::reCoord1.exactMatch(str))
    {
        labelWarning->hide();
    }
    else if(CPositionDialog::reCoord2.exactMatch(str))
    {
        labelWarning->hide();
    }
    else if(CPositionDialog::reCoord3.exactMatch(str))
    {
        labelWarning->hide();
    }
    else if(CPositionDialog::reCoord4.exactMatch(str))
    {
        labelWarning->hide();
    }
    else if(CPositionDialog::reCoord5.exactMatch(str))
    {
        labelWarning->hide();
    }
    else
    {
        labelWarning->show();
    }

    checkInput();
}

void CSetupNewWpt::slotEditName(const QString& str)
{
    checkInput();
}

void CSetupNewWpt::slotChangeIcon()
{
    CWptIconDialog dlg(toolIcon);
    dlg.exec();
}


void CSetupNewWpt::checkInput()
{
    if(labelWarning->isHidden() && !lineName->text().isEmpty())
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
