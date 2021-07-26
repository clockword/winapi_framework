#include <fstream>

#include "DijkstraPath.h"
#include "GraphNode.h"
#include "AISettings.h"

#include "Vector2.h"

void DijkstraPath::LoadExtra()
{
}

void DijkstraPath::Init()
{
}

void DijkstraPath::Draw(Graphics* g)
{
	GameObject::Draw(g);

	Pen edgePen(Color(255, 0, 0));
	Pen nodePen(Color(0, 0, 255));

	std::set<std::unique_ptr<EDGE>>::iterator it;
	std::set<std::unique_ptr<EDGE>>::iterator end;

	auto nodes = m_dijkstraGraph.GetNodes();
	for (auto &pair : *nodes)
	{
		GraphNode* node = pair.second.get();
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
		g->DrawString(text.c_str(), -1, &F, P, &SF, &B);
	}
}