#include "stdafx.h"
#include "_malaAnalysis.h"

vector<malaTopoCell> CmalaTopo::m_TopoObject;

CmalaTopo::CmalaTopo(CView* mView, malaScreen *pScreen, CString &fileFullPath, int topoType)
{

	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;

	CmalaPointsSelect obj1(mBaseView,mScreen, mPath);
	m_SelectPnt = obj1;


	CmalaLinesSelect obj2(mBaseView, mScreen, mPath);
	m_SelectLine = obj2;


	CmalaPolysSelect obj3(mBaseView, mScreen, mPath);
	m_SelectePoly = obj3;

	m_Selected = FALSE;

	m_SelectStyle = topoType;

}

CmalaTopo::~CmalaTopo()
{

}

void CmalaTopo::LButtonDown(UINT nFlags, malaPoint point)
{
	switch (m_SelectStyle)
	{
	case 1:
		if (!m_Selected)
			m_SelectPnt.LButtonDown(nFlags, point);
		break;
	case 2:
		if (!m_Selected)
			m_SelectLine.LButtonDown(nFlags, point);
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.LButtonDown(nFlags, point);
		break;
	default:
		break;
	}
}

void CmalaTopo::LButtonUp(UINT nFlags, malaPoint point)
{
	vector<malaPoint>MyPoint;
	malaTopoCell topo;
	switch (m_SelectStyle)
	{
	case 1:
		if (!m_Selected)
			m_SelectPnt.LButtonUp(nFlags, point);
		m_Selected = m_SelectPnt.m_Selected;
		if (m_Selected)
		{
			MyPoint.push_back(m_SelectPnt.m_pnt);
			topo.index = 1;
			topo.Object = MyPoint;
			m_TopoObject.push_back(topo);
			if (m_TopoObject.size() == 2)
			{
				topoAnalysis(m_TopoObject);
				m_TopoObject.clear();
			}

			m_Selected = FALSE;
			m_SelectPnt.m_Selected = FALSE;
		}
		break;
	case 2:
		if (!m_Selected)
			m_SelectLine.LButtonUp(nFlags, point);
		m_Selected = m_SelectLine.m_Selected;
		if (m_Selected)
		{
			topo.index = 2;
			topo.Object = m_SelectLine.mLine;

			m_TopoObject.push_back(topo);
			if (m_TopoObject.size() == 2)
			{
				topoAnalysis(m_TopoObject);
				m_TopoObject.clear();
			}

			m_Selected = FALSE;
			m_SelectLine.m_Selected = FALSE;
		}
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.LButtonUp(nFlags, point);
		m_Selected = m_SelectePoly.m_Selected;
		if (m_Selected)
		{
			topo.index = 3;
			topo.Object = m_SelectePoly.mSPoly;

			m_TopoObject.push_back(topo);
			if (m_TopoObject.size() == 2)
			{
				topoAnalysis(m_TopoObject);
				m_TopoObject.clear();
			}

			m_Selected = FALSE;
			m_SelectePoly.m_Selected = FALSE;
		}
		break;
	default:
		break;
	}
}

void CmalaTopo::MouseMove(UINT nFlags, malaPoint point)
{

	switch (m_SelectStyle)
	{
	case 1:
		if (!m_Selected)
			m_SelectPnt.MouseMove(nFlags, point);
		break;
	case 2:
		if (!m_Selected)
			m_SelectLine.MouseMove(nFlags, point);
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.MouseMove(nFlags, point);
		break;
	default:
		break;
	}

}

void CmalaTopo::topoAnalysis(vector<malaTopoCell>TopoObject)
{
	malaLogic math;
	vector<malaPoint> Topo1;
	vector<malaPoint> Topo2;
	int index1;//index=1表示点；等于2表示线；等于3表示面
	int index2;
	Topo1 = TopoObject[0].Object;
	index1 = TopoObject[0].index;
	Topo2 = TopoObject[1].Object;
	index2 = TopoObject[1].index;
	//点与点关系
	if (index1 == 1 && index2 == 1)
	{
		if (math.isPointEqPoint(Topo1[0], Topo2[0]))
			MessageBox(mBaseView->m_hWnd, L"两点重合", L"点与点拓扑关系", MB_OK | MB_ICONINFORMATION);
		else
			MessageBox(mBaseView->m_hWnd, L"点与点相离", L"点与点拓扑关系", MB_OK | MB_ICONINFORMATION);
	}

	//点与线
	if (index1 == 1 && index2 == 2)
	{
		if (math.isPointInPolyLine(Topo1[0], Topo2))
			MessageBox(mBaseView->m_hWnd, L"点在线上", L"点与线拓扑关系", MB_OK | MB_ICONINFORMATION);
		else
			MessageBox(mBaseView->m_hWnd, L"点不在线上", L"点与线拓扑关系", MB_OK | MB_ICONINFORMATION);
	}

	if (index1 == 2 && index2 == 1)
	{
		if (math.isPointInPolyLine(Topo2[0], Topo1))
			MessageBox(mBaseView->m_hWnd, L"点在线上", L"点与线拓扑关系", MB_OK | MB_ICONINFORMATION);
		else
			MessageBox(mBaseView->m_hWnd, L"点不在线上", L"点与线拓扑关系", MB_OK | MB_ICONINFORMATION);
	}

	//点与面

	switch (index1)
	{
	case 1:
		if (index2 == 3)
		{
			if (math.isPointInPolygon(Topo1[0], Topo2))
				MessageBox(mBaseView->m_hWnd, L"点在区内", L"点与面拓扑关系", MB_OK | MB_ICONINFORMATION);
			else
				MessageBox(mBaseView->m_hWnd, L"点在区外", L"点与面拓扑关系", MB_OK | MB_ICONINFORMATION);
		}
		break;

	case 3:
		if (index2 == 1)
		{
			if (math.isPointInPolygon(Topo2[0], Topo1))
				MessageBox(mBaseView->m_hWnd, L"点在区内", L"点与面拓扑关系", MB_OK | MB_ICONINFORMATION);
			else
				MessageBox(mBaseView->m_hWnd, L"点在区外", L"点与面拓扑关系", MB_OK | MB_ICONINFORMATION);
		}
		break;
	default:
		;
	}

	//线与线
	if (index1 == 2 && index2 == 2)
	{
		//相等返回1;相交返回2;相离返回3
		int index = math.lineAndLine(Topo1, Topo2);
		switch (index)
		{
		case 1:
			MessageBox(mBaseView->m_hWnd, L"两条线相等", L"线与线拓扑关系", MB_OK | MB_ICONINFORMATION);
			break;
		case 2:
			MessageBox(mBaseView->m_hWnd, L"两条线相交", L"线与线拓扑关系", MB_OK | MB_ICONINFORMATION);
			break;
		case 3:
			MessageBox(mBaseView->m_hWnd, L"两条线相离", L"线与线拓扑关系", MB_OK | MB_ICONINFORMATION);
		default:
			;
		}
	}

	//线与面
	//相离返回1，相交返回2，在区内返回3
	int LinePolygon;
	switch (index1)
	{
	case 2:
		if (index2 == 3)
		{
			LinePolygon = math.polyLineAndPolygon(Topo1, Topo2);
			if (LinePolygon == 1)
				MessageBox(mBaseView->m_hWnd, L"线与区相离", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
			else if (LinePolygon == 2)
				MessageBox(mBaseView->m_hWnd, L"线与区相交", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
			else
				MessageBox(mBaseView->m_hWnd, L"线在区内", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
		}
		break;

	case 3:
		if (index2 == 2)
		{
			LinePolygon = math.polyLineAndPolygon(Topo2, Topo1);
			if (LinePolygon == 1)
				MessageBox(mBaseView->m_hWnd, L"线与区相离", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
			else if (LinePolygon == 2)
				MessageBox(mBaseView->m_hWnd, L"线与区相交", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
			else
				MessageBox(mBaseView->m_hWnd, L"线在区内", L"线与区拓扑关系", MB_OK | MB_ICONINFORMATION);
		}
		break;

	default:
		;
	}

	//面与面
	//相等返回1，相交返回2，内含返回3,相离返回4
	if (index1 == 3 && index2 == 3)
	{
		int PolygonPolygon = math.polygonAndPolygon(Topo2, Topo1);
		if (PolygonPolygon == 1)
			MessageBox(mBaseView->m_hWnd, L"区与区相等", L"区与区的拓扑", MB_OK | MB_ICONINFORMATION);
		if (PolygonPolygon == 2)
			MessageBox(mBaseView->m_hWnd, L"区与区相交", L"区与区的拓扑", MB_OK | MB_ICONINFORMATION);
		if (PolygonPolygon == 3)
			MessageBox(mBaseView->m_hWnd, L"区内含", L"区与区的拓扑", MB_OK | MB_ICONINFORMATION);
		if (PolygonPolygon == 4)
			MessageBox(mBaseView->m_hWnd, L"区与区相离", L"区与区的拓扑", MB_OK | MB_ICONINFORMATION);
		if (PolygonPolygon == 5)
			MessageBox(mBaseView->m_hWnd, L"区覆盖区", L"区与区的拓扑", MB_OK | MB_ICONINFORMATION);
	}
}

//自定义量算
CmalaLineMeasureCustom::CmalaLineMeasureCustom(CView* ptView, malaScreen *Screen)
{
	mBaseView = ptView;
	m_LinePro.lineColor = RGB(0, 0, 0);
	m_LinePro.lineStyle = 0;
	m_LinePro.lineWidth = 1;
	m_bDraw = FALSE;
	m_Screen = Screen;
}

CmalaLineMeasureCustom::~CmalaLineMeasureCustom()
{

}

void CmalaLineMeasureCustom::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_PerPoint = m_PtOrigin = point;
	m_Line.push_back(point);
}


void CmalaLineMeasureCustom::MouseMove(UINT nFlags, malaPoint point)
{
	//橡皮线
	malaCDC dc(mBaseView, *m_Screen);
	if (m_bDraw)
	{
		dc.lineDrawX(m_PtOrigin, m_PerPoint, m_LinePro);
		dc.lineDrawX(m_PtOrigin, point, m_LinePro);
		m_PerPoint = point;
	}

}
void CmalaLineMeasureCustom::RButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	malaLogic tMath;
	double dis = tMath.distanceLine(m_Line);
	CString str;
	str.Format(L"%f ", dis);
	MessageBox(mBaseView->m_hWnd, str, L"坐标长度", MB_OK);
	mBaseView->Invalidate(TRUE);
	m_Line.clear();
}

//已知直线量算
CmalaLineMeasure::CmalaLineMeasure(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	//m_LinePro.lineColor = RGB(0, 0, 0);
	//m_LinePro.lineStyle = 0;
	//m_LinePro.lineWidth = 1;

	mPath = fileFullPath;
	m_Screen = pScreen;

	CmalaLinesSelect obj(mBaseView, m_Screen, mPath);
	m_SelectLine = obj;
	this->m_Selected = m_SelectLine.m_Selected;
}

CmalaLineMeasure::~CmalaLineMeasure()
{

}

void CmalaLineMeasure::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = m_perPoint = point;
	}
}

void CmalaLineMeasure::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.LButtonUp(nFlags, point);

	m_Selected = m_SelectLine.m_Selected;
	if (m_Selected)
	{
		m_line = m_SelectLine.mLine;
		m_linepro = m_SelectLine.mLinePro;
		malaLogic tMath;
		double dis = tMath.distanceLine(m_line);
		CString str;
		str.Format(L"%f", dis);
		MessageBox(mBaseView->m_hWnd, str, L"坐标长度", MB_OK);
		m_Selected = FALSE;
		m_SelectLine.m_Selected = FALSE;
	}
}

void CmalaLineMeasure::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectLine.MouseMove(nFlags, point);
}
/*
* 多边形量算
*/
CmalaPolyMeasure::CmalaPolyMeasure(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	//m_LinePro.lineColor = RGB(0, 0, 0);
	//m_LinePro.lineStyle = 0;
	//m_LinePro.lineWidth = 1;

	mPath = fileFullPath;
	m_Screen = pScreen;

	CmalaPolysSelect obj(mBaseView, m_Screen, mPath);
	m_SelectPoly = obj;
	this->m_Selected = m_SelectPoly.m_Selected;
}

CmalaPolyMeasure::~CmalaPolyMeasure()
{

}

void CmalaPolyMeasure::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPoly.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = m_perPoint = point;
	}
}

void CmalaPolyMeasure::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPoly.LButtonUp(nFlags, point);

	m_Selected = m_SelectPoly.m_Selected;
	if (m_Selected)
	{
		m_poly = m_SelectPoly.mSPoly;
		m_polypro = m_SelectPoly.mSPolyPro;
		malaLogic tMath;
		double area = tMath.ComputePolygonArea(m_poly);
		m_poly.push_back(m_poly[0]);
		double dis = tMath.distanceLine(m_poly);
		CString str;
		str.Format(L"面积：%f \n周长：%f", area, dis);
		MessageBox(mBaseView->m_hWnd, str, L"量算结果", MB_OK);
		m_Selected = FALSE;
		m_SelectPoly.m_Selected = FALSE;
	}
}

void CmalaPolyMeasure::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPoly.MouseMove(nFlags, point);
}