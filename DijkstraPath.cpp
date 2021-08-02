#include <ctime>

#include "DijkstraPath.h"
#include "DijkstraNode.h"

#include "Vector2.h"

void DijkstraPath::LoadExtra()
{
}

void DijkstraPath::Init()
{
	m_beginSet = false;
	m_endSet = false;
}

void DijkstraPath::Draw(Graphics* g)
{
	GameObject::Draw(g);

	Pen edgePen(Color(255, 0, 0));
	Pen nodePen(Color(0, 0, 255));
	Pen beginPen(Color(0, 255, 0));
	beginPen.SetWidth(5);
	Pen endPen(Color(255, 0, 0));
	endPen.SetWidth(5);
	Pen pathPen(Color(255, 0, 255));
	pathPen.SetWidth(5);

	std::set<std::unique_ptr<DijkstraEdge>>::iterator it;
	std::set<std::unique_ptr<DijkstraEdge>>::iterator end;

	auto nodes = m_dijkstraGraph.GetNodes();
	for (auto &pair : *nodes)
	{
		DijkstraNode* node = pair.second.get();
		const unsigned int id = node->GetId();

		std::string _font = "Comic Sans MS";
		std::wstring font = std::wstring(_font.begin(), _font.end());
		Font F(font.c_str(), 12, FontStyleRegular, UnitPixel);
		const PointF P(node->GetPosX(), node->GetPosY());
		SolidBrush B(Color::Black);
		StringFormat SF;
		SF.SetAlignment(StringAlignmentCenter);
		SF.SetLineAlignment(StringAlignmentCenter);

		std::string _text = std::to_string(id);
		std::wstring text = std::wstring(_text.begin(), _text.end());

		it = node->GetEdges()->begin();
		end = node->GetEdges()->end();
		for (; it != end; it++)
		{
			const Vector2 from((*it)->fromNode->GetPosX(), (*it)->fromNode->GetPosY());
			const Vector2 to((*it)->toNode->GetPosX(), (*it)->toNode->GetPosY());
			Vector2 direction(from, to);
			const Vector2 normal(direction.GetNormalized());
			const Vector2 middle((from.x + to.x) * 0.5f, (from.y + to.y) * 0.5f);
			const Vector2 triStart(middle - normal * 10.0f);
			const Vector2 triLeft(triStart + Vector2::Rotate(normal, 90.0f) * 5.0f);
			const Vector2 triRight(triStart + Vector2::Rotate(normal, -90.0f) * 5.0f);
			g->DrawLine(&edgePen, from.x, from.y, to.x, to.y);
			g->DrawLine(&edgePen, triLeft.x, triLeft.y, triRight.x, triRight.y);
			g->DrawLine(&edgePen, triLeft.x, triLeft.y, middle.x, middle.y);
			g->DrawLine(&edgePen, triRight.x, triRight.y, middle.x, middle.y);
		}

		g->DrawEllipse(&nodePen, Rect(node->GetPosX() - 8, node->GetPosY() - 8, 16, 16));

		DijkstraNode* lastNode = nullptr;
		for (auto path : m_shortest)
		{
			if (lastNode == nullptr)
			{
				lastNode = path;
				continue;
			}
			g->DrawLine(&pathPen, lastNode->GetPosX(), lastNode->GetPosY(), path->GetPosX(), path->GetPosY());
			lastNode = path;
		}

		g->DrawString(text.c_str(), -1, &F, P, &SF, &B);

		if (m_beginSet)
		{
			const DijkstraNode* piece = nodes->at(m_beginID).get();
			g->DrawEllipse(&beginPen, Rect(piece->GetPosX() - 10, piece->GetPosY() - 10, 20, 20));
		}
		if (m_endSet)
		{
			const DijkstraNode* piece = nodes->at(m_endID).get();
			g->DrawEllipse(&endPen, Rect(piece->GetPosX() - 10, piece->GetPosY() - 10, 20, 20));
		}
	}
}

void DijkstraPath::SetBeginID(unsigned int id)
{
	m_beginID = id;
	m_beginSet = true;
}

void DijkstraPath::SetEndID(unsigned int id)
{
	m_endID = id;
	m_endSet = true;
}

void DijkstraPath::CheckIsReset(unsigned int id)
{
	if (id == m_beginID) m_beginSet = false;
	else if (id == m_endID) m_endSet = false;
}

DWORD DijkstraPath::Calculate()
{
	const DWORD tick = time(NULL);
	if (m_beginSet && m_endSet)
	{
		m_shortest = m_dijkstraGraph.Calculate(m_beginID, m_endID);
	}
	return time(NULL) - tick;
}
