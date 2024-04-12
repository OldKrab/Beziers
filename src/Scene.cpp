#include <execution>
#include "Scene.h"

#include "HelperFunctions.h"

Scene::Scene(sf::RenderWindow* window, InputHandler* inputHandler) :
	_window(window),
	_inputHandler(inputHandler),
	_isGenerate(false),
	_splineGenerator(1.f, 0.01f),
	_isMouseFollowing(false)
{
}

void Scene::Update(float dt)
{
	if (_isGenerate) {
		_splineGenerator.Update(dt);
		if (_splineGenerator.IsTimeToGenerate())
			GenerateSpline();
	}
	std::for_each(std::execution::par, _splines.begin(), _splines.end(), [dt, this](auto& spline){
		spline.Update(dt);

		if (spline.IsEnded())
			ResetSpline(spline);
	});
	
	UpdateWindowViewCenter(dt);
}

void Scene::SetGenerate(bool value)
{
	_isGenerate = value;
	if (!_isGenerate)
		_splineGenerator.Reset();
}

void Scene::MovePosition(sf::Vector2f vec)
{
	for (auto&& spline : _splines)
		spline.MovePosition(vec);
}

sf::Vector2f Scene::GetPositionsCentroid() const
{
	if (_splines.size() == 0)
		return { 0,0 };
	sf::Vector2f sum(0, 0);
	for (auto& spline : _splines)
		sum += spline.GetCurrentPosition();
	return sum / static_cast<float>(_splines.size());
}

void Scene::Reset()
{
	_splines.erase(_splines.begin() + 1, _splines.end());
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& spline : _splines)
		target.draw(spline);
}



void Scene::GenerateSpline()
{
	auto&& spline = _splines.emplace_back();
	auto dest = GetMouseWorldPosition();
	spline.AddBezier(dest, dest);

	
	spline.SetColor(static_cast<float>(rand()) / RAND_MAX);
	//spline.SetColor(sf::Color(rand() % 200 , rand() % 200, rand() % 200));
	spline.SetSpeed(static_cast<float>(MAX_SPLINE_SPEED - (float)rand() / (float)RAND_MAX * (MAX_SPLINE_SPEED - MIN_SPLINE_SPEED)));
}



void Scene::ResetSpline(MovingBezierSpline& spline) const
{
	sf::Vector2i lt(-20, -20), rb(20, 20);
	sf::Vector2f worldPos = GetMouseWorldPosition();
	auto dir = worldPos - spline.GetCurrentPosition();
	auto delta = static_cast<int>(HelperFunctions::GetLength(worldPos - spline.GetCurrentPosition()));
	delta = std::min(std::max(delta, 50), MAX_DELTA_COEF);
	auto dest = spline.GetCurrentPosition() + dir * MAX_DIR_COEF;
	auto middle = spline.GetCurrentPosition() + dir * MAX_DIR_COEF/2.F;
	if (_isMouseFollowing)
	{
		dest = spline.GetCurrentPosition() + dir * MAX_CONTROL_DIR_COEF;
	}
	sf::Vector2f p1 = dest, p2 = dest;
	if (_isMouseFollowing)
	{
		p1 += HelperFunctions::GetRandomPoint({ lt, rb - lt });
		p2 += HelperFunctions::GetRandomPoint({ lt, rb - lt });
	}
	else {
		p1 = dest+ HelperFunctions::GetRandomPoint({ {-delta / 2 / 6, -delta / 2 / 6},{delta / 6,  delta / 6} });
		p2 = middle + HelperFunctions::GetRandomPoint({ {-delta / 2, -delta / 2},{delta,  delta} });
	}
	spline.AddBezier(p1, p2);
}

void Scene::UpdateWindowViewCenter(float dt)
{
	auto view = _window->getView();
	auto prevCenter = view.getCenter();
	auto curCenter = GetPositionsCentroid();
	auto centerDelta = curCenter - prevCenter;
	auto dist = HelperFunctions::GetLength(centerDelta);
	auto curDist = dist * dt * 10;
	curCenter = prevCenter + curDist / dist * centerDelta;

	if (std::abs(curCenter.x) > 10000 || std::abs(curCenter.y) > 10000)
	{
		MovePosition(-curCenter);
		curCenter = { 0,0 };
	}
	view.setCenter(curCenter);
	_window->setView(view);

}

sf::Vector2f Scene::GetMouseWorldPosition() const
{
	return _window->mapPixelToCoords(_inputHandler->GetMousePosition());
}

