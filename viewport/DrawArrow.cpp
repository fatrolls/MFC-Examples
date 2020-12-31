#include "stdafx.h"

#include "DrawArrow.h"

/****************************************************************************
*                                  DrawArrow
* Inputs:
*       CDC & dc: DC
*       
*       CRect r: Rectangle to draw in
* Result: void
*       
* Effect: 
*       Draws an arrow
****************************************************************************/

void DrawArrow::Draw(CDC & dc, CRect r, Direction direction)
   {
    CArray <CPoint, CPoint&> points;

#define ARROW_BODY_RATIO 5
    switch(direction)
       { /* direction */
        case ARROW_N:
           { /* up */
            /****************************************************************
                              [0]
                         +-----.-----+
                         |    / \    |
                         |   /   \   |
                         |  /     \  |
                         | /       \ |
                      [6]|/__[5|2]__\| [1]
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         +---.---.---+
                            [4] [3]
            ****************************************************************/                         

            int dx = r.Width() / ARROW_BODY_RATIO;
            points.Add(CPoint(r.left + r.Width() / 2,        r.top));                  // [0]
            points.Add(CPoint(r.right,                       r.top + r.Width() / 2));  // [1]
            points.Add(CPoint(points[0].x + dx,              points[1].y));            // [2]
            points.Add(CPoint(points[2].x,                   r.bottom));               // [3]
            points.Add(CPoint(points[0].x - dx,              r.bottom));               // [4]
            points.Add(CPoint(points[4].x,                   points[1].y));            // [5]
            points.Add(CPoint(r.left,                        points[1].y));            // [6]

            dc.BeginPath();
            dc.Polyline(points.GetData(), points.GetSize());
            dc.CloseFigure();
            dc.EndPath();
            dc.StrokeAndFillPath();
           } /* up */
           break;
        case ARROW_S:
           { /* down */
            /****************************************************************
                            [4] [3]
                         +---.---.---+
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                         |   |   |   |
                      [6]|___|   |___| [1]
                         |\ [5] [2] /|
                         | \       / |
                         |  \     /  |
                         |   \   /   |
                         |    \ /    |
                         +-----.-----+
                              [0]
            ****************************************************************/                         
            int dx = r.Width() / ARROW_BODY_RATIO;

            points.Add(CPoint(r.left + r.Width() / 2,       r.bottom));                // [0]
            points.Add(CPoint(r.right,                      r.bottom - r.Width() / 2));// [1]
            points.Add(CPoint(points[0].x + dx,             points[1].y));             // [2]
            points.Add(CPoint(points[2].x,                  r.top));                   // [3]
            points.Add(CPoint(points[0].x - dx,             r.top));                   // [4]
            points.Add(CPoint(points[4].x,                  points[1].y));             // [5]
            points.Add(CPoint(r.left,                       points[1].y));             // [6]

            dc.BeginPath();
            dc.Polyline(points.GetData(), points.GetSize());
            dc.CloseFigure();
            dc.EndPath();
            dc.StrokeAndFillPath();
           } /* down */
           break;
        case ARROW_NONE:
           // Do not draw anything
           break;
        case ARROW_W:
           { /* left */
            /****************************************************************
                             [1]
                         +----.---------------------------------+
                         |   /|                                 |
                         |  / |_________________________________. [3]
                         | /[2]                                 |
                      [0].                                      |
                         | \[5]_________________________________. [4]
                         |  \ |                                 |
                         |   \|                                 |
                         +----.---------------------------------+
                             [6]
            ****************************************************************/                         
            int dy = r.Height() / ARROW_BODY_RATIO;
            points.Add(CPoint(r.left,                       r.top + r.Height() / 2));   // [0]
            points.Add(CPoint(r.left + r.Height() / 2,      r.top));                    // [1]
            points.Add(CPoint(points[1].x,                  points[0].y - dy));         // [2]
            points.Add(CPoint(r.right,                      points[2].y));              // [3]
            points.Add(CPoint(r.right,                      points[0].y + dy));         // [4]
            points.Add(CPoint(points[1].x,                  points[4].y));              // [5]
            points.Add(CPoint(points[1].x,                  r.bottom));                 // [6]

            dc.BeginPath();
            dc.Polyline(points.GetData(), points.GetSize());
            dc.CloseFigure();
            dc.EndPath();
            dc.StrokeAndFillPath();
           } /* left */
           break;
        case ARROW_E:
           { /* right */
            /****************************************************************
                                                          [1]
                         +---------------------------------.----+
                         |                                 |\   |
                         |                                 | \  |
                      [3]._________________________________.  \ |
                         |                                 [2] \. [0]
                         |                                 [5] /|    
                      [4]._________________________________.  / |
                         |                                 | /  |
                         |                                 |/   |
                         +---------------------------------.----+
                                                          [6]
            ****************************************************************/                         
            int dy = r.Height() / ARROW_BODY_RATIO;
            points.Add(CPoint(r.right,                      r.top + r.Height() / 2));   // [0]
            points.Add(CPoint(r.right - r.Height() / 2,     r.top));                    // [1]
            points.Add(CPoint(points[1].x,                  points[0].y - dy));         // [2]
            points.Add(CPoint(r.left,                       points[2].y));              // [3]
            points.Add(CPoint(r.left,                       points[0].y + dy));         // [4]
            points.Add(CPoint(points[1].x,                  points[4].y));              // [5]
            points.Add(CPoint(points[1].x,                  r.bottom));                 // [6]

            dc.BeginPath();
            dc.Polyline(points.GetData(), points.GetSize());
            dc.CloseFigure();
            dc.EndPath();
            dc.StrokeAndFillPath();
           } /* right */
           break;
        default:
           ASSERT(FALSE); // only up and down implemented right now
           break;
       } /* direction */
    
   } // DrawArrow

