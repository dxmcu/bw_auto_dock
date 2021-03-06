/******************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Bluewhale Robot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Author: Xie fusheng, Randoms
 *******************************************************************************/

#ifndef __GRIDLINETRAVERSAL_H__
#define __GRIDLINETRAVERSAL_H__

#include <cstdlib>
#include "bw_auto_dock/point.h"

namespace bw_auto_dock
{
typedef struct
{
    int num_points;
    IntPoint* points;
} GridLineTraversalLine;

struct GridLineTraversal
{
    inline static void gridLine(IntPoint start, IntPoint end, GridLineTraversalLine* line);
    inline static void gridLineCore(IntPoint start, IntPoint end, GridLineTraversalLine* line);
};

void GridLineTraversal::gridLineCore(IntPoint start, IntPoint end, GridLineTraversalLine* line)
{
    int dx, dy, incr1, incr2, d, x, y, xend, yend, xdirflag, ydirflag;
    int cnt = 0;

    dx = abs(end.x - start.x);
    dy = abs(end.y - start.y);

    if (dy <= dx)
    {
        d = 2 * dy - dx;
        incr1 = 2 * dy;
        incr2 = 2 * (dy - dx);
        if (start.x > end.x)
        {
            x = end.x;
            y = end.y;
            ydirflag = (-1);
            xend = start.x;
        }
        else
        {
            x = start.x;
            y = start.y;
            ydirflag = 1;
            xend = end.x;
        }
        line->points[cnt].x = x;
        line->points[cnt].y = y;
        cnt++;
        if (((end.y - start.y) * ydirflag) > 0)
        {
            while (x < xend)
            {
                x++;
                if (d < 0)
                {
                    d += incr1;
                }
                else
                {
                    y++;
                    d += incr2;
                }
                line->points[cnt].x = x;
                line->points[cnt].y = y;
                cnt++;
            }
        }
        else
        {
            while (x < xend)
            {
                x++;
                if (d < 0)
                {
                    d += incr1;
                }
                else
                {
                    y--;
                    d += incr2;
                }
                line->points[cnt].x = x;
                line->points[cnt].y = y;
                cnt++;
            }
        }
    }
    else
    {
        d = 2 * dx - dy;
        incr1 = 2 * dx;
        incr2 = 2 * (dx - dy);
        if (start.y > end.y)
        {
            y = end.y;
            x = end.x;
            yend = start.y;
            xdirflag = (-1);
        }
        else
        {
            y = start.y;
            x = start.x;
            yend = end.y;
            xdirflag = 1;
        }
        line->points[cnt].x = x;
        line->points[cnt].y = y;
        cnt++;
        if (((end.x - start.x) * xdirflag) > 0)
        {
            while (y < yend)
            {
                y++;
                if (d < 0)
                {
                    d += incr1;
                }
                else
                {
                    x++;
                    d += incr2;
                }
                line->points[cnt].x = x;
                line->points[cnt].y = y;
                cnt++;
            }
        }
        else
        {
            while (y < yend)
            {
                y++;
                if (d < 0)
                {
                    d += incr1;
                }
                else
                {
                    x--;
                    d += incr2;
                }
                line->points[cnt].x = x;
                line->points[cnt].y = y;
                cnt++;
            }
        }
    }
    line->num_points = cnt;
}

void GridLineTraversal::gridLine(IntPoint start, IntPoint end, GridLineTraversalLine* line)
{
    int i, j;
    int half;
    IntPoint v;
    gridLineCore(start, end, line);
    if (start.x != line->points[0].x || start.y != line->points[0].y)
    {
        half = line->num_points / 2;
        for (i = 0, j = line->num_points - 1; i < half; i++, j--)
        {
            v = line->points[i];
            line->points[i] = line->points[j];
            line->points[j] = v;
        }
    }
}

};  // namespace bw_auto_dock

#endif
