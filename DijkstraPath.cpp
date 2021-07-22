#include <fstream>

#include "DijkstraPath.h"
#include "GraphNode.h"
#include "AISettings.h"

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
	for (auto pair : *nodes)
	{
		GraphNode* node = pair.second.get();
		unsigned int id = node->GetId();

		std::string _font = "Comic Sans MS";
		std::wstring font = std::wstring(_font.begin(), _font.end());
		Font F(font.c_str(), 12, FontStyleRegular, UnitPixel);
		PointF P(node->GetPosX(), node->GetPosY());
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
			g->DrawLine(&edgePen, (*it)->fromNode->GetPosX(), (*it)->fromNode->GetPosY(),
				(*it)->toNode->GetPosX(), (*it)->toNode->GetPosY());
		}

		g->DrawEllipse(&nodePen, Rect(node->GetPosX() - 8, node->GetPosY() - 8, 16, 16));
		g->DrawString(text.c_str(), -1, &F, P, &SF, &B);
	}
}
