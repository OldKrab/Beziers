#include "MovingBezierSpline.h"

#include <algorithm>
#include <queue>

#include "HelperFunctions.h"
#include "ThicknessLine.h"

bool MovingBezierSpline::isDrawCurve = false;

void MovingBezierSpline::Update(float dt) {
    if (!_curCurve.has_value() || IsEnded())
        return;

    _curProgress += _speedProgress * dt;
    if (IsEnded())
        return;

    _curPosition = _curCurve->GetValue(_curProgress);
    _drawVertexes.emplace_back(_curPosition, _color);

    size_t cnt = _drawVertexes.size();

    static float dtSum = 0;
    dtSum += dt;
    if (dtSum * _decaySpeed > 1) {
        for (size_t i = 0; i < cnt; i++) {
            auto decay = static_cast<sf::Uint8>(dtSum * _decaySpeed);
            auto a = static_cast<sf::Uint8>(std::max(0, _drawVertexes[i].color.a - decay));
            _drawVertexes[i].color = HelperFunctions::GetGradientRgbColor(_colorGradient + static_cast<float>(255 - a) / 255 / 3);
            _drawVertexes[i].color.a = a;
        }
        dtSum = 0;
    }
    _drawVertexes.erase(std::ranges::remove_if(_drawVertexes, [](sf::Vertex v) { return v.color.a == 0; }).begin(), _drawVertexes.end());
}

void MovingBezierSpline::AddBezier(sf::Vector2f point, sf::Vector2f controlPoint) {
    if (!_curCurve.has_value()) {
        _curCurve = BezierCurve(std::vector<sf::Vector2f>{point, point, point, point});
        _curPosition = point;
        return;
    }
    const auto& prevPoints = _curCurve->Points;
    auto prevPoint = prevPoints[prevPoints.size() - 1];
    auto prevControlPoint = prevPoints[prevPoints.size() - 2];
    auto firstControlPoint = prevPoint + (prevPoint - prevControlPoint);
    _curCurve = BezierCurve(std::vector<sf::Vector2f>{prevPoint, firstControlPoint, controlPoint, point});
    _curProgress = 0;
}

void MovingBezierSpline::AddRandomBezier(sf::IntRect range) {
    AddBezier(_curPosition + HelperFunctions::GetRandomPoint(range), _curPosition + HelperFunctions::GetRandomPoint(range));
}

void MovingBezierSpline::MovePosition(sf::Vector2f vec) {
    for (auto&& point : _curCurve->Points)
        point += vec;
    for (auto&& vertex : _drawVertexes)
        vertex.position += vec;
    _curPosition += vec;
}

void drawCurve(const BezierCurve& curve, sf::RenderTarget& window) {
    int steps = 20;
    std::vector<sf::Vertex> line;
    for (int step = 0; step < steps; step++) {
        float x = (float)step / steps;
        line.emplace_back(curve.GetValue(x));
        if (step > 0)
            line.push_back(line.back());
    }

    window.draw(line.data(), line.size(), sf::Lines);
}

void MovingBezierSpline::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isDrawCurve)
        drawCurve(*_curCurve, target);
    ThicknessLine::Draw(target, _drawVertexes, _thickness);
}
