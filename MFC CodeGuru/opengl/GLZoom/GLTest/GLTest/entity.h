#define PI				3.14159265359

typedef struct tagColorStruct
{
	GLdouble red;
	GLdouble green;
	GLdouble blue;
}COLOR_STRUCT, *LPCOLOR_STRUCT;


typedef struct tagVertex
{
	double east;
	double north;
	double elev;
}VERTEX, *LPVERTEX;


class CCircleEntity
{
public:
	CCircleEntity(LPCOLOR_STRUCT color, LPVERTEX center, GLdouble radius);
	virtual void Draw();
protected:
	GLdouble m_Radius;
	LPVERTEX m_Center;
	COLOR_STRUCT m_Color;
};


