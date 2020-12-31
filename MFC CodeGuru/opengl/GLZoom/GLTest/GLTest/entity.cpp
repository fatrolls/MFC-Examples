#include "stdafx.h"
#include "entity.h"
#include <math.h>
///////////////////////////////////////////////////////////////////////////////////
// CBSplineEntity

CCircleEntity::CCircleEntity(LPCOLOR_STRUCT color, LPVERTEX center, GLdouble radius)
{
	memcpy(&m_Color, color, sizeof(COLOR_STRUCT));
	m_Center = new VERTEX;
	memcpy(m_Center, center, sizeof(VERTEX));
	m_Radius = radius;
}

void CCircleEntity::Draw()
{
	::glColor3d(m_Color.red, m_Color.green, m_Color.blue);
	GLdouble alpha= 0.0; /* Winkel zum Zeichnen des Kreises von 0.0- < 360.0 */

	/* Zeichnen eines geschlossenen Linienzuges */
	glBegin( GL_LINE_LOOP);
	while( alpha< 2*PI)
	{

		/* Berechnung der X-Y Koordinaten und setzen der Punkte */
		GLdouble x = m_Center->east + ((GLdouble)sin(alpha) * m_Radius);
		GLdouble y = m_Center->north + ((GLdouble)cos(alpha) * m_Radius);
		::glVertex3d(x, y, m_Center->elev);

		/* Winkel wird um PI/16 erhoeht - 'Kreis' besteht aus 32 Segmenten.
		Hier koennte man herumexperimentieren ( z.b. mal PI/ 4 eintragen)*/
		alpha += PI/ 128;
		if(alpha >= 360)
			alpha -= 360;
	}
	glEnd();
}
