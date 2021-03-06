#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define malabasedll  __declspec(dllimport)
#else
#define malabasedll  __declspec(dllexport)
#endif

#include "malaStruct.h"
#include "_malaBase.h"
#include <vector>
using namespace std;

/*
* 屏幕坐标转换函数
*/

void malabasedll ScreenToCoord(long inX, long inY, malaScreen pScreen, double *outX, double *outY);//屏幕坐标系转换为平面坐标系
void malabasedll CoordToScreen(double inX, double inY, malaScreen pScreen, long *outX, long *outY);//平面坐标系转换为屏幕坐标系

/*
* 鼠标操作基类
*/
class malabasedll CmalaMouseAction
{
public:
	CmalaMouseAction();
	virtual ~CmalaMouseAction();
	virtual void LButtonDown (UINT nFlags, malaPoint point);
	virtual void LButtonUp(UINT nFlags, malaPoint point);
	virtual void RButtonDown(UINT nFlags, malaPoint point);
	virtual void RButtonUp(UINT nFlags, malaPoint point);
	virtual void MouseMove(UINT nFlags, malaPoint point);
	virtual void MouseWheel(UINT nFlags, short zDelta, malaPoint pt);

	CView* mBaseView;
};

/*
* 绘图类
*/
class malabasedll malaCDC
{
public:
	malaCDC(CView* ptView,malaScreen pScreen);
	~malaCDC();
public:
	void pointDrawAuto(malaPoint Point, malaPointPro PntPro);//根据点型自动绘制点
	void pointDrawAutoX(malaPoint Point, malaPointPro PntPro);//根据点型自动绘制点(橡皮)

	void pointDrawCircle(malaPoint Point, malaPointPro PntPro);//绘制一个圆点
	void pointDrawCircleX(malaPoint Point, malaPointPro PntPro);//绘制一个圆点(橡皮)
	void pointDrawRect(malaPoint Point, malaPointPro PntPro);//绘制一个矩形点
	void pointDrawRectX(malaPoint Point, malaPointPro PntPro);//绘制一个矩形点(橡皮)
	void pointDrawTriangle(malaPoint Point, malaPointPro PntPro);//绘制一个三角形点
	void pointDrawTriangleX(malaPoint Point, malaPointPro PntPro);//绘制一个三角形点(橡皮)

	void lineDraw(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro); //绘制直线
	void lineDrawX(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro);//绘制直线（橡皮）
	void lineDrawAll(vector<malaPoint>& Line, malaLinePro LinePro);//绘制一条折线
	void lineDrawAllX(vector<malaPoint>& Line, malaLinePro LinePro);//绘制一条折线（橡皮）

	void polyDrawAuto(vector<malaPoint>& Poly, malaPolyPro PolyPro);//自动绘制一个多边形
	void polyDrawAutoX(vector<malaPoint>& Poly, malaPolyPro PolyPro);//自动绘制一个多边形(橡皮)
	void polyDraw(vector<malaPoint>& Poly, malaPolyPro PolyPro);//绘制一个多边形
	void polyDrawX(vector<malaPoint>& Poly, malaPolyPro PolyPro);//绘制一个多边形(橡皮)
	void ellipseDraw(vector<malaPoint>& Poly, malaPolyPro PolyPro);//根据一个多边形的外包矩形绘制一个椭圆
	void ellipseDrawX(vector<malaPoint>& Poly, malaPolyPro PolyPro);//根据一个多边形的外包矩形绘制一个椭圆(橡皮)

	
	void textDraw(malaPoint Point, malaLabelPro &labelPro);//绘制字体
	
	void drawSelectRectPoint(malaPoint Point, malaPointPro PntPro);//绘制选中状态的外接矩形
	void drawSelectCirclePoint(malaPoint Point, malaPointPro PntPro);//绘制选中状态的外接圆

	void drawRectNULLFill(malaPoint Point1, malaPoint point2);//绘制空心矩形

private:
	CView* mView;//绘图指针
	malaScreen mScreen;

};

/*
*逻辑运算基类
*/
class malabasedll malaLogic
{
public:
	malaLogic();
	~malaLogic();
public:
	
	double getMaxX(vector<malaPoint>& Point);//从所有的点中找到最大的x
	double getMaxY(vector<malaPoint>& Point);//从所有的点中找到最大的y
	double getMinX(vector<malaPoint>& Point);//从所有的点中找到最小的x
	double getMinY(vector<malaPoint>& Point);//从所有的点中找到最小的y
	
	malaRect getRect(vector<malaPoint>& Point);//返回一个图元的外接矩形
public:
	bool isPntInRect(malaPoint &Point, malaRect& rc);//点是否在矩形内部
	bool isRectIntersect(malaRect &r1, malaRect &r2);//判断两个矩形是否相交（不能判断包含）

	bool isLineIntersect(malaPoint startPointA, malaPoint endPointA, malaPoint startPointB, malaPoint endPointB);//判断两条直线是否相交
	bool isLinePolylineIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Line);//判断直线是否与折线相交
	bool isLineInRect(malaRect& rc, vector<malaPoint>& Line);//判断折线与矩形是否相交

	bool isPolyInRect(malaRect& rc, vector<malaPoint>& Poly);//判断区是否和矩形相交
	bool isLinePolyIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Poly);//判断直线是否与多边形相交

	bool cutLine(malaPoint point, vector<malaPoint>& Line1, vector<malaPoint>& Line2);//剪断线
	bool addPointInLine(malaPoint point, vector<malaPoint>& Line);//线上加点

	bool addPointPoly(malaPoint point, vector<malaPoint>& Poly);//边界加点
	bool delPointPoly(malaPoint point, vector<malaPoint>& Poly);//边界删点
	
	double distancePointToPoint(malaPoint point1, malaPoint point2);//计算两点距离
	int getPointPosInLine(malaPoint point, vector<malaPoint>& Line);//得到点在线的位置

	bool isPointInLine(malaPoint point, malaPoint startPoint, malaPoint endPoint);//判断点是否在直线上
	bool isPointInPolyLine(malaPoint point, vector<malaPoint>& Line);//判断点是否在折线上
	bool isPointEqPoint(malaPoint point1, malaPoint point2);//判断两点之前的拓扑关系
	bool isPointInPolygon(malaPoint point, vector<malaPoint>& Poly);//点是否在多边形内部
	int  lineAndLine(vector<malaPoint>& Line1, vector<malaPoint>& Line2);  //折线与折线的拓扑关系 相等返回1;相交返回2;相离返回3
	int  polyLineAndPolygon(vector<malaPoint>&Line, vector<malaPoint>&Polygon);	//折线与多边形拓扑关系 相离返回1，相交返回2，在区内返回3
	int  lineAndPolygon(malaPoint pntStart, malaPoint pntEnd, vector<malaPoint>&Polygon);//直线与多边形拓扑关系  相离返回1，相交返回2，在区内返回3
	int  polygonAndPolygon(vector<malaPoint>&Polygon1, vector<malaPoint>&Polygon2);//面与面的拓扑关系  相等返回1，相交返回2，内含返回3,相离返回4

	
	double distanceLine(vector<malaPoint>& pLilne);//计算一条线的长度
	double ComputePolygonArea(vector<malaPoint> &points);//计算任意多边形的面积

};

#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif